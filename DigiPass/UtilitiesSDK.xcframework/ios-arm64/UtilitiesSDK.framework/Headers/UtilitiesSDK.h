//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef UtilitiesSDK_H
#define UtilitiesSDK_H

#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus

#define UTILITIES_SDK_VERSION "4.28.0"

#ifndef WBCTYPES_DEC_H_
#define WBCTYPES_DEC_H_

// to avoid duplicate def with WBCSDK, this define has been added

#include <stdlib.h>
#include <stdint.h>

// Number of rounds (set to 10 for AES128)
#define NR 10

// Define whether we can use the hidden attribute
#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
/* Test for GCC > 4.0.0 */
#if GCC_VERSION > 40000
#define ATTRIBUTE __attribute__ ((visibility ("hidden")))
#else
#define ATTRIBUTE
#endif


// Type I Lookup tables
typedef uint8_t (typeI_t)[4][4][256][16];
// Type IA Lookup tables (same as typeI_t)
typedef typeI_t typeIA_t;
// Type IB Lookup tables (same as typeI_t)
typedef typeI_t typeIB_t;
// Type II or Type III Lookup tables (for one round)
typedef uint8_t (typeII_round_t)[4][4][256][4];
// Type II or Type III Lookup tables (for one round)
typedef typeII_round_t typeIII_round_t;
// Type II or Type III Lookup tables for all rounds
typedef typeII_round_t (typeII_t)[NR-1];
// Type II or Type III Lookup tables for all rounds
typedef typeII_t typeIII_t;
// Type IV Lookup tables following Type I (128 bit)
typedef uint8_t (typeIV128_t)[4][4][15][2][128];
// Type IV Lookup tables following Type IA (128 bit)
typedef typeIV128_t typeIV_IA_t;
// Type IV Lookup tables following Type IB (128 bit)
typedef typeIV128_t typeIV_IB_t;
// Type IV Lookup tables following Type II or III (32 bit) for one round
typedef uint8_t (typeIV32_round_t)[4][4][3][2][128];
// Type IV Lookup tables following Type II or III (32 bit) for all rounds
typedef typeIV32_round_t (typeIV32_t)[NR-1];
// Type IV Lookup tables following Type II (32 bit) for all rounds
typedef typeIV32_round_t typeIV_II_round_t;
// Type IV Lookup tables following Type III (32 bit) for all rounds
typedef typeIV32_round_t typeIV_III_round_t;
// 4-bit strips for 32bit operations
typedef uint8_t _4bit_strip32_t[4][4][4];
// 4-bit strips for 128bit operations
typedef uint8_t _4bit_strip128_t[4][4][16];
// 2 4x4sboxes used in 4bit encoding/decoding
typedef uint8_t (sboxes_8bit_t)[4][4][2][16];


// A word is the typical packed data structure to represent packed bits
typedef uint64_t word;

// Type of row and column indexes
// This type is used for integer values that hold row/colum sized values
typedef int rci_t;

// Type of word indexes
// This type is used for the array of words that make up a row
typedef int wi_t;

// Blocks
typedef struct
{
    size_t size;
    word* begin;
    word* end;
} mzd_block_t;


// Dense matrices over GF(2)
typedef struct mzd_t
{
    // Number of rows.
    rci_t nrows;
    // Number of columns.
    rci_t ncols;
    // Number of words with valid bits.
    // width = ceil((ncols + offset) / matrix_radix)
    wi_t width;
    // Offset in words between rows.
    // rowstride = (width < mzd_paddingwidth || (width & 1) == 0) ? width : width + 1;
    // where width is the width of the underlying non-windowed matrix.
    wi_t rowstride;
    // Offset in words from start of block to first word.
    // rows[0] = blocks[0].begin + offset_vector;
    // This, together with rowstride, makes the rows array obsolete.
    wi_t offset_vector;
    // Number of rows to the first row counting from the start of the first block.
    wi_t row_offset;
    // column offset of the first column.
    uint16_t offset;
    // Booleans to speed up things.
    // The bits have the following meaning:
    // 0: Has non-zero offset (and thus is windowed).
    // 1: Has non-zero excess.
    // 2: Is windowed, but has zero offset.
    // 3: Is windowed, but has zero excess.
    // 4: Is windowed, but owns the blocks allocations.
    // 5: Spans more than 1 block.
    uint8_t flags;
    // blockrows_log = log2(blockrows);
    // where blockrows is the number of rows in one block, which is a power of 2.
    uint8_t blockrows_log;
    // Mask for valid bits in the word with the highest index (width - 1).
    word high_bitmask;
    // Mask for valid bits in the word with the lowest index (0).
    word low_bitmask;
    // Contains pointers to the actual blocks of memory containing the
    // values packed into words of size matrix_radix.
    mzd_block_t *blocks;
    // Address of first word in each row, so the first word of row i is m->rows[i]
    word **rows;
} mzd_t;

// make gf2matrix the same as mzd_t in m4ri
typedef mzd_t gf2matrix;


int ATTRIBUTE message_to_typeIA_input_sbox(uint8_t *message, int nLength, sboxes_8bit_t typeIA_input_sbox);
int ATTRIBUTE message_to_typeIAs(uint8_t *message, int nLength, typeIA_t typeIAs);
int ATTRIBUTE message_to_typeIV_IAs(uint8_t *message, int nLength, typeIV_IA_t typeIV_IAs);
int ATTRIBUTE message_to_typeIIs(uint8_t *message, int nLength, typeII_t typeIIs);
int ATTRIBUTE message_to_typeIV_IIs(uint8_t *message, int nLength, typeIV_II_round_t typeIV_IIs[NR - 1]);
int ATTRIBUTE message_to_typeIIIs(uint8_t *message, int nLength, typeIII_t typeIIIs);
int ATTRIBUTE message_to_typeIV_IIIs(uint8_t *message, int nLength, typeIV_III_round_t typeIV_IIIs[NR - 1]);
int ATTRIBUTE message_to_typeIBs(uint8_t *message, int nLength, typeIB_t typeIBs);
int ATTRIBUTE message_to_typeIV_IBs(uint8_t *message, int nLength, typeIV_IB_t typeIV_IBs);
int ATTRIBUTE message_to_typeIB_output_sbox_inv(uint8_t *message, int nLength, sboxes_8bit_t typeIB_output_sbox_inv);
int ATTRIBUTE message_to_gf2matrix(uint8_t *message, int nLength, gf2matrix **matrix);

#endif /* WBCTYPES_DEC_H_ */

    /**
     * MD5 hash
     */
#define UTILITIES_SDK_CONSTANTS_HASH_MD5 0x01
    
    /**
     * SHA-1 hash
     */
#define UTILITIES_SDK_CONSTANTS_HASH_SHA_1 0x02
    
    /**
     * SHA-256 hash
     */
#define UTILITIES_SDK_CONSTANTS_HASH_SHA_256 0x03
    
    /**
     * SM3 hash
     */
#define UTILITIES_SDK_CONSTANTS_HASH_SM3 0x04
    
    /**
     * DES cipher mechanism
     */
#define UTILITIES_SDK_CONSTANTS_CIPHER_MECHANISM_DES 0x01
    
    /**
     * Triple DES cipher mechanism
     */
#define UTILITIES_SDK_CONSTANTS_CIPHER_MECHANISM_DES3 0x02
    
    /**
     * AES cipher mechanism
     */
#define UTILITIES_SDK_CONSTANTS_CIPHER_MECHANISM_AES 0x03
    
    /**
     * ECB cipher mode
     */
#define UTILITIES_SDK_CONSTANTS_CIPHER_MODE_ECB 0x01
    
    /**
     * CBC cipher mode
     */
#define UTILITIES_SDK_CONSTANTS_CIPHER_MODE_CBC 0x02
    
    /**
     * CFB cipher mode
     */
#define UTILITIES_SDK_CONSTANTS_CIPHER_MODE_CFB 0x03
    
    /**
     * CTR cipher mode
     */
#define UTILITIES_SDK_CONSTANTS_CIPHER_MODE_CTR 0x04

/**
 * The secure channel message is a multi-device license activation message.
 */
#define UTILITIES_SDK_SECURE_CHANNEL_MESSAGE_TYPE_LICENSE_ACTIVATION 0

/**
 * The secure channel message is an multi-device instance activation message.
 */
#define UTILITIES_SDK_SECURE_CHANNEL_MESSAGE_TYPE_INSTANCE_ACTIVATION 1

/**
 * The secure channel message is a deactivation message.
 */
#define UTILITIES_SDK_SECURE_CHANNEL_MESSAGE_TYPE_DEACTIVATION 2

/**
 * The secure channel message is a request message.
 */
#define UTILITIES_SDK_SECURE_CHANNEL_MESSAGE_TYPE_REQUEST 3

/**
 * The secure channel message is a response message.
 */
#define UTILITIES_SDK_SECURE_CHANNEL_MESSAGE_TYPE_RESPONSE 4

/**
 * Length of the secure channel message header
 * */
#define UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_HEADER 15

/**
 * Length of the secure channel message footer
 * */
#define UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_FOOTER 8

/**
 * Length of the secure channel message serial number
 * */
#define UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER 10

/**
 * Length of the secure channel message authentication tag
 * */
#define UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_NONCE 8

/**
 * Maximal length of the secure channel message body
 * */
#define UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_BODY_MAX 2078

/**
 * Maximal length of the secure channel message
 * */
#define UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_MAX (UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_HEADER + UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_BODY_MAX + UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_FOOTER)

/**
 * The secure channel message is not protected.
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_PROTECTION_NONE 0x00

/**
 * The secure channel message is validated using HMAC-SHA256 and its payload is ciphered with AES-128-CTR.
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_PROTECTION_HMAC_AESCTR 0x01

/**
 * The secure channel message is validated using HMAC-SHA256 and its payload is not ciphered.
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_PROTECTION_HMAC 0x11

/**
 * Minimal value for the protocol version of a secure channel message
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_PROTOCOL_VERSION_MIN 0

/**
 * Maximal value for the protocol version of a secure channel message
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_PROTOCOL_VERSION_MAX 0x0F

/**
 * Minimal value for the message type of a secure channel message
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_MESSAGE_TYPE_MIN 0

/**
 * Maximal value for the message type of a secure channel message
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_MESSAGE_TYPE_MAX 0x3F

/**
 * Minimal value for the protection type of a secure channel message
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_PROTECTION_TYPE_MIN 0

/**
 * Maximal value for the protection type of a secure channel message
 */
#define UTILITIES_SDK_VALUES_SECURE_CHANNEL_MESSAGE_PROTECTION_TYPE_MAX 0x3F

/**
 * Operation successful
 */
#define UTILITIES_SDK_RETURN_CODE_SUCCESS 0

/**
 * The crypto mechanism is invalid
 */
#define UTILITIES_SDK_RETURN_CODE_CRYPTO_MECANISM_INVALID -4201

/**
 * The crypto mode is invalid
 */
#define UTILITIES_SDK_RETURN_CODE_CRYPTO_MODE_INVALID -4202

/**
 * The key is null
 */
#define UTILITIES_SDK_RETURN_CODE_KEY_NULL -4203

/**
 * The key length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_KEY_INCORRECT_LENGTH -4204

/**
 * The input data is null
 */
#define UTILITIES_SDK_RETURN_CODE_INPUT_DATA_NULL -4205

/**
 * The input data length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH -4206

/**
 * The initial vector length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_INCORRECT_LENGTH -4207

/**
 * The output data is null
 */
#define UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL -4208

/**
 * The output data length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH -4209

/**
 * The key to derive is null
 */
#define UTILITIES_SDK_RETURN_CODE_INPUT_KEY_NULL -4210

/**
 * The salt is null
 */
#define UTILITIES_SDK_RETURN_CODE_SALT_NULL -4211

/**
 * The iteration count is incorrect. Must be > 0
 */
#define UTILITIES_SDK_RETURN_CODE_ITERATION_COUNT_INCORRECT -4212

/**
 * The secure channel message is null
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NULL -4213

/**
 * The secure channel message format is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_FORMAT -4214

/**
 * The secure channel message length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_LENGTH -4215

/**
 * The secure channel message protocol version is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_PROTOCOL_VERSION -4216

/**
 * The secure channel message message type is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_MESSAGE_TYPE -4217

/**
 * The secure channel message protection type is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_PROTECTION_TYPE -4218

/**
 * The secure channel message serial number is null
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER_NULL -4219

/**
 * The secure channel message serial number length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER_INCORRECT_LENGTH -4220

/**
 * The secure channel message serial number format is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER_INCORRECT_FORMAT -4221

/**
 * The secure channel message nonce is null
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NONCE_NULL -4222

/**
 * The secure channel message nonce length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NONCE_INCORRECT_LENGTH -4223

/**
 * The secure channel message nonce format is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NONCE_INCORRECT_FORMAT -4224

/**
 * The secure channel message body is null
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_BODY_NULL -4225

/**
 * The secure channel message body length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_BODY_INCORRECT_LENGTH -4226

/**
 * The secure channel message body format is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_BODY_INCORRECT_FORMAT -4227

/**
 * The secure channel message authentication tag is null
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_AUTHENTICATION_TAG_NULL -4228

/**
 * The secure channel message authentication tag length is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_AUTHENTICATION_TAG_INCORRECT_LENGTH -4229

/**
 * The secure channel message authentication tag format is incorrect
 */
#define UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_AUTHENTICATION_TAG_INCORRECT_FORMAT -4230

/**
 * The white box data is invalid
 */
#define UTILITIES_SDK_RETURN_CODE_WBC_INPUT_ARRAY_INVALID -4231

/**
* The initial vector is null
*/
#define UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_NULL -4232

/**
* There was an error while generating a random byte
*/
#define UTILITIES_SDK_RETURN_CODE_RANDOM_GENERATOR_ERROR -4232

/**
 * Unknown error: occurs when an unmanaged exception is raised, the return code value is {@value UNKNOWN_ERROR}.
 */
#define UTILITIES_SDK_RETURN_CODE_UNKNOWN_ERROR -4299


#ifndef  VDSTYPES_H

#if defined(WIN64)
  #include <windows.h>
  #ifndef VDS_EXPORT
    #define VDS_EXPORT(type) type __stdcall
  #endif
#else
  #ifndef VDS_EXPORT
    #define VDS_EXPORT(type) type
  #endif
#endif  // WIN64

#if defined(__MVS__)
  #ifndef _EBCDIC
    #define _EBCDIC
  #endif
  #ifndef WORDS_BIGENDIAN
    #define WORDS_BIGENDIAN
  #endif
#endif  // __MVS__

#ifdef _EBCDIC
  typedef unsigned char         vds_ascii;
#else
  typedef char                  vds_ascii;    //!< DIGIPASS SDK internal type, represents a character
#endif  // _EBCDIC

typedef unsigned char vds_byte;        //!< DIGIPASS SDK internal type, represents a byte
typedef short int vds_bool;            //!< DIGIPASS SDK internal type, represents a boolean
typedef short int vds_int16;           //!< DIGIPASS SDK internal type, represents a signed short
typedef unsigned short int vds_uint16; //!< DIGIPASS SDK internal type, represents an unsigned short

typedef int           vds_int32;
typedef unsigned int  vds_word32;

#if defined(WIN64) /* For windows 64 bit : long is still coded on 4 bytes as the int */
 typedef __int64          vds_int64; /* NEW */
 typedef unsigned __int64 vds_word64; /* NEW */
 #define atoint64         _atoi64
 #define strtol64         _strtoi64
#else
 typedef long long          vds_int64; /* NEW */
 typedef unsigned long long vds_word64; /* NEW */
 #define atoint64           atoll
 #define strtol64           strtoll
#endif

#define vds_false 0 //!< DIGIPASS SDK internal type, represents the FALSE boolean
#define vds_true  1 //!< DIGIPASS SDK internal type, represents the TRUE boolean

#endif  // vdsTypes_H

#if defined(WIN64)
   #ifndef SDK_IMPORT
     #define SDK_IMPORT(type) type __stdcall
   #endif
   #ifndef SDK_EXPORT
     #define SDK_EXPORT(type) type __stdcall
   #endif
 #else
   #ifndef SDK_IMPORT
     #define SDK_IMPORT(type) type
   #endif
   #ifndef SDK_EXPORT
     #define SDK_EXPORT(type) type
   #endif
 #endif


 //--------------------------------------------------------------------------
 //--- STRUCTURES -----------------------------------------------------------
 //--------------------------------------------------------------------------

 typedef struct
 {
     vds_byte protocolVersion;
     vds_byte messageType;
     vds_byte protectionType;
     vds_ascii serialNumber[UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER + 1];
     vds_ascii nonce[UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_NONCE * 2 + 1];
     vds_ascii body[UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_BODY_MAX * 2 + 1];
     vds_ascii authenticationTag[UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_FOOTER * 2 + 1];
     vds_ascii rawData[UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_MAX * 2 + 1];
     vds_bool encrypted;
 } UtilitiesSDKSecureChannelMessage;

#define UtilitiesSDK_hash(...) aRsUBwSTybWFNyIYYAUJ(__VA_ARGS__)
 /**
  * Hash function
  * @param mechanism Hash mechanism (HASH_MD5, HASH_SHA_1 or HASH_SHA_256)
  * @param dataIn Data to hash, cannot be null
  * @param dataInLength length of data to hash
  * @param dataOut output buffer, cannot be null
  * @param dataOutLength length of output buffer
  * @return A return code indicating the process result
  * <br/>The following codes can be returned:
  * <ul>
  *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS in case of success</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_CRYPTO_MECANISM_INVALID if the mechanism is not managed</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_NULL if the input bytes array is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL if the output data is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH if the output data length is invalid</li>
  * </ul>
  */
 SDK_IMPORT(vds_int32) UtilitiesSDK_hash(vds_int32 mechanism, vds_byte* dataIn, vds_int32 dataInLength, vds_byte* dataOut,
		vds_int32* dataOutLength);

#define UtilitiesSDK_hmac(...) XHnjJORiObqDzdphsNFq(__VA_ARGS__)
 /**
  * Keyed-hash message authentication code (HMAC)
  * @param mechanism HMAC mechanism (only HASH_SHA_256 supported)
  * @param dataIn Data to hash, cannot be null
  * @param dataInLength length of data to hash
  * @param key cryptographic key, cannot be null
  * @param keyLength length of the cryptographic key
  * @param dataOut output buffer, cannot be null
  * @param dataOutLength length of output buffer
  * @return A return code indicating the process result
  * <br/>The following codes can be returned:
  * <ul>
  *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS in case of success</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_CRYPTO_MECANISM_INVALID if the mechanism is not managed</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_NULL if the input bytes array is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH if the input bytes array length is invalid</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_KEY_NULL if the key is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_KEY_INCORRECT_LENGTH if the key length is invalid</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL if the output data is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH if the output data length is invalid</li>
  * </ul>
  */
 SDK_IMPORT(vds_int32) UtilitiesSDK_hmac(vds_int32 mechanism, vds_byte* dataIn, vds_int32 dataInLength, vds_byte* key, vds_int32 keyLength,
         vds_byte* dataOut, vds_int32 dataOutLength);

#define UtilitiesSDK_encrypt(...) OlYGCMHnMEdyhzldzixr(__VA_ARGS__)
 /**
  * Cipher function to encrypt data
  * @param mechanism Cipher mechanism (CIPHER_MECHANISM_DES, CIPHER_MECHANISM_DES3, CIPHER_MECHANISM_AES)
  * @param mode Cipher mode (CIPHER_MODE_ECB, CIPHER_MODE_CBC, CIPHER_MODE_CFB, CIPHER_MODE_CTR)
  * @param key Cipher key
  * @param keyLength length of the key. Must be: 8 bytes for DES, 16/24 bytes for 3DES, 16/24/32 bytes for AES
  * @param initialVector Initial vector used for the CBC, CFB and CTR modes, can be null, mandatory in CTR mode, else can be null
  * @param initialVectorLength Initial vector length. Can be 0, fixed length in CBC and CTR modes (8 bytes for DES/3DES, 16 bytes for AES), variable length in CFB mode
  * @param dataIn Data to process
  * @param dataInLength length of Data to process, no length constraint in CFB and CTR modes, length constraint in ECB mode and in CBC mode: 8 bytes multiple for DES/3DES, 16 bytes multiple for AES
  * @param dataOut output buffer
  * @param dataOutLength output buffer length
  * @return A return code indicating the process result
  * <br/>The following codes can be returned:
  * <ul>
  *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS in case of success</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_CRYPTO_MECANISM_INVALID if the mechanism is not managed</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_CRYPTO_MODE_INVALID if the mode is not managed</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_KEY_NULL if the key is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_KEY_INCORRECT_LENGTH if key length is incorrect according to the selected mechanism</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_NULL if the input bytes array is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH if input bytes array length is incorrect according to the selected mechanism</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_INCORRECT_LENGTH if the initial vector length is incorrect according to the selected mechanism</li>
  * </ul>
  */
 SDK_IMPORT(vds_int32) UtilitiesSDK_encrypt(vds_byte mechanism, vds_byte mode, vds_byte* key, vds_int32 keyLength,
		vds_byte* initialVector, vds_int32 initialVectorLength, vds_byte* dataIn, vds_int32 dataInLength,
		vds_byte* dataOut, vds_int32* dataOutLength);

#define UtilitiesSDK_decrypt(...) HAkzVUkcmmaeTTlXtKlM(__VA_ARGS__)
 /**
  * Cipher function to decrypt data
  * @param mechanism Cipher mechanism (CIPHER_MECHANISM_DES, CIPHER_MECHANISM_DES3, CIPHER_MECHANISM_AES)
  * @param mode Cipher mode (CIPHER_MODE_ECB, CIPHER_MODE_CBC, CIPHER_MODE_CFB, CIPHER_MODE_CTR)
  * @param key Cipher key
  * @param keyLength length of the key. Must be: 8 bytes for DES, 16/24 bytes for 3DES, 16/24/32 bytes for AES
  * @param initialVector Initial vector used for the CBC, CFB and CTR modes, can be null, mandatory in CTR mode, else can be null
  * @param initialVectorLength Initial vector length. Can be 0, fixed length in CBC and CTR modes (8 bytes for DES/3DES, 16 bytes for AES), variable length in CFB mode
  * @param dataIn Data to process
  * @param dataInLength length of Data to process, no length constraint in CFB and CTR modes, length constraint in ECB mode and in CBC mode: 8 bytes multiple for DES/3DES, 16 bytes multiple for AES
  * @param dataOut output buffer
  * @param dataOutLength output buffer length
  * @return A return code indicating the process result
  * <br/>The following codes can be returned:
  * <ul>
  *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS in case of success</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_CRYPTO_MECANISM_INVALID if the mechanism is not managed</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_CRYPTO_MODE_INVALID if the mode is not managed</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_KEY_NULL if the key is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_KEY_INCORRECT_LENGTH if key length is incorrect according to the selected mechanism</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_NULL if the input bytes array is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH if input bytes array length is incorrect according to the selected mechanism</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_INCORRECT_LENGTH if the initial vector length is incorrect according to the selected mechanism</li>
  * </ul>
  */
 SDK_IMPORT(vds_int32) UtilitiesSDK_decrypt(vds_byte mechanism, vds_byte mode, vds_byte* key, vds_int32 keyLength,
		vds_byte* initialVector, vds_int32 initialVectorLength, vds_byte* dataIn, vds_int32 dataInLength,
		vds_byte* dataOut, vds_int32* dataOutLength);

#define UtilitiesSDK_deriveKey(...) vAfqjKavovXfBfJwUuVq(__VA_ARGS__)
 /**
  * function to derive a key. It used PBKDF2 algorithm
  * @param mechanism Hash mechanism. Only HASH_SHA_256 is supported...
  * @param key key to derive
  * @param key length of key to derive
  * @param salt salt for derivation
  * @param salt length of salt for derivation
  * @param iterationCount number of iterations
  * @param dataOut output buffer
  * @param dataOutLength length of output buffer
  * @return A return code indicating the process result
  * <br/>The following codes can be returned:
  * <ul>
  *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS in case of success</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_KEY_NULL if the key is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SALT_NULL if the salt is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_ITERATION_COUNT_INCORRECT if the iteration count is equal to 0</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH if output length is equals to 0</li>
  * </ul>
  */
 SDK_IMPORT(vds_int32) UtilitiesSDK_deriveKey(vds_byte mechanism, vds_byte *key, vds_int32 keyLength, vds_byte *salt,
        vds_int32 saltLength, vds_int32 iterationCount, vds_byte* dataOut, vds_int32 dataOutLength);

#define UtilitiesSDK_parseSecureChannelMessage(...) IRbinydlOlxuKjSUNRlK(__VA_ARGS__)
 /**
  * Parse a secure channel message
  * @param message Content of the secure channel message in hexadecimal characters
  * @return A SecureChannelMessage object containing the parsed secure channel message.
  * <br/>The following codes can be returned:
  * <ul>
  *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS in case of success</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NULL if the secure channel message is NULL</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_FORMAT if the secure channel message format is incorrect</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_LENGTH if the secure channel message length is incorrect</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL if the secure channel message structure is null</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_UNKNOWN_ERROR if an unknown error has occurred</li>
  * </ul>
  */
 SDK_IMPORT(vds_int32) UtilitiesSDK_parseSecureChannelMessage(vds_ascii* message,
         UtilitiesSDKSecureChannelMessage* secureChannelMessage);

#define UtilitiesSDK_generateSecureChannelMessage(...) REGywOreDWYyGGxpaWNY(__VA_ARGS__)
 /**
  * Generates a secure channel message
  * @param secureChannelMessage Secure channel message object to serialize
  * @param message OUTPUT Generated message length
  * @param messageLength INPUT/OUTPUT Must be (UTILITIES_SDK_LENGTH_SECURE_CHANNEL_MESSAGE_MAX * 2 + 1), value updated after generation
  * @return An object containing an error code and the generated secure channel message in hexadecimal characters.
  * <br/>The following codes can be returned:
  * <ul>
  *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NULL</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_PROTOCOL_VERSION</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_MESSAGE_TYPE</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_INCORRECT_PROTECTION_TYPE</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER_NULL</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER_INCORRECT_LENGTH</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_SERIAL_NUMBER_INCORRECT_FORMAT</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NONCE_NULL</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NONCE_INCORRECT_LENGTH</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_NONCE_INCORRECT_FORMAT</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_BODY_NULL</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_BODY_INCORRECT_LENGTH</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_BODY_INCORRECT_FORMAT</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_AUTHENTICATION_TAG_NULL</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_AUTHENTICATION_TAG_INCORRECT_LENGTH</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_SECURE_CHANNEL_MESSAGE_AUTHENTICATION_TAG_INCORRECT_FORMAT</li>
  *  <li>UTILITIES_SDK_RETURN_CODE_UNKNOWN_ERROR</li>
  * </ul>
  */
 SDK_IMPORT(vds_int32) UtilitiesSDK_generateSecureChannelMessage(UtilitiesSDKSecureChannelMessage* secureChannelMessage, vds_ascii* message,
         vds_int32* messageLength);

 /**
 * Decrypt strings that have been encrypted with the pre-compilation tool
 * @param dataIn The string to decrypt
 * @return The decrypted string
 */
 SDK_IMPORT(vds_int32) UtilitiesSDK_ikXfulM5lD(vds_ascii* dataIn, vds_ascii* dataOut);

#define UtilitiesSDK_WBC_encryptAESBlock(...) eqTALHhxLxhyKRUTCFSZ(__VA_ARGS__)
 /**
 * This method encrypt a block of data using white box cryptography
 * @param table: WBC table
 * @param tableLength: size of the WBC table
 * @param dataIn: block to encrypt. Must be 16 bytes
 * @param dataOut: encrypted block. Must be 16 bytes
 * <br/>The following codes can be returned:
 * <ul>
 *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_WBC_INPUT_ARRAY_INVALID</li>
 * </ul>
 */
SDK_IMPORT(void) UtilitiesSDK_WBC_encryptAESBlock(vds_byte *table,
                                                  size_t tableLength,
                                                  vds_byte (*dataIn)[16],
                                                  vds_byte (*dataOut)[16]);

#define UtilitiesSDK_WBC_encrypt(...) ImYkFkeQLYBEmAgETgws(__VA_ARGS__)
 /**
 * encrypt method using white box 
 * @param table: WBC table
 * @param tableLength: size of the WBC table
 * @param initialVector initial vector to use
 * @param initialVectorLength initial vector length
 * @param dataIn data to encrypt
 * @param dataInLength data length
 * @param dataOut result of the encryption
 * @param dataOutLength length of the encryption result
 * <br/>The following codes can be returned:
 * <ul>
 *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_NULL
 *  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_NULL</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL</li>
 * </ul>
 */
SDK_IMPORT(vds_int32) UtilitiesSDK_WBC_encrypt(const vds_byte *table,
                                               const size_t tableLength,
                                               const vds_byte * initialVector,
                                               const vds_int32 initialVectorLength,
                                               const vds_byte *  dataIn,
                                               const vds_int32 dataInLength,
                                               vds_byte *  dataOut,
                                               const vds_int32 * dataOutLength);

#define UtilitiesSDK_WBC_decrypt(...) JKgXXAdsYGRgHgpDQlNC(__VA_ARGS__)
/**
* encrypt method using white box
* @param table: WBC table
* @param tableLength: size of the WBC table
* @param initialVector initial vector to use
* @param initialVectorLength initial vector length
* @param dataIn data to encrypt
* @param dataInLength data length
* @param dataOut result of the encryption
* @param dataOutLength length of the encryption result
* <br/>The following codes can be returned:
* <ul>
*  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS</li>
*  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_NULL
*  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_INCORRECT_LENGTH</li>
*  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_NULL</li>
*  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH</li>
*  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL</li>
*  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_NULL</li>
* </ul>
*/
SDK_IMPORT(vds_int32) UtilitiesSDK_WBC_decrypt(const vds_byte *table,
                                               const size_t tableLength,
                                               const vds_byte * initialVector,
                                               const vds_int32 initialVectorLength,
                                               const vds_byte *  dataIn,
                                               const vds_int32 dataInLength,
                                               vds_byte *  dataOut,
                                               const vds_int32 * dataOutLength);

#define UtilitiesSDK_WBC_encryptAESCTRWithMasterKey(...) VeBwZTYdgdVoCWClVrhN(__VA_ARGS__)
 /**
 * encrypt method using white box and the master key
 * @param initialVector initial vector, byte array of length 16
 * @param initialVector initial vector to use
 * @param initialVectorLength initial vector length
 * @param dataIn data to encrypt
 * @param dataInLength data length
 * @param dataOut result of the encryption
 * @param dataOutLength length of the encryption result
 * <br/>The following codes can be returned:
 * <ul>
 *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_WBC_INPUT_ARRAY_INVALID</li>
 * </ul>
 */
SDK_IMPORT(vds_int32) UtilitiesSDK_WBC_encryptAESCTRWithMasterKey(const vds_byte * initialVector,
        const vds_int32 initialVectorLength,
        const vds_byte * dataIn,
        const vds_int32 dataInLength,
        vds_byte * dataOut,
        const vds_int32 * dataOutLength);

#define UtilitiesSDK_WBC_decryptAESCTRWithMasterKey(...) WDkZuBdPJrXDtMtnOOCd(__VA_ARGS__)
 /**
 * decrypt method using white box and the master key
 * @param initialVector initial vector, byte array of length 16
 * @param initialVector initial vector to use
 * @param initialVectorLength initial vector length
 * @param dataIn data to encrypt
 * @param dataInLength data length
 * @param dataOut result of the encryption
 * @param dataOutLength length of the encryption result
 * <br/>The following codes can be returned:
 * <ul>
 *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_INPUT_DATA_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_INITIAL_VECTOR_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_WBC_INPUT_ARRAY_INVALID</li>
 * </ul>
 */
SDK_IMPORT(vds_int32) UtilitiesSDK_WBC_decryptAESCTRWithMasterKey(const vds_byte * initialVector,
        const vds_int32 initialVectorLength,
        const vds_byte * dataIn,
        const vds_int32 dataInLength,
        vds_byte * dataOut,
        const vds_int32 * dataOutLength);

#define UtilitiesSDK_generateRandomByteArray(...) imfbVrVkzNEgDseuEArk(__VA_ARGS__)
 /**
 * Generates a random byte array
 * @param length length of the output to generate
 * @param dataOut generated byte array
 * @return An object containing an error code and the generated random byte array.
 * <br/>The following codes can be returned:
 * <ul>
 *  <li>UTILITIES_SDK_RETURN_CODE_SUCCESS</li>
 *  <li>UTILITIES_SDK_RETURN_CODE_OUTPUT_DATA_INCORRECT_LENGTH</li>
 * </ul>
 */
 SDK_IMPORT(vds_int32) UtilitiesSDK_generateRandomByteArray(const vds_int32 length, vds_byte * const dataOut);

#define UtilitiesSDK_isPasswordWeak(...) qoTRjuVLANmTuclFwBuy(__VA_ARGS__)
 /**
 * Checks the password weakness.
 * @param password Password to check
 * @return True in the following cases
 * <ul>
 * <li>The password is null or empty.</li>
 * <li>The password contains less than four characters.</li>
 * <li>The difference between each consecutive characters is constant.</li>
 * <li>The password contains a row of 0s (N-1 0s for a PIN of N digits) followed by a number (e.g. 00003) or a number followed by a row of 0s (e.g. 2000).</li>
 * </ul>
 */
SDK_IMPORT(vds_bool) UtilitiesSDK_isPasswordWeak(vds_ascii* password);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif
