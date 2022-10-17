//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <MSSDigipass/DigipassSDK.h>

NS_ASSUME_NONNULL_BEGIN

@class DigipassSDKSecureChannelMessage;
@class DigipassSDKMultiDeviceLicenseActivationResponse;
@class DigipassSDKActivationResponse;
@class DigipassSDKGenericResponse;
@class DigipassSDKSignatureResponse;

/**
 * This category of DIgipass SDK describes the Multi Device Activation and the methods linked to the Secure Channel.
 */
@interface DigipassSDK (MultiDeviceActivationAndSecureChannelMethods)

/**
 * Parse a secure channel message.
 *
 * @param message Content of the secure channel message, MANDATORY, from 46 to 1070 hexadecimal characters
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectFormat} if the secure channel message format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectLength} if the secure channel message length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKSecureChannelMessage} object containing:
 * <ul>
 *  <li>The parsed secure channel message</li>
 * </ul>
 */
+ (DigipassSDKSecureChannelMessage *_Nullable)parseSecureChannelMessage:(NSString *)message
                                                                  error:(NSError **)error;

/**
 * First step of the multi-device activation process. License provisioning.
 * <ul>
 *  <li>Checks the input data.</li>
 *  <li>Parses the DIGIPASS settings.</li>
 *  <li>Gets and checks the license activation data.</li>
 *  <li>Generates a device code.</li>
 * </ul>
 * @param secureChannelMessage Secure channel message, contains the license activation data, MANDATORY, see {@link DigipassSDK#parseSecureChannelMessage:error:}
 * @param staticVector Static vector, contains the DIGIPASS settings, OPTIONAL, from 182 to 1916 hexadecimal characters
 * @param platformFingerprint Platform fingerprint used to generate the device code, MANDATORY, no specific length
 * @param jailbreakStatus Jailbreak status, see {@link DigipassSDKConstants#jailbreakStatusNa}, {@link DigipassSDKConstants#jailbreakStatusSafe} and {@link DigipassSDKConstants#jailbreakStatusUnsafe}
 * @param clientServerTimeShift RFU
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectType} if the secure channel message is not a multi-device license activation message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeJailbreakStatusInvalid} if the jailbreak status is invalid</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null as parameter and in the secure channel message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageStaticVectorInconsistent} if the static vector contained in the secure channel message is not equal to the one provided as parameter</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeMultiDeviceActivationDisabled} if the multi-device activation is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformActivationKeyInvalid} if the platform activation key is invalid because it cannot be validated against its checksum</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKMultiDeviceLicenseActivationResponse} object containing:
 * <ul>
 *  <li>The static vector ready to be stored, from 91 to 958 bytes</li>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes</li>
 *  <li>The generated device code</li>
 * </ul>
 */
+ (DigipassSDKMultiDeviceLicenseActivationResponse *_Nullable)multiDeviceActivateLicenseWithSecureChannelMessage:(DigipassSDKSecureChannelMessage *)secureChannelMessage
                                                                                               staticVectorInput:(NSString * _Nullable)staticVectorInput
                                                                                             platformFingerprint:(NSString *)platformFingerprint
                                                                                                 jailbreakStatus:(UInt8)jailbreakStatus
                                                                                           clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                                                                           error:(NSError **)error;

/**
 * Second step of the multi-device activation process with a password. Instance activation.
 * <ul>
 *  <li>Checks the input data.</li>
 *  <li>Parses the DIGIPASS settings.</li>
 *  <li>Checks the data contained in the secure channel message.</li>
 *  <li>Gets the instance activation data.</li>
 *  <li>Extracts DIGIPASS secrets from the instance activation data and encrypts them by using a key derived from the password.</li>
 * </ul>
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes
 * @param secureChannelMessage Secure channel message, contains the instance activation data, MANDATORY, see {@link DigipassSDK#parseSecureChannelMessage:error:}
 * @param password Password (as bytes) used to encrypt DIGIPASS secrets, MANDATORY if the password is required in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordMandatory})
 * @param platformFingerprint Platform fingerprint used for the secrets encryption, MANDATORY, no specific length
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectType} if the secure channel message is not a multi-device license activation message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageSignatureInvalid} if the signature of the secure channel message is invalid</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null as parameter and in the secure channel message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeMultiDeviceActivationDisabled} if the multi-device activation is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the DIGIPASS status is not {@link DigipassSDKConstants#statusPreActivated}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeLicenseIncorrect} if the DIGIPASS license is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectTarget} if the secure channel message is not dedicated to the current DIGIPASS</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordNull} if the password is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooShort} if the password is too short</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooLong} if the password is too long</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordWeak} if the password is weak</li>
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
 * @return A {@link DigipassSDKActivationResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes</li>
 * </ul>
 */
+ (DigipassSDKActivationResponse *_Nullable)multiDeviceActivateInstanceWithStaticVector:(NSData *)staticVector
                                                                          dynamicVector:(NSData *)dynamicVector
                                                                   secureChannelMessage:(DigipassSDKSecureChannelMessage *)secureChannelMessage
                                                                               password:(char * _Nullable)password
                                                                    platformFingerprint:(NSString *)platformFingerprint
                                                                                  error:(NSError **)error;

/**
 * Second step of the multi-device activation process with an encryption key. Instance activation.
 * <ul>
 *  <li>Checks the input data.</li>
 *  <li>Parses the DIGIPASS settings.</li>
 *  <li>Checks the data contained in the secure channel message.</li>
 *  <li>Gets the activation data.</li>
 *  <li>Extracts DIGIPASS secrets from the activation data and encrypts them by using the encryptionKey.</li>
 * </ul>
 * @param encryptionKey Encryption key used to encrypt DIGIPASS secrets, MANDATORY, 16 bytes
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes
 * @param secureChannelMessage Secure channel message, contains the activation data, MANDATORY, see {@link DigipassSDK#parseSecureChannelMessage:error:}
 * @param platformFingerprint Platform fingerprint used for the secrets encryption, MANDATORY, no specific length
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectType} if the secure channel message is not a multi-device license activation message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageSignatureInvalid} if the signature of the secure channel message is invalid</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null as parameter and in the secure channel message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeMultiDeviceActivationDisabled} if the multi-device activation is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the DIGIPASS status is not {@link DigipassSDKConstants#statusPreActivated}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeLicenseIncorrect} if the DIGIPASS license is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectTarget} if the secure channel message is not dedicated to the current DIGIPASS</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeEncryptionKeyNull} if the encryption key is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeEncryptionKeyIncorrectLength} if the encryption key length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKActivationResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes</li>
 * </ul>
 */
+ (DigipassSDKActivationResponse *_Nullable)multiDeviceActivateInstanceWithKey:(NSData * _Nullable)encryptionKey
                                                                  staticVector:(NSData *)staticVector
                                                                 dynamicVector:(NSData *)dynamicVector
                                                          secureChannelMessage:(DigipassSDKSecureChannelMessage *)secureChannelMessage
                                                           platformFingerprint:(NSString *)platformFingerprint
                                                                         error:(NSError **)error;

/**
 * Checks and decrypts the body of a secure channel message.
 * @param secureChannelMessage Secure channel message, MANDATORY, not a  multi-device license activation message nor a multi-device instance activation message, see {@link DigipassSDK#parseSecureChannelMessage:error:}, {@link DigipassSDKConstants#secureChannelMessageTypeLicenseActivation} and {@link DigipassSDKConstants#secureChannelMessageTypeInstanceActivation}
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes
 * @param platformFingerprint Platform fingerprint used for the secrets encryption, MANDATORY, no specific length
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectType} if the secure channel message is not a multi-device license activation message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageSignatureInvalid} if the signature of the secure channel message is invalid</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null as parameter and in the secure channel message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeMultiDeviceActivationDisabled} if the multi-device activation is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeLicenseIncorrect} if the DIGIPASS license is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelDisabled} if the secure channel is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the DIGIPASS cannot be be used because of its status (not activated or locked)</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown error has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKGenericResponse} object containing:
 * <ul>
 *  <li>The secure channel message body</li>
 * </ul>
 */
+ (DigipassSDKGenericResponse *_Nullable)decryptSecureChannelMessageBody:(DigipassSDKSecureChannelMessage *)secureChannelMessage
                                                            staticVector:(NSData *)staticVector
                                                           dynamicVector:(NSData *)dynamicVector
                                                     platformFingerprint:(NSString *)platformFingerprint
                                                                   error:(NSError **)error;

/**
 * Generate a signature from the secure channel message with a password.
 * @param secureChannelMessage Secure channel message of activation or request type, MANDATORY, see {@link DigipassSDK#parseSecureChannelMessage:error:}, {@link DigipassSDKConstants#secureChannelMessageTypeInstanceActivation} and {@link DigipassSDKConstants#secureChannelMessageTypeRequest}
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes
 * @param password Password (as bytes) used to decrypt DIGIPASS secrets, MANDATORY if the password is required in the DIGIPASS settings (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:} and {@link DigipassPropertiesResponse#passwordProtected})
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the response, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used for the secrets encryption, MANDATORY, no specific length
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectType} if the secure channel message is not an activation or a request message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeProtectionTypeNotSupported} if the secure channel message signature has no protection type</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeMultiDeviceActivationDisabled} if the multi-device activation is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeLicenseIncorrect} if the DIGIPASS license is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the status is invalid (not activated or locked), an activation is required</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordNull} if the password is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooShort} if the password is too short</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLengthTooLong} if the password is too long</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordLock} if the application is locked after too many wrong tries</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePasswordWrong} if the password is cannot be validated</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeNotPasswordProtected} if the DIGIPASS is not password protected</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the Digipass settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeCharacterInvalid} if one of the data to sign contains invalid characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldsNumberInvalid} if the number of data fields to sign is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldIncorrectLength} if one of the data fields to sign length is incorrect </li>
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
 *  <li>The generated host code, if the host code is enabled for the crypto application (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:}, {@link DigipassPropertiesResponse.applications} and {@link DigipassSDKApplication#hostCodeLength})</li>
 * </ul>
 */
+ (DigipassSDKSignatureResponse *_Nullable)generateSignatureFromSecureChannelMessage:(DigipassSDKSecureChannelMessage *)secureChannelMessage
                                                                        staticVector:(NSData *)staticVector
                                                                       dynamicVector:(NSData *)dynamicVector
                                                                            password:(char * _Nullable)password
                                                               clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                              cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                                 platformFingerprint:(NSString *)platformFingerprint
                                                                               error:(NSError **)error;

/**
 * Generate a signature from the secure channel message with an encryption key.
 * @param secureChannelMessage Secure channel message of activation or request type, MANDATORY, see {@link DigipassSDK#parseSecureChannelMessage:error:}, {@link DigipassSDKConstants#secureChannelMessageTypeInstanceActivation} and {@link DigipassSDKConstants#secureChannelMessageTypeRequest}
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes
 * @param encryptionKey Encryption key used to decrypt the DIGIPASS secrets, MANDATORY, 16 bytes
 * @param clientServerTimeShift Client/Server time shift in seconds, OPTIONAL, recommended if the application to use is time-based, else must be 0, use {@link DigipassSDK#computeClientServerTimeShiftFromServerTime:} to compute this value
 * @param cryptoApplicationIndex Crypto application index, indicates which application must be used to generate the response, MANDATORY, from {@link DigipassSDKConstants#cryptoApplicationIndexApp1} to {@link DigipassSDKConstants#cryptoApplicationIndexApp8}
 * @param platformFingerprint Platform fingerprint used for the secrets encryption, MANDATORY, no specific length
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageNull} if the secure channel message is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageIncorrectType} if the secure channel message is not an activation or a request message</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeProtectionTypeNotSupported} if the secure channel message signature has no protection type</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorNull} if the static vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectLength} if the static vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStaticVectorIncorrectFormat} if the static vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorNull} if the dynamic vector is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectLength} if the dynamic vector length is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDynamicVectorIncorrectFormat} if the dynamic vector format is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeMultiDeviceActivationDisabled} if the multi-device activation is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeLicenseIncorrect} if the DIGIPASS license is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeEncryptionKeyNull} if the encryption key is null</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeEncryptionKeyIncorrectLength} if the encryption key length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeStatusInvalid} if the status is invalid (not activated or locked), an activation is required</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeCryptoApplicationIndexInvalid} if the crypto application index is invalid</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeApplicationDisabled} if the crypto application is disabled in the Digipass settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeChallengeCharacterInvalid} if one of the data to sign contains invalid characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldsNumberInvalid} if the number of data fields to sign is incorrect</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeDataFieldIncorrectLength} if one of the data fields to sign length is incorrect </li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKSignatureResponse} object containing:
 * <ul>
 *  <li>The dynamic vector ready to be stored, from 80 to 303 bytes</li>
 *  <li>The generated response (signature)</li>
 *  <li>The generated host code, if the host code is enabled for the crypto application (see {@link DigipassSDK#digipassPropertiesWithStaticVector:dynamicVector:error:}, {@link DigipassPropertiesResponse.applications} and {@link DigipassSDKApplication#hostCodeLength})</li>
 * </ul>
 */
+ (DigipassSDKSignatureResponse *_Nullable)generateSignatureFromSecureChannelMessage:(DigipassSDKSecureChannelMessage *)secureChannelMessage
                                                                        staticVector:(NSData *)staticVector
                                                                       dynamicVector:(NSData *)dynamicVector
                                                                       encryptionKey:(NSData *)encryptionKey
                                                               clientServerTimeShift:(NSInteger)clientServerTimeShift
                                                              cryptoApplicationIndex:(NSInteger)cryptoApplicationIndex
                                                                 platformFingerprint:(NSString *)platformFingerprint
                                                                               error:(NSError **)error;

/**
 * Generate a secure channel information message. The message can be secured using the payload key of the dynamic vector.
 *
 * @param secureChannelMessageBody Message to send to the server as an hexadecimal string, MANDATORY, cannot be null nor empty, length must not exceed 1024 hexadecimal characters. This string will be converted to uppercase.
 * @param staticVector Static vector, contains the DIGIPASS settings, MANDATORY, from 91 to 958 bytes
 * @param dynamicVector Dynamic vector, contains DIGIPASS data, MANDATORY, from 80 to 303 bytes
 * @param protectionType type of protection used to secure the message. Two types of protection are supported:
 * <ul>
 *  <li>{@link DigipassSDKConstants#secureChannelMessageProtectionNone}, the message is not protected.</li>
 *  <li>{@link DigipassSDKConstants#secureChannelMessageProtectionHmacAesctr}, HMAC-SHA256 along with AES-CTR are used to guarantee data origin authentication and confidentiality</li>
 * </ul>
 * @param platformFingerprint Platform fingerprint used for the DIGIPASS secrets encryption, MANDATORY, no specific length
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DigipassSDKErrorCodes#returnCodePlatformFingerprintNotDefined} if the platform fingerprint is not defined</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeProtectionTypeNotSupported} if the protection type is neither {@link DigipassSDKConstants#secureChannelMessageProtectionNone} nor {@link DigipassSDKConstants#secureChannelMessageProtectionHmacAesctr}</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageBodyNullOrEmpty} if the secure channel message body is null or empty</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageBodyIncorrectFormat} if the secure channel message body is not an hexadecimal string</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelMessageBodyIncorrectLength} if the secure channel message body does no have an even length or is longer than 1024 hexadecimal characters</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeSecureChannelDisabled} if the secure channel is disabled in the DIGIPASS settings</li>
 *  <li>{@link DigipassSDKErrorCodes#returnCodeUnknownError} if an unknown has occurred</li>
 * </ul>
 * @return A {@link DigipassSDKSecureChannelMessage} object containing:
 * <ul>
 *  <li>The generated secure channel message</li>
 * </ul>
 */
+ (DigipassSDKSecureChannelMessage *_Nullable)generateSecureChannelInformationMessageWithBody:(NSString *)secureChannelMessageBody
                                                                               protectionType:(UInt8)protectionType
                                                                                 staticVector:(NSData *)staticVector
                                                                                dynamicVector:(NSData *)dynamicVector
                                                                          platformFingerprint:(NSString *)platformFingerprint
                                                                                        error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
