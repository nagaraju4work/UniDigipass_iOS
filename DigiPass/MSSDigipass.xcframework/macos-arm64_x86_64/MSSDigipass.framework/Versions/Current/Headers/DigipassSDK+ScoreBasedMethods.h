//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <MSSDigipass/DigipassSDK.h>

NS_ASSUME_NONNULL_BEGIN

@class DigipassSDKGenerationResponse;
@class DigipassSDKSignatureResponse;
@class DigipassSDKSecureChannelMessage;

/**
 * This category of DIgipass SDK describes the Score Based methods.
 */
@interface DigipassSDK (ScoreBasedMethods)

/**
 * Response Only process.
 * <ul>
 *  <li>Validates the password.</li>
 *  <li>Generates a score-based OTP.</li>
 *  <li>Updates the application data (status and counters) according to the validation and generation results.</li>
 * </ul>
 * @param score Score generated between 0 and 7
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the response, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used for the DIGIPASS secrets encryption and for the token derivation if supported, OPTIONAL but strongly recommended, no specific length, must be null if not used.<br/>
 * The platform fingerprint is used to perform the token derivation only if the {@link DigipassSDK#generateDerivationCodeWithStaticVector:dynamicVector:password:clientServerTimeShift:cryptoApplicationIndex:platformFingerprint:challenge:error:} has already been called.<br/>
 * For a DIGIPASS created by a DIGIPASS SDK 4.0 (<=> {@link DigipassPropertiesResponse#creationVersion} < 3), the platform fingerprint is used to perform the token derivation even if if the {@link DigipassSDK#generateDerivationCodeWithStaticVector:dynamicVector:password:clientServerTimeShift:cryptoApplicationIndex:platformFingerprint:challenge:error:} has not been called.
 * @param password Password (as bytes) used to decrypt DIGIPASS secrets, MANDATORY if the password is required in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordProtected})
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordNull} if the password is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooShort} if the password is too short</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooLong} if the password is too long</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLock} if the application is locked after too many wrong tries</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordWrong} if the password is cannot be validated</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeNotPasswordProtected} if the DIGIPASS is not password protected</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid, use {@link DigipassSDKConstants#cryptoApplicationIndexApp1} ... {@link DigipassSDKConstants#cryptoApplicationIndexApp8}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeClientScoreDisabled} if the Client Score feature is disabled</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeScoreInvalid} if the score value is not between 0 and 7</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown has occurred</li>
 * </ul>
 * \warning Passwords are used as char* to prevent unecessary copies of the password in memory.
 *  We **strongly** encourage you to reset your byte buffer as soon as possible using the following example
 *   @code
 *    char password[] = "password";
 *    // ...
 *    memset(password, 0, strlen(password));
 *   @endcode
 *
 * @return A {@link DigipassSDKGenerationResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})</li>
 *  <li>The attempt left if the password validation failed and if the password fatal counter is enabled in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordFatal})</li>
 *  <li>The generated response (OTP)</li>
 *  <li>The generated host code, if the host code is enabled for the crypto application (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassSDKApplication#hostCodeLength})</li>
 * </ul>
 */
+ (DigipassSDKGenerationResponse * _Nullable)generateResponseOnlyWithScore:(UInt8)score
                                                              staticVector:(NSData *)staticVector
                                                             dynamicVector:(NSData *)dynamicVector
                                                     clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                    cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                       platformFingerprint:(NSString * _Nullable)platformFingerprint
                                                                  password:(char * _Nullable)password
                                                                     error:(NSError **)error;

/**
 * Challenge Response process.
 * <ul>
 *  <li>Validates the password.</li>
 *  <li>Generates a score-based response by signing the challenge.</li>
 *  <li>Updates the application data (status and counters) according to the validation and generation results.</li>
 * </ul>
 * @param score Score generated between 0 and 7
 * @param challenge Challenge to sign, up to 16 valid characters, MANDATORY can be empty but not null, length defined in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:}, {@link DigipassSDKApplication#dataFieldsMinLength} and {@link DigipassSDKApplication#dataFieldsMaxLength})
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param password Password (as bytes) used to decrypt DIGIPASS secrets, MANDATORY if the password is required in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordProtected})
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the response, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used for the DIGIPASS secrets encryption and for the token derivation if supported, OPTIONAL but strongly recommended, no specific length, must be null if not used.<br/>
 * The platform fingerprint is used to perform the token derivation only if the {@link DigipassSDK#generateDerivationCodeWithStaticVector:dynamicVector:password:clientServerTimeShift:cryptoApplicationIndex:platformFingerprint:challenge:error:} has already been called.<br/>
 * For a DIGIPASS created by a DIGIPASS SDK 4.0 (<=> {@link DigipassPropertiesResponse#creationVersion} < 3), the platform fingerprint is used to perform the token derivation even if if the {@link DigipassSDK#generateDerivationCodeWithStaticVector:dynamicVector:password:clientServerTimeShift:cryptoApplicationIndex:platformFingerprint:challenge:error:} has not been called.
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordNull} if the password is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooShort} if the password is too short</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooLong} if the password is too long</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLock} if the application is locked after too many wrong tries</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordWrong} if the password is cannot be validated</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeNotPasswordProtected} if the DIGIPASS is not password protected</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid, use {@link DigipassSDKConstants#cryptoApplicationIndexApp1} ... {@link DigipassSDKConstants#cryptoApplicationIndexApp8}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeNull} if the challenge is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeIncorrectLength} if the challenge length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeCharacterInvalid} if one of the data to sign contains invalid characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeClientScoreDisabled} if the Client Score feature is disabled</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeScoreInvalid} if the score value is not between 0 and 7</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown has occurred</li>
 * </ul>
 * \warning Passwords are used as char* to prevent unecessary copies of the password in memory.
 *  We **strongly** encourage you to reset your byte buffer as soon as possible using the following example
 *   @code
 *    char password[] = "password";
 *    // ...
 *    memset(password, 0, strlen(password));
 *   @endcode
 *
 * @return A {@link DigipassSDKGenerationResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})</li>
 *  <li>The attempt left if the password validation failed and if the password fatal counter is enabled in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordFatal})</li>
 *  <li>The generated response (OTP)</li>
 *  <li>The generated host code, if the host code is enabled for the crypto application (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassSDKApplication#hostCodeLength})</li>
 * </ul>
 */
+ (DigipassSDKGenerationResponse * _Nullable)generateResponseFromChallengeWithScore:(UInt8)score
                                                                          challenge:(NSString *)challenge
                                                                       staticVector:(NSData *)staticVector
                                                                      dynamicVector:(NSData *)dynamicVector
                                                                           password:(char * _Nullable)password
                                                              clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                             cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                                platformFingerprint:(NSString * _Nullable)platformFingerprint
                                                                              error:(NSError **)error;

/**
 * Signature process.
 * <ul>
 *  <li>Validates the password.</li>
 *  <li>Generates a score-based signature by signing the data fields.</li>
 *  <li>Updates the application data (status and counters) according to the validation and generation results.</li>
 * </ul>
 * @param score Score generated between 0 and 7
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})
 * @param dataFields Data fields to sign, up to 8 strings having up to 16 valid characters, the array length must not exceed the data fields number contained in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:}, DigipassSDKApplication#dataFieldNumber, {@link DigipassSDKApplication#dataFieldsMinLength} and {@link DigipassSDKApplication#dataFieldsMaxLength})
 * @param password Password (as bytes) used to decrypt DIGIPASS secrets, MANDATORY if the password is required in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordProtected})
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the response, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used for the DIGIPASS secrets encryption and for the token derivation if supported, OPTIONAL but strongly recommended, no specific length, must be null if not used.<br/>
 * The platform fingerprint is used to perform the token derivation only if the {@link DigipassSDK#generateDerivationCodeWithStaticVector:dynamicVector:password:clientServerTimeShift:cryptoApplicationIndex:platformFingerprint:challenge:error:} has already been called.<br/>
 * For a DIGIPASS created by a DIGIPASS SDK 4.0 (<=> {@link DigipassPropertiesResponse#creationVersion} < 3), the platform fingerprint is used to perform the token derivation even if if the {@link DigipassSDK#generateDerivationCodeWithStaticVector:dynamicVector:password:clientServerTimeShift:cryptoApplicationIndex:platformFingerprint:challenge:error:} has not been called.
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordNull} if the password is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooShort} if the password is too short</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooLong} if the password is too long</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLock} if the application is locked after too many wrong tries</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordWrong} if the password is cannot be validated</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeNotPasswordProtected} if the DIGIPASS is not password protected</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid, use {@link DigipassSDKConstants#cryptoApplicationIndexApp1} ... {@link DigipassSDKConstants#cryptoApplicationIndexApp8}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldsArrayNull} if the data fields array is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldsNumberInvalid} if the number of data fields to sign is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldNull} if one of the data fields to sign is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldIncorrectLength} if one of the data fields to sign length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldsNotContiguous} if one of the data fields is empty between two not empty data fields</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeCharacterInvalid} if one of the data to sign contains invalid characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeClientScoreDisabled} if the Client Score feature is disabled</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeScoreInvalid} if the score value is not between 0 and 7</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown has occurred</li>
 * </ul>
 * \warning Passwords are used as char* to prevent unecessary copies of the password in memory.
 *  We **strongly** encourage you to reset your byte buffer as soon as possible using the following example
 *   @code
 *    char password[] = "password";
 *    // ...
 *    memset(password, 0, strlen(password));
 *   @endcode
 *
 * @return A {@link DigipassSDKSignatureResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes (56 if static vector version < 8, see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#version})</li>
 *  <li>The attempt left if the password validation failed and if the password fatal counter is enabled in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordFatal})</li>
 *  <li>The generated response (signature)</li>
 *  <li>The generated host code, if the host code is enabled for the crypto application (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassSDKApplication#hostCodeLength})</li>
 * </ul>
 */
+ (DigipassSDKSignatureResponse *_Nullable)generateSignatureWithScore:(UInt8)score
                                                         staticVector:(NSData *)staticVector
                                                        dynamicVector:(NSData *)dynamicVector
                                                           dataFields:(NSArray<NSString *>*)dataFields
                                                             password:(char * _Nullable)password 
                                                clientServerTimeShift:(NSInteger)clientServerTimeShift
                                               cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                  platformFingerprint:(NSString * _Nullable)platformFingerprint
                                                                error:(NSError **)error;

/**
 * Generate a signature from the secure channel message with a password.
 * @param secureChannelMessage Secure channel message of activation or request type, MANDATORY, see {@link DigipassSDK#parseSecureChannelMessage:error:, {@link DigipassSDKConstants#secureChannelMessageTypeInstanceActivation} and {@link DigipassSDKConstants#secureChannelMessageTypeRequest}
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes
 * @param password Password (as bytes) used to decrypt DIGIPASS secrets, MANDATORY if the password is required in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordProtected})
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the response, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used for the secrets encryption, MANDATORY, no specific length
 * @param score Score generated between 0 and 7
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectType} if the secure channel message is not an activation or a request message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeProtectionTypeNotSupported} if the secure channel message signature has no protection type</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeMultiDeviceActivationDisabled} if the multi-device activation is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeLicenseIncorrect} if the DIGIPASS license is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordNull} if the password is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooShort} if the password is too short</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooLong} if the password is too long</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLock} if the application is locked after too many wrong tries</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordWrong} if the password is cannot be validated</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeNotPasswordProtected} if the DIGIPASS is not password protected</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeCharacterInvalid} if one of the data to sign contains invalid characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldsNumberInvalid} if the number of data fields to sign is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldIncorrectLength} if one of the data fields to sign length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeClientScoreDisabled} if the Client Score feature is disabled</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeScoreInvalid} if the score value is not between 0 and 7</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown has occurred</li>
 * </ul>
 * \warning Passwords are used as char* to prevent unecessary copies of the password in memory.
 *  We **strongly** encourage you to reset your byte buffer as soon as possible using the following example
 *   @code
 *    char password[] = "password";
 *    // ...
 *    memset(password, 0, strlen(password));
 *   @endcode
 *   
 * @return A {@link DigipassSDKSignatureResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes</li>
 *  <li>The generated response (signature)</li>
 *  <li>The generated host code, if the host code is enabled for the crypto application (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassSDKApplication#hostCodeLength})</li>
 * </ul>
 */
+ (DigipassSDKSignatureResponse *_Nullable)generateSignatureFromSecureChannelMessage:(DigipassSDKSecureChannelMessage *)secureChannelMessage
                                                             staticVector:(NSData *)staticVector
                                                            dynamicVector:(NSData *)dynamicVector
                                                                 password:(char * _Nullable)password
                                                    clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                   cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                      platformFingerprint:(NSString *)platformFingerprint
                                                                    score:(UInt8)score
                                                                    error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
