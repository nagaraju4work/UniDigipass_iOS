#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
/**
 * Response class used to store the elements resulting of SRP client ephemeral key generation.
 * The SRPSessionKeyResponseObjC object is returned by {@link DSAPPClientObjC#generateSRPSessionKeyWithClientEphemeralPublicKey:clientEphemeralPrivateKey:serverEphemeralPublicKey:userIdentity:userPassword:salt:error:}.
 */
@interface SRPSessionKeyResponseObjC : NSObject

/** The SRP session key. {@link DSAPPClientConstantsObjC#srpSessionKeyLength} hexadecimal string. Must be stored on the client side and used for the data decryption. */
@property(nonatomic, copy, readonly) NSString *sessionKey;

/** The SRP client evidence message. {@link DSAPPClientConstantsObjC#srpEvidenceMessageLength} hexadecimal string. Must be sent to the server. */
@property(nonatomic, copy, readonly) NSString *clientEvidenceMessage;

@end

NS_ASSUME_NONNULL_END
