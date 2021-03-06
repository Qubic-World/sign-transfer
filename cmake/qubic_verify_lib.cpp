#include "qubic_verify_lib.h"
#include <cstring>
#include "types.h"
#include "Identity.h"

class memoryWraper final
{
private:
   uint8_t *ptr_;

public:
   memoryWraper(uint8_t *ptr) : ptr_(ptr)
   {
   }
   ~memoryWraper()
   {
      if (ptr_)
      {
         delete[] ptr_;
      }
   }
};

void get_public_key_from_id(const unsigned char *identity, unsigned char *publicKey)
{
   getPublicKeyFromIdentity(identity, publicKey);
}

bool verify_signature(const unsigned char *publicKey, const unsigned char *messageDigest, const unsigned char *signature)
{
   alignas(32) uint8_t public_key_alignas[transfer::size::key_size]{};
   alignas(32) uint8_t digest_alignas[transfer::size::digest_size]{};
   alignas(32) uint8_t signature_alignas[transfer::size::signature_size]{};

   memcpy(public_key_alignas, publicKey, transfer::size::key_size);
   memcpy(digest_alignas, messageDigest, transfer::size::digest_size);
   memcpy(signature_alignas, signature, transfer::size::signature_size);

   return verify(public_key_alignas, digest_alignas, signature_alignas);
}

bool verify_message(const unsigned char *publicKey, const unsigned char *message, const uint64_t messageSize, const unsigned char *signature)
{
   alignas(32) uint8_t public_key_alignas[transfer::size::key_size]{};
   alignas(32) uint8_t* message_alignas{new uint8_t[messageSize]};
   alignas(32) uint8_t signature_alignas[transfer::size::signature_size]{};

   memoryWraper mw{message_alignas};

   memcpy(public_key_alignas, publicKey, transfer::size::key_size);
   memcpy(message_alignas, message, messageSize);
   memcpy(signature_alignas, signature, transfer::size::signature_size);

   return verifyMessage(public_key_alignas, message_alignas, messageSize, signature_alignas);

}

void kangaroo_twelve(unsigned char *input, unsigned long long inputByteLen, unsigned char *output, unsigned long long outputByteLen)
{
   KangarooTwelve(input, inputByteLen, output, outputByteLen);
}

/** Sign*/

bool get_subseed(const unsigned char *seed, unsigned char *subseed)
{
   return getSubseed(seed, subseed);
}

void get_private_key(unsigned char *subseed, unsigned char *privateKey)
{
   getPrivateKey(subseed, privateKey);
}

void get_public_key(const unsigned char *privateKey, unsigned char *publicKey)
{
   alignas(32) transfer::types::key_type public_key_alignas{};

   getPublicKey(privateKey, public_key_alignas);
   memcpy(publicKey, public_key_alignas, transfer::size::key_size);
}

void sign_signature(const unsigned char *subseed, const unsigned char *publicKey, const unsigned char *messageDigest, unsigned char *signature)
{
   alignas(32) transfer::types::signature_type signature_alignas{};
   alignas(32) transfer::types::digest_type digest_alignas{};
   alignas(32) transfer::types::key_type public_key_alignas{};

   memcpy(digest_alignas, messageDigest, transfer::size::digest_size);
   memcpy(public_key_alignas, publicKey, transfer::size::key_size);

   sign(subseed, public_key_alignas, digest_alignas, signature_alignas);
   memcpy(signature, signature_alignas, sizeof(transfer::types::signature_type));
}


void sign_message(const unsigned char *subseed, const unsigned char *publicKey, const unsigned char *message, const uint64_t messageSize, unsigned char *signature)
{
   alignas(32) transfer::types::signature_type signature_alignas{};
   alignas(32) uint8_t *message_alignas{new uint8_t[messageSize]};
   alignas(32) transfer::types::key_type public_key_alignas{};
   alignas(32) const uint64_t message_size_alignas{messageSize};

   memoryWraper mw{message_alignas};

   memcpy(message_alignas, message, messageSize);
   memcpy(public_key_alignas, publicKey, transfer::size::key_size);

   signMessage(subseed, public_key_alignas, message_alignas, message_size_alignas, signature_alignas);
   memcpy(signature, signature_alignas, sizeof(transfer::types::signature_type));
}

void get_identity(unsigned char *const publicKey, uint16_t *identity)
{
   alignas(32) transfer::types::identity_type identity_alignas{};
   getIdentity(publicKey, identity_alignas);

   memcpy(identity, identity_alignas, transfer::size::id_len * sizeof(uint16_t));
}