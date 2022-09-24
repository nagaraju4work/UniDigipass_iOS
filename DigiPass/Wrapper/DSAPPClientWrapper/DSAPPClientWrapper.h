//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

#import <DSAPP_Client/DSAPPConstants.h>
#import <DSAPP_Client/DSAPPErrorCodes.h>
#import "NSError+DSAPPWrapper.h"
#import "SRPSessionKeyResponseWrapper.h"
#import "SRPClientEphemeralKeyResponseWrapper.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * Provides the entry points of the DSAPP client library:
 * <ul>
 *  <li>validation of the checksum of the shared secret (e.g. activation password or authorization code);</li>
 *  <li>initialization of the protocol by generating required data from the shared secret received from the server;</li>
 *  <li>generation of the session key;</li>
 *  <li>decryption of encrypted data;</li>
 *  <li>validation of MAC received from the server.</li>
 * </ul>
 * <br/>The following sequence diagram describes the integration of the DSAPP:<br/><br/>
 * \image html DSAPP_sequence_diagram.png
 */
@interface DSAPPClientWrapper : NSObject

/**
 * @return version of DSAPP Client
 */
+ (NSString *)DSAPPClient_VERSION;

/**
 * Validates the checksum of the user password used in SRP protocol.
 *
 * @param userPassword User password. Alphanumeric string, from {@link DSAPPConstants_SRP_PWD_MIN_LENGTH} to {@link DSAPPConstants_SRP_PWD_MAX_LENGTH} characters.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPErrorCodes_SRP_PASSWORD_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_PASSWORD_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_CHECKSUM_VALIDATION_FAILED}</li>
 *  <li>{@link DSAPPErrorCodes_INTERNAL_ERROR}</li>
 * </ul>
 */
+ (BOOL)validateSRPUserPasswordChecksum:(NSString *)userPassword error:(NSError **)error;

/**
 * Generates the SRP client public and private ephemeral keys.
 *
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPErrorCodes_INTERNAL_ERROR}</li>
 * </ul>
 * @return response A response object that contains:
 * <ul>
 *  <li>The client public ephemeral key. A {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} max length hexadecimal string. Must be sent to the server. Must be stored on the client side and used for SRP session key generation.</li>
 *  <li>The client private ephemeral key. A {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} max length hexadecimal string. Must be stored on the client side and used for SRP session key generation.</li>
 * </ul>
 */
+ (SRPClientEphemeralKeyResponseWrapper * _Nullable)generateSRPClientEphemeralKeyWithError:(NSError **)error;

/**
 * Generates the SRP session key and the client evidence message.
 *
 * @param clientEphemeralPublicKey Client ephemeral public key. Hexadecimal string, maximum {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} characters. Has been calculated by generateSRPClientEphemeralKey method.
 * @param clientEphemeralPrivateKey Client ephemeral private key. Hexadecimal string, maximum {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} characters. Has been calculated by generateSRPClientEphemeralKey method.
 * @param serverEphemeralPublicKey Server ephemeral public key. Hexadecimal string, maximum {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} characters. Received from the server.
 * @param userIdentity User identity. String, from {@link DSAPPConstants_SRP_USER_ID_MIN_LENGTH} to {@link DSAPPConstants_SRP_USER_ID_MAX_LENGTH} characters.
 * @param userPassword User password. Alphanumeric string, from {@link DSAPPConstants_SRP_PWD_MIN_LENGTH} to {@link DSAPPConstants_SRP_PWD_MAX_LENGTH} characters.
 * @param salt Salt. Hexadecimal string of length {@link DSAPPConstants_SRP_SALT_LENGTH}. Received from the server.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INVALID}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_INVALID}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_PRIVATE_KEY_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_INVALID}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SERVER_EPHEMERAL_KEY_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_USER_ID_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_USER_ID_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SALT_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SALT_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SALT_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_PASSWORD_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_PASSWORD_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_INTERNAL_ERROR}</li>
 * </ul>
 * @return response A response object that contains:
 * <ul>
 *  <li>The session key. A {@link DSAPPConstants_SRP_SESSION_KEY_LENGTH} length hexadecimal string. Must be stored on the client side and used for SRP server evidence message validation and SRP decryption.</li>
 *  <li>The client evidence message. A {@link DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH} length hexadecimal string. Must be sent to the server. Must be stored on the client side and used for SRP server evidence message validation.</li>
 * </ul>
 */
+ (SRPSessionKeyResponseWrapper * _Nullable)generateSRPSessionKeyWithClientEphemeralPublicKey:(NSString *)clientEphemeralPublicKey
                                                                    clientEphemeralPrivateKey:(NSString *)clientEphemeralPrivateKey
                                                                     serverEphemeralPublicKey:(NSString *)serverEphemeralPublicKey
                                                             registrationIdentifier:(NSString *)registrationIdentifier
                                                                           activationPassword:(NSString *)activationPassword
                                                                                         salt:(NSString *)salt
                                                                                        error:(NSError **)error;

/**
 * Verifies the server evidence message
 *
 * @param clientEphemeralPublicKey Client ephemeral public key. Hexadecimal string, maximum {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH} characters. Has been calculated by generateSRPClientEphemeralKey method.
 * @param clientEvidenceMessage Client evidence message. Hexadecimal string of length {@link DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH}. Has been calculated by generateSRPSessionKey method.
 * @param serverEvidenceMessage Server evidence message. Hexadecimal string of length {@link DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH}. Has been received from server.
 * @param sessionKey Session key. Hexadecimal string of length {@link DSAPPConstants_SRP_SESSION_KEY_LENGTH}. Has been calculated by generateSRPSessionKey method.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INVALID}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_EPHEMERAL_KEY_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_MESSAGE_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_MESSAGE_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_CLIENT_MESSAGE_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SERVER_MESSAGE_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SERVER_MESSAGE_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SERVER_MESSAGE_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MESSAGE_VERIFICATION_FAILED}</li>
 *  <li>{@link DSAPPErrorCodes_INTERNAL_ERROR}</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
+ (BOOL)verifySRPServerEvidenceMessageWithClientEphemeralPublicKey:(NSString *)clientEphemeralPublicKey
                                             clientEvidenceMessage:(NSString *)clientEvidenceMessage
                                             serverEvidenceMessage:(NSString *)serverEvidenceMessage
                                                  clientSessionKey:(NSString *)clientSessionKey
                                                             error:(NSError **)error;

/**
 * Decrypts the SRP data.
 *
 * @param clientSessionKey Session key. Hexadecimal string of length {@link DSAPPConstants_SRP_SESSION_KEY_LENGTH}. Has been calculated by generateSRPSessionKey method.
 * @param encryptedData Encrypted data. Hexadecimal string. Has been received from server.
 * @param encryptionCounter Encryption counter. Hexadecimal string of length {@link DSAPPConstants_SRP_ENCRYPTION_COUNTER_LENGTH}. Has been received from server.
 * @param mac MAC. Hexadecimal string of length {@link DSAPPConstants_SRP_MAC_LENGTH}. Has been received from server.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_ENCRYPTED_DATA_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_ENCRYPTED_DATA_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_ENCRYPTION_COUNTER_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_ENCRYPTION_COUNTER_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_ENCRYPTION_COUNTER_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_VERIFICATION_FAILED}</li>
 *  <li>{@link DSAPPErrorCodes_DECRYPTED_DATA_NULL}</li>
 *  <li>{@link DSAPPErrorCodes_DECRYPTED_DATA_LENGTH_NULL}</li>
 *  <li>{@link DSAPPErrorCodes_DECRYPTED_DATA_LENGTH_TOO_SMALL}</li>
 *  <li>{@link DSAPPErrorCodes_INTERNAL_ERROR}</li>
 * </ul>
 * @return Decrypted data. byte array containing the decrypted data.
 * {@link DSAPPErrorCodes_DECRYPTED_DATA_LENGTH_TOO_SMALL} and sets decryptedDataBufferLength with the size required to hold in the decrypted data.
 * It should be at least half the value of encryptedData. After the decryption, this value is set to exactly half the value of encryptedData.
 */
+ (NSString * _Nullable)decryptSRPDataWithClientSessionKey:(NSString *)clientSessionKey
                                             encryptedData:(NSString *)encryptedData
                                          encryptedCounter:(NSString *)encryptedCounter
                                                       MAC:(NSString *)MAC
                                                     error:(NSError **)error;

/**
 * Derives the session key, computes the MAC of the input data (HMAC-SHA-256) and verifies the given MAC.
 * @param clientSessionKey Session key. Hexadecimal string of length {@link DSAPPConstants_SRP_SESSION_KEY_LENGTH}. Has been calculated by generateSRPSessionKey method.
 * @param data Input data to check. Byte array containing the data.
 * @param dataLength The size of the input data. Must be different of 0.
 * @param mac MAC of the input data. Hexadecimal string of length {@link DSAPPConstants_SRP_MAC_LENGTH}.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_SESSION_KEY_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_DATA_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_NULL_OR_EMPTY}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_INCORRECT_LENGTH}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_INCORRECT_FORMAT}</li>
 *  <li>{@link DSAPPErrorCodes_SRP_MAC_VERIFICATION_FAILED}</li>
 *  <li>{@link DSAPPErrorCodes_INTERNAL_ERROR}</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
+ (BOOL)verifySRPMACWithClientSessionKey:(NSString *)clientSessionKey
                           bytesToVerify:(NSData *)bytesToVerify
                                     MAC:(NSString *)MAC
                                   error:(NSError **)error;

@end


/*!
 * \mainpage DIGIPASS Software Advanced Provisioning Protocol - Programmer documentation
 * \brief This documentation describes the methods and the constants provided by the DSAPP client C++ library.<br/>
 * <br/>
 * They are exposed by the DSAPPClient class.<br/>
 * <br/>
 * Copyright &copy; since 1999. VASCO DATA SECURITY. All Rights Reserved.
 * @version @release-version@
 */

NS_ASSUME_NONNULL_END
