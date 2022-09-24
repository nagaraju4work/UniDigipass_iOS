//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Response class used to store the elements resulting of SRP client ephemeral key generation.
 * The GenerateSRPClientEphemeralKeyResponse object is returned by {@link DSAPPClient#generateSRPClientEphemeralKey}.
 */
@interface SRPClientEphemeralKeyResponseWrapper : NSObject

/** The SRP private ephemeral key. Hexadecimal string of size inferior or equal to {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH}.
 * Must be stored on the client side and used for the SRP session key generation.
 */
@property(nonatomic, copy, readonly) NSString *clientEphemeralPrivateKey;

/** The SRP public ephemeral key. Hexadecimal string of size inferior or equal to {@link DSAPPConstants_SRP_EPHEMERAL_KEY_MAX_LENGTH}.
 * Must be sent to the server and stored on the client side to be used for the SRP session key generation and the server message verification.
 */
@property(nonatomic, copy, readonly) NSString *clientEphemeralPublicKey;

@end

NS_ASSUME_NONNULL_END
