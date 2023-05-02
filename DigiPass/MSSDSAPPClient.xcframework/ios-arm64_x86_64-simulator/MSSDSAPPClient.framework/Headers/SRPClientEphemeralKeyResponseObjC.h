#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
/**
 * Response class used to store the elements resulting of SRP client ephemeral key generation.
 * The SRPClientEphemeralKeyResponseObjC object is returned by {@link DSAPPClientObjC#generateSRPClientEphemeralKeyAndReturnError:}.
 */
@interface SRPClientEphemeralKeyResponseObjC : NSObject

/** The SRP private ephemeral key. Hexadecimal string of size inferior or equal to {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength}.
 * Must be stored on the client side and used for the SRP session key generation.
 */
@property(nonatomic, copy, readonly) NSString *clientEphemeralPrivateKey;

/** The SRP public ephemeral key. Hexadecimal string of size inferior or equal to {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength}.
 * Must be sent to the server and stored on the client side to be used for the SRP session key generation and the server message verification.
 */
@property(nonatomic, copy, readonly) NSString *clientEphemeralPublicKey;

@end

NS_ASSUME_NONNULL_END
