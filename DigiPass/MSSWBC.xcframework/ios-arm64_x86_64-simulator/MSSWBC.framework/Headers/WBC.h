#import <Foundation/Foundation.h>
#import <MSSWBC/WBCTableContainer.h>

NS_ASSUME_NONNULL_BEGIN

#define WBCSDK_VERSION  @"4.27.0"

//! Project version number for WBCSDK.
FOUNDATION_EXPORT double WBCSDKVersionNumber;

//! Project version string for WBCSDK.
FOUNDATION_EXPORT const unsigned char WBCSDKVersionString[];

@interface WBC : NSObject

/**
 * This method encrypts data using White Box Cryptography.
 * @param   mechanism Cipher mechanism ({@link CRYPTO_MECHANISM_AES} only supported).
 * @param   mode Cipher mode ({@link CRYPTO_MODE_CTR} only supported).
 * @param   initialVector NSNumber array containing the initial vector. Initial vector used for the CTR modes, mandatory.
 *          For {@link CRYPTO_MECHANISM_AES} and{@link CRYPTO_MODE_CTR}, it must be 16 bytes long.
 * @param   dataIn NSData containing clear data to be encrypted. Cannot be null or empty.
 * @param   table The encryption table wrapped into a WBCTableContainer
 * @param   error A NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link WBCSDK_TABLES_INVALID} if White box tables are null or invalid.</li>
 *  <li>{@link CRYPTO_MECHANISM_INVALID} if crypto mechanism is invalid.</li>
 *  <li>{@link CRYPTO_MODE_INVALID} if crypto mode is invalid.</li>
 *  <li>{@link INITIAL_VECTOR_NULL} if initial vector is null.</li>
 *  <li>{@link INITIAL_VECTOR_INCORRECT_LENGTH} if initial vector has an incorrect length.</li>
 *  <li>{@link INPUT_DATA_NULL} if input data is null.</li>
 *  <li>{@link INPUT_DATA_INCORRECT_LENGTH} if input data length is incorrect.</li>
 *  <li>{@link OUTPUT_DATA_NULL} if output data has an incorrect length.</li>
 *  <li>{@link OUTPUT_DATA_INCORRECT_LENGTH} if output data is null.</li>
 *  <li>{@link INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 * @return NSData containing the encrypted data. If an error occurred the reason will be put in the error.
 */
+ (NSData *_Nullable)encryptWithMechanism:(const unsigned char)mechanism
                                     mode:(const unsigned char)mode
                            initialVector:(NSArray<NSNumber *>*)initialVector
                                   dataIn:(NSData *)dataIn
                                    table:(WBCTableContainer*)container
                                    error:(NSError **)error;

/**
 * This method decrypts data using White Box Cryptography.
 * @param   mechanism Cipher mechanism ({@link CRYPTO_MECHANISM_AES} only supported).
 * @param   mode Cipher mode ({@link CRYPTO_MODE_CTR} only supported)
 * @param   initialVector NSNumber array containing the initial vector. Initial vector used for the CTR modes, mandatory.
 *          For {@link CRYPTO_MECHANISM_AES} and{@link CRYPTO_MODE_CTR}, it must be 16 bytes long.
 * @param   dataIn NSData containing encrypted data to be decrypted. Cannot be null or empty.
 * @param   table The encryption table wrapped into a WBCTableContainer 
 * @param   error A NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link WBCSDK_TABLES_INVALID} if White box tables are null or invalid.</li>
 *  <li>{@link CRYPTO_MECHANISM_INVALID} if crypto mechanism is invalid.</li>
 *  <li>{@link CRYPTO_MODE_INVALID} if crypto mode is invalid.</li>
 *  <li>{@link INITIAL_VECTOR_NULL} if initial vector is null.</li>
 *  <li>{@link INITIAL_VECTOR_INCORRECT_LENGTH} if initial vector has an incorrect length.</li>
 *  <li>{@link INPUT_DATA_NULL} if input data is null.</li>
 *  <li>{@link INPUT_DATA_INCORRECT_LENGTH} if input data length is incorrect.</li>
 *  <li>{@link OUTPUT_DATA_NULL} if output data has an incorrect length.</li>
 *  <li>{@link OUTPUT_DATA_INCORRECT_LENGTH} if output data is null.</li>
 *  <li>{@link INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 * @return NSData containing the clear data. If an error occurred the reason will be put in the error.
 */
+ (NSData *_Nullable)decryptWithMechanism:(const unsigned char)mechanism
                                     mode:(const unsigned char)mode
                            initialVector:(NSArray<NSNumber *>*)initialVector
                                   dataIn:(NSData *)dataIn
                                    table:(WBCTableContainer*)container
                                    error:(NSError **)error;

NS_ASSUME_NONNULL_END

@end

/*!
 * \mainpage White Box Cryptography SDK - Programmer documentation
 * \brief This documentation describes the methods and the constants provided by the WBC SDK.<br/>
 * <br/>
 * They are exposed by the WBC class.<br/>
 * <br/>
 * @OneSpanCopyright
 * \version 4.27.0
 */
