#import <Foundation/Foundation.h>

//! Project version NSString for DSAPPClient. 
static const NSString * _Nonnull DSAPPClientObjC_VERSION = @"4.29.0";


NS_ASSUME_NONNULL_BEGIN

@class SRPClientEphemeralKeyResponseObjC;
@class SRPSessionKeyResponseObjC;

NS_REFINED_FOR_SWIFT
@interface DSAPPClientObjC : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Validates the checksum of the user password used in SRP protocol.
 *
 * @param userPassword User password. Alphanumeric string, from {@link DSAPPClientConstantsObjC#DSAPPClientConstantsObjC#srpPwdMinLength} to {@link DSAPPClientConstantsObjC#srpPwdMaxLength} characters.
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpPasswordNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpPasswordIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#checksumValidationFailed}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#internalError}</li>
 * </ul>
 * @return true if successuf
 */
+ (BOOL)validateSRPUserPasswordChecksum:(NSString *)userPassword error:(NSError **)error;

/**
 * Generates the SRP client public and private ephemeral keys.
 *
 * @param error raised if there is an error during the process. The following codes can be returned:
 * {@link DSAPPClientErrorCodesObjC#internalError}
 * @return A {@link SRPClientEphemeralKeyResponseObjC} object that contains:
 * <ul>
 *  <li>The client public ephemeral key. A {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} max length hexadecimal string. Must be sent to the server. Must be stored on the client side and used for SRP session key generation.</li>
 *  <li>The client private ephemeral key. A {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} max length hexadecimal string. Must be stored on the client side and used for SRP session key generation.</li>
 * </ul>
 */
+ (SRPClientEphemeralKeyResponseObjC * _Nullable)generateSRPClientEphemeralKeyAndReturnError:(NSError **)error;

/**
 * Generates the SRP session key and the client evidence message.
 *
 * @param clientEphemeralPublicKey Client ephemeral public key. Hexadecimal string, maximum {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} characters. Has been calculated by generateSRPClientEphemeralKey method.
 * @param clientEphemeralPrivateKey Client ephemeral private key. Hexadecimal string, maximum {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} characters. Has been calculated by generateSRPClientEphemeralKey method.
 * @param serverEphemeralPublicKey Server ephemeral public key. Hexadecimal string, maximum {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} characters. Received from the server.
 * @param userIdentity User identity. String, from {@link DSAPPClientConstantsObjC#srpUserIdMinLength} to {@link DSAPPClientConstantsObjC#srpUserIdMaxLength} characters.
 * @param userPassword User password. Alphanumeric string, from {@link DSAPPClientConstantsObjC#srpPwdMinLength} to {@link DSAPPClientConstantsObjC#srpPwdMaxLength} characters.
 * @param salt Salt. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpSaltLength}. Received from the server.
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyInvalid}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientPrivateKeyInvalid}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientPrivateKeyNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientPrivateKeyIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientPrivateKeyIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpServerEphemeralKeyInvalid}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpServerEphemeralKeyNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpServerEphemeralKeyIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpServerEphemeralKeyIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpUserIdNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpUserIdIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSaltNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSaltIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSaltIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpPasswordNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpPasswordIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#internalError}</li>
 * </ul>
 * @return A {@link SRPSessionKeyResponseObjC} object that contains:
 * <ul>
 *  <li>The session key. A {@link DSAPPClientConstantsObjC#srpSessionKeyLength} length hexadecimal string. Must be stored on the client side and used for SRP server evidence message validation and SRP decryption.</li>
 *  <li>The client evidence message. A {@link DSAPPClientConstantsObjC#srpEvidenceMessageLength} length hexadecimal string. Must be sent to the server. Must be stored on the client side and used for SRP server evidence message validation.</li>
 * </ul>
 */
+ (SRPSessionKeyResponseObjC * _Nullable)generateSRPSessionKeyWithClientEphemeralPublicKey:(NSString *)clientEphemeralPublicKey
                                                                 clientEphemeralPrivateKey:(NSString *)clientEphemeralPrivateKey
                                                                  serverEphemeralPublicKey:(NSString *)serverEphemeralPublicKey
                                                                              userIdentity:(NSString *)userIdentity
                                                                              userPassword:(NSString *)userPassword
                                                                                      salt:(NSString *)salt
                                                                                     error:(NSError **)error;

/**
 * Verifies the server evidence message
 *
 * @param clientEphemeralPublicKey Client ephemeral public key. Hexadecimal string, maximum {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} characters. Has been calculated by generateSRPClientEphemeralKey method.
 * @param clientEvidenceMessage Client evidence message. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpEvidenceMessageLength}. Has been calculated by generateSRPSessionKey method.
 * @param serverEvidenceMessage Server evidence message. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpEvidenceMessageLength}. Has been received from server.
 * @param clientSessionKey Session key. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpSessionKeyLength}. Has been calculated by generateSRPSessionKey method.
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyInvalid}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientEphemeralKeyIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientMessageNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientMessageIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpClientMessageIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpServerMessageNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpServerMessageIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpServerMessageIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMessageVerificationFailed}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#internalError}</li>
 * </ul>
 * @return true if successuf
 */
+ (BOOL)verifySRPServerEvidenceMessageWithClientEphemeralPublicKey:(NSString *)clientEphemeralPublicKey
                                             clientEvidenceMessage:(NSString *)clientEvidenceMessage
                                             serverEvidenceMessage:(NSString *)serverEvidenceMessage
                                                  clientSessionKey:(NSString *)clientSessionKey
                                                             error:(NSError **)error;

/**
 * Decrypts the SRP data.
 *
 * @param clientSessionKey Session key. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpSessionKeyLength}. Has been calculated by generateSRPSessionKey method.
 * @param encryptedData Encrypted data. Hexadecimal string. Has been received from server.
 * @param encryptionCounter Encryption counter. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpEncryptionCounterLength}. Has been received from server.
 * @param MAC Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpMacLength}. Has been received from server.
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpEncryptedDataNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpEncryptedDataIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpEncryptionCounterNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpEncryptionCounterIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpEncryptionCounterIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacVerificationFailed}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#internalError}</li>
 * </ul>
 * @return decryptedData string containing the decrypted data.
 */
+ (NSString * _Nullable)decryptSRPDataWithClientSessionKey:(NSString *)clientSessionKey
                                             encryptedData:(NSString *)encryptedData
                                          encryptedCounter:(NSString *)encryptedCounter
                                                       MAC:(NSString *)MAC
                                                     error:(NSError **)error;

/**
 * Derives the session key, computes the MAC of the input data (HMAC-SHA-256) and verifies the given MAC.
 * @param clientSessionKey Session key. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpSessionKeyLength}. Has been calculated by generateSRPSessionKey method.
 * @param bytesToVerify Input data to check. Byte array containing the data.
 * @param MAC of the input data. Hexadecimal string of length {@link DSAPPClientConstantsObjC#srpMacLength}.
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpSessionKeyIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpDataNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacNullOrEmpty}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacIncorrectLength}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpMacVerificationFailed}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#srpDecryptedDataIncorrectFormat}</li>
 *  <li>{@link DSAPPClientErrorCodesObjC#internalError}</li>
 * </ul>
 * @return true if successuf
 */
+ (BOOL)verifySRPMACWithClientSessionKey:(NSString *)clientSessionKey
                           bytesToVerify:(NSData *)bytesToVerify
                                     MAC:(NSString *)MAC
                                   error:(NSError **)error;

@end

@interface NSError (DSAPP)

/**
 * Gets a default error message associated with the error code
 * @return The error message
 */
- (NSString *)dsappMessage;

@end

/*!
 * \mainpage DIGIPASS Software Advanced Provisioning Protocol - Programmer documentation
 * \brief This documentation describes the methods and the constants provided by the DSAPP client Objective C library.<br/>
 * <br/>
 * They are exposed by the DSAPPClient class.<br/>
 * <br/>
 * @OneSpanCopyright
 * @version 4.29.0
 */

NS_ASSUME_NONNULL_END
