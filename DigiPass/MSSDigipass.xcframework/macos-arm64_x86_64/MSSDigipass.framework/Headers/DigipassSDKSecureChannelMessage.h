//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This class represents a secure channel message.
 */
NS_REFINED_FOR_SWIFT
@interface DigipassSDKSecureChannelMessage : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Protocol version
@property (nonatomic, readonly) UInt8 protocolVersion;

/** Message type, see the types listed below:<br>
 * {@link DigipassSDKConstants#secureChannelMessageTypeLicenseActivation}<br>
 * {@link DigipassSDKConstants#secureChannelMessageTypeInstanceActivation}<br>
 * {@link DigipassSDKConstants#secureChannelMessageTypeDeactivation}<br>
 * {@link DigipassSDKConstants#secureChannelMessageTypeRequest}<br>
 * {@link DigipassSDKConstants#secureChannelMessageTypeResponse}<br>
 * {@link DigipassSDKConstants#secureChannelMessageTypeInformationMessage}<br>
 */
@property (nonatomic, readonly) UInt8 messageType;

/** Protection type, see the types listed below:<br>
 * {@link DigipassSDKConstants#secureChannelMessageProtectionNone}<br>
 * {@link DigipassSDKConstants#secureChannelMessageProtectionHmacAesctr}<br>
 * {@link DigipassSDKConstants#secureChannelMessageProtectionHmac}<br>
 */
@property (nonatomic, readonly) UInt8 protectionType;

/// Serial number
@property (nonatomic, copy, readonly) NSString *serialNumber;

/// Nonce
@property (nonatomic, copy, readonly) NSString *nonce;

/** Body, can be encrypted, see {@link DigipassSDKSecureChannelMessage#encrypted} and {@link DigipassSDK#decryptSecureChannelMessageBody:staticVector:dynamicVector:platformFingerprint:error:} */
@property (nonatomic, copy, readonly) NSString *body;

/// Authentication tag, used as a checksum to validate the message content
@property (nonatomic, copy, readonly) NSString *authenticationTag;

/// Raw data of the message
@property (nonatomic, copy, readonly) NSString *rawData;

/// Indicates whether the body is encrypted
@property (nonatomic, readonly) BOOL encrypted;


@property (nonatomic, copy, readonly) NSData *paddingFor8BytesMultiple;

@end

NS_ASSUME_NONNULL_END
