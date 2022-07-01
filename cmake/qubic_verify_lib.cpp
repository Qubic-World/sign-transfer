#include "qubic_verify_lib.h"
#include <cstring>
#include "types.h"
#include "Identity.h"

void get_public_key_from_id(const unsigned char *identity, unsigned char *publicKey)
{
   getPublicKeyFromIdentity(identity, publicKey);
}

bool verify_signature(const unsigned char *publicKey, const unsigned char *messageDigest, const unsigned char *signature)
{
   alignas(32) uint8_t public_key_alignas[transfer::size::key_size]{};
   alignas(32) uint8_t digest_alignas[transfer::size::digest_size]{};
   alignas(32) uint8_t signature_alignas[transfer::size::signature_size]{};

#ifndef __GNUC__
   memcpy_s(public_key_alignas, transfer::size::key_size, publicKey, transfer::size::key_size);
   memcpy_s(digest_alignas, transfer::size::digest_size, messageDigest, transfer::size::digest_size);
   memcpy_s(signature_alignas, transfer::size::signature_size, signature, transfer::size::signature_size);
#else
   memcpy(public_key_alignas, publicKey, transfer::size::key_size);
   memcpy(digest_alignas, messageDigest, transfer::size::digest_size);
   memcpy(signature_alignas, signature, transfer::size::signature_size);
#endif

   return ::verify(public_key_alignas, digest_alignas, signature_alignas);
}
void kangaroo_twelve(unsigned char *input, unsigned long long inputByteLen, unsigned char *output, unsigned long long outputByteLen)
{
   KangarooTwelve(input, inputByteLen, output, outputByteLen);
}