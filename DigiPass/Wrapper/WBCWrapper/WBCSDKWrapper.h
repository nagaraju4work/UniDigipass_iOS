//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const WBCSDK_VERSION;

@interface WBCSDKWrapper : NSObject

/**
 * This method encrypts data using White Box Cryptography.
 * @param   mechanism Cipher mechanism ({@link WBCSDKConstants::CRYPTO_MECHANISM_AES} only supported).
 * @param   mode Cipher mode ({@link WBCSDKConstants::CRYPTO_MODE_CTR} only supported).
 * @param   initialVector NSNumber array containing the initial vector. Initial vector used for the CTR modes, mandatory.
 *          For {@link WBCSDKConstants::CRYPTO_MECHANISM_AES} and{@link WBCSDKConstants::CRYPTO_MODE_CTR}, it must be 16 bytes long.
 * @param   dataIn NSData containing clear data to be encrypted. Cannot be null or empty.
 * @param   error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link WBCSDKErrorCodes::WBCSDK_TABLES_INVALID} if White box tables are null or invalid.</li>
 *  <li>{@link WBCSDKErrorCodes::CRYPTO_MECHANISM_INVALID} if crypto mechanism is invalid.</li>
 *  <li>{@link WBCSDKErrorCodes::CRYPTO_MODE_INVALID} if crypto mode is invalid.</li>
 *  <li>{@link WBCSDKErrorCodes::INITIAL_VECTOR_NULL} if initial vector is null.</li>
 *  <li>{@link WBCSDKErrorCodes::INITIAL_VECTOR_INCORRECT_LENGTH} if initial vector has an incorrect length.</li>
 *  <li>{@link WBCSDKErrorCodes::INPUT_DATA_NULL} if input data is null.</li>
 *  <li>{@link WBCSDKErrorCodes::INPUT_DATA_INCORRECT_LENGTH} if input data length is incorrect.</li>
 *  <li>{@link WBCSDKErrorCodes::OUTPUT_DATA_NULL} if output data has an incorrect length.</li>
 *  <li>{@link WBCSDKErrorCodes::OUTPUT_DATA_INCORRECT_LENGTH} if output data is null.</li>
 *  <li>{@link WBCSDKErrorCodes::INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 * @return NSData containing the encrypted data. If an error occurred the reason will be put in the error.
 */
+ (NSData *_Nullable)encrypt:(const unsigned char)mechanism mode:(const unsigned char)mode initialVector:(NSArray<NSNumber *>*)initialVector dataIn:(NSData *)dataIn error:(NSError **)error;

/**
 * This method decrypts data using White Box Cryptography.
 * @param   mechanism Cipher mechanism ({@link WBCSDKConstants::CRYPTO_MECHANISM_AES} only supported).
 * @param   mode Cipher mode ({@link WBCSDKConstants::CRYPTO_MODE_CTR} only supported)
 * @param   initialVector NSNumber array containing the initial vector. Initial vector used for the CTR modes, mandatory.
 *          For {@link WBCSDKConstants::CRYPTO_MECHANISM_AES} and{@link WBCSDKConstants::CRYPTO_MODE_CTR}, it must be 16 bytes long.
 * @param   dataIn NSData containing encrypted data to be decrypted. Cannot be null or empty.
 * @param   error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link WBCSDKErrorCodes::WBCSDK_TABLES_INVALID} if White box tables are null or invalid.</li>
 *  <li>{@link WBCSDKErrorCodes::CRYPTO_MECHANISM_INVALID} if crypto mechanism is invalid.</li>
 *  <li>{@link WBCSDKErrorCodes::CRYPTO_MODE_INVALID} if crypto mode is invalid.</li>
 *  <li>{@link WBCSDKErrorCodes::INITIAL_VECTOR_NULL} if initial vector is null.</li>
 *  <li>{@link WBCSDKErrorCodes::INITIAL_VECTOR_INCORRECT_LENGTH} if initial vector has an incorrect length.</li>
 *  <li>{@link WBCSDKErrorCodes::INPUT_DATA_NULL} if input data is null.</li>
 *  <li>{@link WBCSDKErrorCodes::INPUT_DATA_INCORRECT_LENGTH} if input data length is incorrect.</li>
 *  <li>{@link WBCSDKErrorCodes::OUTPUT_DATA_NULL} if output data has an incorrect length.</li>
 *  <li>{@link WBCSDKErrorCodes::OUTPUT_DATA_INCORRECT_LENGTH} if output data is null.</li>
 *  <li>{@link WBCSDKErrorCodes::INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 * @return NSData containing the clear data. If an error occurred the reason will be put in the error.
 */
+ (NSData *_Nullable)decrypt:(const unsigned char)mechanism mode:(const unsigned char)mode initialVector:(NSArray<NSNumber *>*)initialVector dataIn:(NSData *)dataIn error:(NSError **)error;

NS_ASSUME_NONNULL_END

@end
