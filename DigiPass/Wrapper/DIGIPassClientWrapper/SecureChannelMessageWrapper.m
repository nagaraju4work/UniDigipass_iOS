//
//  SecureChannelMessageWrapper.m
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

#import "SecureChannelMessageWrapper.h"

@implementation SecureChannelMessageWrapper

- (instancetype)initWithSecureChannel:(SecureChannelMessage) channelMessage
{
    self = [super init];
    if (self) {
        _protocolVersion = [NSString stringWithFormat:@"%c", channelMessage.protocolVersion];
        _messageType = [NSString stringWithFormat:@"%c", channelMessage.messageType];
        _protectionType = [NSString stringWithFormat:@"%c", channelMessage.protectionType];
        _serialNumber = [NSString stringWithFormat:@"%s", channelMessage.serialNumber];
        _nonce = [NSString stringWithFormat:@"%s", channelMessage.nonce];
        _body = [NSString stringWithFormat:@"%s", channelMessage.body];
        _authenticationTag = [NSString stringWithFormat:@"%s", channelMessage.authenticationTag];
        _rawData = [NSString stringWithFormat:@"%s", channelMessage.rawData];
        _paddingFor8BytesMultiple = [NSString stringWithFormat:@"%s", channelMessage.paddingFor8BytesMultiple];
        NSNumber* number = [NSNumber numberWithInt:channelMessage.encrypted];
        _encrypted = [number boolValue];
        _message = channelMessage;
    }
    return self;
}

@end
