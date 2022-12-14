//
//  SecureChannelMessageWrapper.h
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MSSDigipass/DP4Capi.h>

NS_ASSUME_NONNULL_BEGIN

@interface SecureChannelMessageWrapper : NSObject

- (instancetype)initWithSecureChannel:(SecureChannelMessage) channelMessage;

@property (strong, nonatomic) NSString* protocolVersion;
@property (strong, nonatomic) NSString* messageType;
@property (strong, nonatomic) NSString* protectionType;
@property (strong, nonatomic) NSString* serialNumber;
@property (strong, nonatomic) NSString* nonce;
@property (strong, nonatomic) NSString* body;
@property (strong, nonatomic) NSString* authenticationTag;
@property (strong, nonatomic) NSString* rawData;
@property (assign, nonatomic) BOOL encrypted;
@property (strong, nonatomic) NSString* paddingFor8BytesMultiple;
@property (assign, nonatomic) SecureChannelMessage message;

@end

NS_ASSUME_NONNULL_END
