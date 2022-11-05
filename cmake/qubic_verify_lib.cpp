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

static const auto ZERO{_mm256_setzero_si256()};

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
   alignas(32) uint8_t *message_alignas{new uint8_t[messageSize]};
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

unsigned int get_score(const unsigned char (&nonces)[][32],
                       uint16_t nubmerOfSolutionNonces)
{
   unsigned int score{0};

   for (unsigned int i = 0; i < nubmerOfSolutionNonces; ++i)
   {
      if (_mm256_movemask_epi8(
              _mm256_cmpeq_epi64(_mm256_lddqu_si256((__m256i *)nonces[i]), ZERO)) != 0xFFFFFFFF)
      {
         ++score;
      }
   }

   return score;
}

void random(unsigned char *publicKey, unsigned char *nonce, unsigned char *output, unsigned int outputSize)
{
   alignas(32) unsigned char state[200]{0};
   *((__m256i *)&state[0]) = *((__m256i *)publicKey);
   *((__m256i *)&state[32]) = *((__m256i *)nonce);
   memset(&state[64], 0, sizeof(state) - 64);

   for (unsigned int i = 0; i < outputSize / sizeof(state); i++)
   {
      KeccakP1600_Permute_12rounds(state);
      memcpy(output, state, sizeof(state));
      output += sizeof(state);
   }
   if (outputSize % sizeof(state))
   {
      KeccakP1600_Permute_12rounds(state);
      memcpy(output, state, outputSize % sizeof(state));
   }
}

using miningDataType = std::array<unsigned long long, 65536>;

inline miningDataType getMiningData()
{
   unsigned char randomSeed[32]{0};
   randomSeed[0] = 200;
   randomSeed[1] = 80;
   randomSeed[2] = 105;
   randomSeed[3] = 2;
   randomSeed[4] = 212;
   randomSeed[5] = 16;
   randomSeed[6] = 70;
   randomSeed[7] = 28;

   miningDataType miningData;
   random(randomSeed, randomSeed, (unsigned char *)miningData.data(), sizeof(miningData));
   return miningData;
}

unsigned int get_real_score(const unsigned char *publicKey, const unsigned char (&nonces)[][32], uint16_t nubmerOfSolutionNonces)
{
   unsigned int realScore = 0;
   alignas(32) unsigned char *alignasPublicKey[transfer::size::key_size]{0};
   memcpy(alignasPublicKey, publicKey, transfer::size::key_size);

   constexpr auto NUMBER_OF_NEURONS{19000};
   constexpr auto SOLUTION_THRESHOLD{27};

   unsigned int neuronLinks[NUMBER_OF_NEURONS][2]{0};
   constexpr auto neuroLinksSize{sizeof(neuronLinks)};

   unsigned char neuronValues[NUMBER_OF_NEURONS]{0};

   static const auto miningData{getMiningData()};

   for (uint32_t j = 0; j < nubmerOfSolutionNonces; j++)
   {
      if (_mm256_movemask_epi8(_mm256_cmpeq_epi64(_mm256_lddqu_si256((__m256i *)nonces[j]), ZERO)) != 0xFFFFFFFF)
      {
         {
            uint32_t k{0};
            for (k = 0; k < j; k++)
            {
               if (_mm256_movemask_epi8(_mm256_cmpeq_epi64(_mm256_lddqu_si256((__m256i *)nonces[k]), _mm256_lddqu_si256((__m256i *)nonces[j]))) == 0xFFFFFFFF)
               {
                  break;
               }
            }
            if (k != j)
            {
               break;
            }
         }

         {
            alignas(32) unsigned char nonce[32]{0};
            memcpy(nonce, nonces[j], 32);

            random((unsigned char *)alignasPublicKey, nonce, (unsigned char *)neuronLinks, neuroLinksSize);
         }

         for (unsigned int k = 0; k < NUMBER_OF_NEURONS; k++)
         {
            neuronLinks[k][0] %= NUMBER_OF_NEURONS;
            neuronLinks[k][1] %= NUMBER_OF_NEURONS;
            neuronValues[k] = 0xFF;
         }

         unsigned int limiter = 10000;
         unsigned int outputLength = 0;
         while (true)
         {
            const unsigned int prevValue0 = neuronValues[NUMBER_OF_NEURONS - 1];
            const unsigned int prevValue1 = neuronValues[NUMBER_OF_NEURONS - 2];

            for (unsigned int k = 0; k < NUMBER_OF_NEURONS; k++)
            {
               neuronValues[k] = ~(neuronValues[neuronLinks[k][0]] & neuronValues[neuronLinks[k][1]]);
            }

            if (neuronValues[NUMBER_OF_NEURONS - 1] != prevValue0 && neuronValues[NUMBER_OF_NEURONS - 2] == prevValue1)
            {
               if (!((miningData[outputLength >> 6] >> (outputLength & 63)) & 1))
               {
                  break;
               }

               outputLength++;
            }
            else
            {
               if (neuronValues[NUMBER_OF_NEURONS - 2] != prevValue1 && neuronValues[NUMBER_OF_NEURONS - 1] == prevValue0)
               {
                  if ((miningData[outputLength >> 6] >> (outputLength & 63)) & 1)
                  {
                     break;
                  }

                  outputLength++;
               }
               else
               {
                  if (!(--limiter))
                  {
                     break;
                  }
               }
            }
         }

         // std::cout << "Output length: " << outputLength << std::endl;
         if (outputLength >= SOLUTION_THRESHOLD)
         {
            ++realScore;
         }
      }
   }

   return realScore;
}