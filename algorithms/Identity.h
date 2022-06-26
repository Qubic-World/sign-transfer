#pragma once

#include "FourQ.h"
#include "KangarooTwelve.h"

static bool getSubseed(const unsigned char* seed, unsigned char* subseed)
{
	unsigned char seedBytes[55];
	for (int i = 0; i < 55; i++)
	{
		if (seed[i] < 'a' || seed[i] > 'z')
		{
			return false;
		}
		seedBytes[i] = seed[i] - 'a';
	}
	KangarooTwelve(seedBytes, sizeof(seedBytes), subseed, 32);

	return true;
}

static void getPrivateKey(unsigned char* subseed, unsigned char* privateKey)
{
	KangarooTwelve(subseed, 32, privateKey, 32);
}

static void getPublicKey(const unsigned char* privateKey, unsigned char* publicKey)
{ // SchnorrQ public key generation
  // It produces a public key publicKey, which is the encoding of P = s*G, where G is the generator and
  // s is the output of hashing publicKey and taking the least significant 32 bytes of the result
  // Input:  32-byte privateKey
  // Output: 32-byte publicKey
	point_t P;

	ecc_mul_fixed((unsigned long long*)privateKey, P); // Compute public key                                       
	encode(P, publicKey);                              // Encode public key
}

static constexpr bool getPublicKeyFromIdentity(const unsigned char* identity, unsigned char* publicKey)
{
	for (int i = 0; i < 32; i++)
	{
		if (identity[i << 1] < 'A' || identity[i << 1] > 'P'
			|| identity[(i << 1) + 1] < 'A' || identity[(i << 1) + 1] > 'P')
		{
			return false;
		}
		publicKey[i] = ((identity[i << 1] - 'A') << 4) | (identity[(i << 1) + 1] - 'A');
	}

	return true;
}

static bool getSharedKey(const unsigned char* privateKey, const unsigned char* publicKey, unsigned char* sharedKey)
{ // Secret agreement computation for key exchange using a compressed, 32-byte public key
  // The output is the y-coordinate of privateKey*A, where A is the decoding of the public key publicKey
  // Inputs: 32-byte privateKey and 32-byte publicKey
  // Output: 32-byte sharedKey
	point_t A;

	if (publicKey[15] & 0x80) // Is bit128(PublicKey) = 0?
	{
		return false;
	}

	if (!decode(publicKey, A)) // Also verifies that A is on the curve, if it is not it fails
	{
		return false;
	}

	if (!ecc_mul(A, (unsigned long long*)privateKey, A))
	{
		return false;
	}

	if (A->x[0][0] == 0 && A->x[0][1] == 0 && A->x[1][0] == 0 && A->x[1][1] == 0
		&& A->y[0][0] == 1 && A->y[0][1] == 0 && A->y[1][0] == 0 && A->y[1][1] == 0) // Is output = neutral point (0,1)?
	{
		return false;
	}

	*((__m256i*)sharedKey) = *((__m256i*)A->y);

	return true;
}

static void getIdentity(unsigned char* const publicKey, uint16_t* identity)
{
	for (int i = 0; i < 32; i++)
	{
		identity[i << 1] = (publicKey[i] >> 4) + L'A';
		identity[(i << 1) + 1] = (publicKey[i] & 0xF) + L'A';
	}
	unsigned char identityBytesChecksum[3];
	KangarooTwelve(publicKey, 32, identityBytesChecksum, sizeof(identityBytesChecksum));
	for (int i = 0; i < sizeof(identityBytesChecksum); i++)
	{
		identity[64 + (i << 1)] = (identityBytesChecksum[i] >> 4) + L'A';
		identity[65 + (i << 1)] = (identityBytesChecksum[i] & 0xF) + L'A';
	}
	identity[70] = 0;
}

static void sign(const unsigned char* subseed, const unsigned char* publicKey, const unsigned char* messageDigest, unsigned char* signature)
{ // SchnorrQ signature generation
  // It produces the signature signature of a message messageDigest of size 32 in bytes
  // Inputs: 32-byte subseed, 32-byte publicKey, and messageDigest of size 32 in bytes
  // Output: 64-byte signature 
	point_t R;
	unsigned char k[64], r[64], h[64], temp[32 + 64];

	KangarooTwelve((unsigned char*)subseed, 32, k, 64);

	*((__m256i*)(temp + 32)) = *((__m256i*)(k + 32));
	*((__m256i*)(temp + 64)) = *((__m256i*)messageDigest);

	KangarooTwelve(temp + 32, 32 + 32, r, 64);

	ecc_mul_fixed((unsigned long long*)r, R);
	encode(R, signature); // Encode lowest 32 bytes of signature
	*((__m256i*)temp) = *((__m256i*)signature);
	*((__m256i*)(temp + 32)) = *((__m256i*)publicKey);

	KangarooTwelve(temp, 32 + 64, h, 64);
	modulo_order((unsigned long long*)r, (unsigned long long*)r);
	modulo_order((unsigned long long*)h, (unsigned long long*)h);
	Montgomery_multiply_mod_order((unsigned long long*)k, Montgomery_Rprime, (unsigned long long*)(signature + 32));
	Montgomery_multiply_mod_order((unsigned long long*)h, Montgomery_Rprime, (unsigned long long*)h);
	Montgomery_multiply_mod_order((unsigned long long*)(signature + 32), (unsigned long long*)h, (unsigned long long*)(signature + 32));
	Montgomery_multiply_mod_order((unsigned long long*)(signature + 32), ONE, (unsigned long long*)(signature + 32));
	subtract_mod_order((unsigned long long*)r, (unsigned long long*)(signature + 32), (unsigned long long*)(signature + 32));
}

static bool verify(const unsigned char* publicKey, const unsigned char* messageDigest, const unsigned char* signature)
{ // SchnorrQ signature verification
  // It verifies the signature Signature of a message MessageDigest of size 32 in bytes
  // Inputs: 32-byte PublicKey, 64-byte Signature, and MessageDigest of size 32 in bytes
  // Output: true (valid signature) or false (invalid signature)
	point_t A;
	unsigned char temp[32 + 64], h[64];

	if (((publicKey[15] & 0x80) != 0) || ((signature[15] & 0x80) != 0) || (signature[63] != 0) || ((signature[62] & 0xC0) != 0))
	{  // Are bit128(PublicKey) = bit128(Signature) = 0 and Signature+32 < 2^246?
		return false;
	}

	if (!decode(publicKey, A)) // Also verifies that A is on the curve, if it is not it fails
	{
		return false;
	}

	*((__m256i*)temp) = *((__m256i*)signature);
	*((__m256i*)(temp + 32)) = *((__m256i*)publicKey);
	*((__m256i*)(temp + 64)) = *((__m256i*)messageDigest);

	KangarooTwelve(temp, 32 + 64, h, 64);

	if (!ecc_mul_double((unsigned long long*)(signature + 32), (unsigned long long*)h, A))
	{
		return false;
	}

	encode(A, (unsigned char*)A);

	return (_mm256_movemask_epi8(_mm256_cmpeq_epi64(*((__m256i*)A), *((__m256i*)signature))) == 0xFFFFFFFF);
}