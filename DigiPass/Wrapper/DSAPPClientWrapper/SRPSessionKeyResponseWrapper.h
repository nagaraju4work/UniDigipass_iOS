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
 * The GenerateSRPSessionKeyResponse object is returned by {@link DSAPPClient#generateSRPClientEphemeralKey}.
 */
@interface SRPSessionKeyResponseWrapper : NSObject

/** The SRP session key. {@link DSAPPConstants_SRP_SESSION_KEY_LENGTH} hexadecimal string. Must be stored on the client side and used for the data decryption. */
@property(nonatomic, copy, readonly) NSString *sessionKey;

/** The SRP client evidence message. {@link DSAPPConstants_SRP_EVIDENCE_MESSAGE_LENGTH} hexadecimal string. Must be sent to the server. */
@property(nonatomic, copy, readonly) NSString *clientEvidenceMessage;

@end

NS_ASSUME_NONNULL_END
