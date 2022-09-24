////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) since 1999. VASCO DATA SECURITY
// All rights reserved. http://www.vasco.com
//
////////////////////////////////////////////////////////////////////////////////

#ifndef openSSL_h
#define openSSL_h

#include <stdio.h>

#define fipsOpenSSL_VERSION  @"4.21.1"

/**
 * SHA-1 hash
 */
#define FIPS_SSL_CONSTANTS_HASH_SHA_1 0x02

/**
 * SHA-256 hash
 */
#define FIPS_SSL_CONSTANTS_HASH_SHA_256 0x03

/**
 * Triple DES cipher mechanism
 */
#define FIPS_SSL_CONSTANTS_CIPHER_MECHANISM_DES3 0x02

/**
 * AES cipher mechanism
 */
#define FIPS_SSL_CONSTANTS_CIPHER_MECHANISM_AES 0x03

/**
 * ECB cipher mode
 */
#define FIPS_SSL_CONSTANTS_CIPHER_MODE_ECB 0x01

/**
 * CBC cipher mode
 */
#define FIPS_SSL_CONSTANTS_CIPHER_MODE_CBC 0x02

/**
 * CFB cipher mode
 */
#define FIPS_SSL_CONSTANTS_CIPHER_MODE_CFB 0x03

/**
 * CTR cipher mode
 */
#define FIPS_SSL_CONSTANTS_CIPHER_MODE_CTR 0x04

#define openSSL_encrypt(...) C8pyszN8ayikqooys7BV(__VA_ARGS__)
int openSSL_encrypt(unsigned char mechanism,
                    unsigned char mode,
                    unsigned char* key,
                    int keyLength,
                    unsigned char* iv,
                    unsigned char* input,
                    size_t inputLength,
                    unsigned char* output,
                    size_t* outputLength);

#define openSSL_decrypt(...) iJNWyCooVtzJP8mwPIJ0(__VA_ARGS__)
int openSSL_decrypt(unsigned char mechanism,
                    unsigned char mode,
                    unsigned char* key,
                    int keyLength,
                    unsigned char* iv,
                    unsigned char* input,
                    size_t inputLength,
                    unsigned char* output,
                    size_t* outputLength);

#define openSSL_shaCalculate(...) BQY3OgONaWaEr4YVVraB(__VA_ARGS__)
int openSSL_shaCalculate(unsigned char algo,
                         const unsigned char *dataIn,
                         size_t dataInLength,
                         unsigned char outputBuffer[]);

#define openSSL_Hmac(...) n3mzHvoSyLIKDKSkbbVK(__VA_ARGS__)
int openSSL_Hmac (unsigned char algo,
                  unsigned char output[],
                  const unsigned char *key,
                  size_t keylen,
                  const unsigned char *data,
                  size_t len );

#define openSSL_generate_random(...) OE3f7X5QasJTwzcALKl4(__VA_ARGS__)
int openSSL_generate_random (unsigned char * dataOut,
                             size_t dataOutLength);

#endif /* openSSL_h */
