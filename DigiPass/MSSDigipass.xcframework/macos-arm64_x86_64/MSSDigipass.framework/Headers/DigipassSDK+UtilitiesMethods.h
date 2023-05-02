//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <MSSDigipass/DigipassSDK.h>

NS_ASSUME_NONNULL_BEGIN

@class DigipassSDKManageApplicationResponse;
@class DigipassSDKGenerateDerivationCodeResponse;
@class DigipassPropertiesResponse;

/**
 * This category of DIgipass SDK describes multiple utilities methods.
 */
@interface DigipassSDK (UtilitiesMethods)

/**
 * Enable a crypto application
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the derivation code, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, OPTIONAL, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the status is invalid (not activated or locked), an activation is required</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid, use {@link DigipassSDKConstants#cryptoApplicationIndexApp1} ... {@link DigipassSDKConstants#cryptoApplicationIndexApp8}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKManageApplicationResponse} object containing an error code and the updated dynamic vector.
 */
+ (DigipassSDKManageApplicationResponse * _Nullable)enableApplicationWithIndex:(NSInteger)cryptoApplicationIndex
                                                                  staticVector:(NSData *)staticVector
                                                                 dynamicVector:(NSData *)dynamicVector
                                                                         error:(NSError **)error;

/**
 * Disable a crypto application
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the derivation code, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, OPTIONAL, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the status is invalid (not activated or locked), an activation is required</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid, use {@link DigipassSDKConstants#cryptoApplicationIndexApp1} ... {@link DigipassSDKConstants#cryptoApplicationIndexApp8}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKManageApplicationResponse} object containing an error code and the updated dynamic vector.
 */
+ (DigipassSDKManageApplicationResponse * _Nullable)disableApplicationWithIndex:(NSInteger)cryptoApplicationIndex
                                                                   staticVector:(NSData *)staticVector
                                                                  dynamicVector:(NSData *)dynamicVector
                                                                          error:(NSError **)error;

/**
 * Generates a derivation code.
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, OPTIONAL, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param password Password (as bytes) used to decrypt DIGIPASS secrets, MANDATORY if the password is required in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordProtected})
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the derivation code, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used to generate the derivation code, MANDATORY, no specific length
 * @param challenge Challenge which could used to generate the derivation code if the used crypto application is challenge/response, up to 16 valid characters, OPTIONAL, length defined in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:}, {@link DigipassSDKApplication#dataFieldsMinLength} and {@link DigipassSDKApplication#dataFieldsMaxLength})
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the status is invalid (not activated or locked), an activation is required</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordNull} if the password is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLock} if the application is locked after too many wrong tries</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordWrong} if the password is cannot be validated</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeNotPasswordProtected} if the DIGIPASS is not password protected</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid, use {@link DigipassSDKConstants#cryptoApplicationIndexApp1} ... {@link DigipassSDKConstants#cryptoApplicationIndexApp8}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeNull} if the challenge is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeIncorrectLength} if the challenge length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeCharacterInvalid} if one of the data to sign contains invalid characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeTokenDerivationNotSupported} if the token derivation is not supported</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * \warning Passwords are used as char* to prevent unecessary copies of the password in memory.
 *  We **strongly** encourage you to reset your byte buffer as soon as possible using the following example
 *   @code
 *    char password[] = "password";
 *    // ...
 *    memset(password, 0, strlen(password));
 *   @endcode
 *   
 * @return A {@link DigipassSDKGenerateDerivationCodeResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})</li>
 *  <li>The attempt left if the password validation failed and if the password fatal counter is enabled in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordFatal})</li>
 *  <li>The generated derivation code</li>
 * </ul>
 */
+ (DigipassSDKGenerateDerivationCodeResponse * _Nullable)generateDerivationCodeWithStaticVector:(NSData *)staticVector
                                                                                  dynamicVector:(NSData *)dynamicVector
                                                                                       password:(char * _Nullable)password
                                                                          clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                                         cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                                            platformFingerprint:(NSString *)platformFingerprint
                                                                                      challenge:(NSString * _Nullable)challenge
                                                                                          error:(NSError **)error;

/**
 * Generates a derivation code with an encryption key.
 * @param encryptionKey Encryption key used to decrypt the DIGIPASS secrets, MANDATORY, 16 bytes
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, OPTIONAL, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the derivation code, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used to generate the derivation code, MANDATORY, no specific length
 * @param challenge Challenge which could used to generate the derivation code if the used crypto application is challenge/response, up to 16 valid characters, OPTIONAL, length defined in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:}, {@link DigipassSDKApplication#dataFieldsMinLength} and {@link DigipassSDKApplication#dataFieldsMaxLength})
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the status is invalid (not activated or locked), an activation is required</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeEncryptionKeyNull} if the encryption key is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeEncryptionKeyIncorrectLength} if the encryption key length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid, use {@link DigipassSDKConstants#cryptoApplicationIndexApp1} ... {@link DigipassSDKConstants#cryptoApplicationIndexApp8}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeNull} if the challenge is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeIncorrectLength} if the challenge length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeCharacterInvalid} if one of the data to sign contains invalid characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeTokenDerivationNotSupported} if the token derivation is not supported</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKGenerateDerivationCodeResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})</li>
 *  <li>The attempt left if the password validation failed and if the password fatal counter is enabled in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordFatal})</li>
 *  <li>The generated derivation code</li>
 * </ul>
 */
+ (DigipassSDKGenerateDerivationCodeResponse * _Nullable)generateDerivationCodeWithKey:(NSData *)encryptionKey
                                                                          staticVector:(NSData *)staticVector
                                                                         dynamicVector:(NSData *)dynamicVector
                                                                 clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                                cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                                   platformFingerprint:(NSString *)platformFingerprint
                                                                             challenge:(NSString * _Nullable)challenge
                                                                                 error:(NSError **)error;

/**
 * Gets the DIGIPASS properties from the static and dynamic vectors
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, OPTIONAL, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassPropertiesResponse} object containing an error code and the digipass properties
 */
+ (DigipassPropertiesResponse * _Nullable)digipassPropertiesWithStaticVector:(NSData *)staticVector
                                                               dynamicVector:(NSData * _Nullable)dynamicVector
                                                                       error:(NSError **)error;

/**
 * Gets the DIGIPASS properties from the XFAD
 * @param xfad Encrypted Full Activation Data, contains the activation data, MANDATORY, from 205 to 1738 hexadecimal characters (from 139 to 166 characters if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeXfadNull} if the XFAD is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeXfadIncorrectLength} if the XFAD length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeXfadIncorrectFormat} if the XFAD format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassPropertiesResponse} object containing the digipass properties
 */
+ (DigipassPropertiesResponse * _Nullable)digipassPropertiesWithXFAD:(NSString *)xfad
                                                               error:(NSError **)error;

/**
 * Gets the message associated with a return code.
 * @param returnCode Return code
 * @return The message associated with the return code
 */
+ (NSString *)messageForReturnCode:(NSInteger)returnCode;

/**
 * Computes the client server time shift by using the server time and the client UTC times (timeShift = serverTime - clientTime)
 * <br/><b>WARNING: </b>The time shift computing method has been changed since the previous SDK version (3.x or older).
 * <br/>In the old SDK version (3.x or older), timeShift = clientTime - serverTime (VDS_UtilsPublic.getCSTimeShiftFromServerTime)
 * @param serverTimeInSeconds Server time in seconds
 * @return Client server time shift in seconds
 */
+ (NSInteger)computeClientServerTimeShiftFromServerTime:(NSInteger)serverTimeInSeconds;

@end

NS_ASSUME_NONNULL_END
