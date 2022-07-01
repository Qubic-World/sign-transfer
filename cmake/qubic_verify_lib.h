#pragma once

#include "qubic_verify_export.h"

extern "C" void QUBIC_VERIFY_EXPORT get_public_key_from_id(const unsigned char *identity, unsigned char *publicKey);
extern "C" bool QUBIC_VERIFY_EXPORT verify_signature(const unsigned char* publicKey, const unsigned char* messageDigest, const unsigned char* signature);
extern "C" void QUBIC_VERIFY_EXPORT kangaroo_twelve(unsigned char* input, unsigned long long inputByteLen, unsigned char* output, unsigned long long outputByteLen);
