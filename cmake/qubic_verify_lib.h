#pragma once
#include <cinttypes>
#ifdef _WIN32
    #include "qubic_verify_export_Windows.h"
#elif __linux__
    #include "qubic_verify_export_Linux.h"
#endif


extern "C" void QUBIC_VERIFY_EXPORT get_public_key_from_id(const unsigned char *identity, unsigned char *publicKey);
extern "C" bool QUBIC_VERIFY_EXPORT verify_signature(const unsigned char *publicKey, const unsigned char *messageDigest, const unsigned char *signature);
extern "C" void QUBIC_VERIFY_EXPORT kangaroo_twelve(unsigned char *input, unsigned long long inputByteLen, unsigned char *output, unsigned long long outputByteLen);

/** Sign*/
extern "C" bool QUBIC_VERIFY_EXPORT get_subseed(const unsigned char *seed, unsigned char *subseed);
extern "C" void QUBIC_VERIFY_EXPORT get_private_key(unsigned char* subseed, unsigned char* privateKey);
extern "C" void QUBIC_VERIFY_EXPORT get_public_key(const unsigned char* privateKey, unsigned char* publicKey);
extern "C" void QUBIC_VERIFY_EXPORT sign_message(const unsigned char *subseed, const unsigned char *publicKey, const unsigned char *message, const uint64_t messageSize, unsigned char *signature);
extern "C" void QUBIC_VERIFY_EXPORT sign_signature(const unsigned char* subseed, const unsigned char* publicKey, const unsigned char* messageDigest, unsigned char* signature);

extern "C" void QUBIC_VERIFY_EXPORT get_identity(unsigned char *const publicKey, uint16_t *identity);