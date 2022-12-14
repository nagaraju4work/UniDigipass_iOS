//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <MSSSecureStorage/MSSSecureStorage.h>
#import <MSSSecureStorage/SecureStorageSDKErrorCodes.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This class provides mecanisms to create a storage, add and remove value, write and delete storage file
 */
@interface SecureStorageSDKWrapper : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Initializes a new storage instance by reading an existing storage if available.
 * @param filename Storage file name. Must not be null nor empty, the max length is 100 and it can only contain alphanumeric characters (along with "-", "_" and ".").
 * @param fingerprint Data used to secure the storage. It should be a device-dependent data. Can be null.
 * @param iterationNumber Indicates the power of the storage encryption. Once set must not be changed. Must be greater than 0.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_STORAGE_NAME_NULL if the storage file name is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_STORAGE_NAME_INCORRECT_LENGTH if the storage file name has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_STORAGE_NAME_INCORRECT_FORMAT if the storage file name contains invalid characters. It can only contain alphanumeric characters (along wit “-“, “_” and “.”) (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_UNREADABLE_STORAGE if the storage is not readable (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_ITERATION_COUNT_INCORRECT if the iteration number is incorrect, Must be >0 (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_STORAGE_CORRUPTED if the storage is corrupted (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return A SecureStorageSDKWrapper instance, If an error occurred the reason will be put in the error.
 */
- (instancetype _Nullable)initWithFileName:(NSString *)filename useFingerPrint:(NSString * _Nullable) fingerprint andIterationNumber:(int)iterationNumber error:(NSError **)error;

/**
 * Writes the storage in the device's persistent memory.
 * @param fingerprint Used to generate an encryption key. Can be null.
 * @param iterationNumber Number of loops used to calculate the encryption key. Must be > 0.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_ITERATION_COUNT_INCORRECT if the iteration number is incorrect, Must be >0 (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
- (BOOL)writeWithFingerprint:(NSString * _Nullable)fingerprint andIterationNumber:(int)iterationNumber error:(NSError **)error;

/**
 * Puts a string into the storage. If the key already exists, the value is updated.
 * @param key Used to identify a storage value. Must not be null nor empty, the max length is 100} and it can only contain alphanumeric characters.
 * @param value String to store. Must not be null and cannot contain characters "¨" and "§".
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_NULL if the key is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_LENGTH if the key has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_FORMAT if the key contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_VALUE_NULL if the value is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_VALUE_INCORRECT_FORMAT if the value contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
- (BOOL)putStringForValue:(NSString *)value forKey:(NSString *)key error:(NSError **)error;

/**
 * Puts a string into the storage. If the key already exists, the value is updated.
 * @param key Used to identify a storage value. Must not be null nor empty, the max length is 100} and it can only contain alphanumeric characters.
 * @param value Bytes array to store. Must not be null.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_NULL if the key is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_LENGTH if the key has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_FORMAT if the key contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_VALUE_NULL if the value is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_VALUE_INCORRECT_FORMAT if the value contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
- (BOOL)putBytesForBytes:(NSData *)value forKey:(NSString *)key error:(NSError **)error;

/**
 * Removes a value from the storage.
 * @param key Key to retrieve value. Must not be null, must not be empty, key.length() must be <= 100} and can only contain alphanumeric characters.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_NULL if the key is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_LENGTH if the key has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_FORMAT if the key contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_UNKNOWN_KEY if the key is unknown (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
- (BOOL)removeForKey:(NSString *)key error:(NSError **)error;

/**
 * Gets a string from the storage.
 * @param key Key to retrieve value. Must not be null, must not be empty, key.length() must be <= 100} and can only contain alphanumeric characters.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_NULL if the key is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_LENGTH if the key has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_FORMAT if the key contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_UNKNOWN_KEY if the key is unknown (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_INCORRECT_GETTER if the requested value is a bytes array (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return The string value, If an error occurred the reason will be put in the error.
 */
- (NSString *_Nullable)getStringForKey:(NSString *)key error:(NSError **)error;

/**
 * Gets a bytes array from the storage.
 * @param key Key to retrieve value. Must not be null, must not be empty, key.length() must be <= 100} and can only contain alphanumeric characters.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_NULL if the key is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_LENGTH if the key has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_FORMAT if the key contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_UNKNOWN_KEY if the key is unknown (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_INCORRECT_GETTER if the requested value is a bytes array (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return The bytes array value, If an error occurred the reason will be put in the error.
 */
- (NSData *_Nullable)getBytesForKey:(NSString *)key error:(NSError **)error;

/**
 * Gets all the data from the storage.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return The data contained in the storage, If an error occurred the reason will be put in the error.
 */
- (NSDictionary * _Nullable)getAllWithError:(NSError **)error;

/**
 * Deletes a Secure Storage instance.
 * @param filename Name of the data file. Must not be null, must not be empty, filename.length() must be <= 100 and can only contain alphanumeric characters (along with "-" and "_").
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_STORAGE_NAME_NULL if the storage file name is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_STORAGE_NAME_INCORRECT_LENGTH if the storage file name has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_STORAGE_NAME_INCORRECT_FORMAT if the storage file name contains invalid characters. Must be alphanumeric (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_UNKNOWN_STORAGE if the storage does not exist (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
+ (BOOL)deleteWithFileName:(NSString *)filename error:(NSError **)error;

/**
 * Returns true if this storage contains a mapping for the specified key
 * @param key The key whose presence in this storage is to be tested. Must not be null, must not be empty, key.length() must be <= 100} and can only contain alphanumeric characters.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_NULL if the key is null (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_LENGTH if the key has an incorrect length (see SecureStorageSDKErrorCodes.h).</li>
 *  <li>SecureStorageSDKErrorCodes_KEY_INCORRECT_FORMAT if the key contains invalid characters (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return True if this storage contains a mapping for the specified key, If an error occurred the reason will be put in the error.
 */
- (BOOL)containsKey:(NSString *)key error:(NSError **)error;

/**
 * Remove all of the data from this storage. The storage will be empty after this call returns.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>SecureStorageSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see SecureStorageSDKErrorCodes.h).</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
- (BOOL)clearWithError:(NSError **)error;

/**
 * Return if the Secure Storage SDK support the hardware protection.
 * @return bool true if the Secure Storage support hardware protection, false otherwise.
 */
+ (BOOL)isProtectedBySecureHardware;

@end

NS_ASSUME_NONNULL_END
