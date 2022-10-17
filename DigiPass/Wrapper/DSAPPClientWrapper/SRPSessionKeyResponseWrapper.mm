//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "SRPSessionKeyResponseWrapper.h"
#import <MSSDSAPPClient/SRPSessionKeyResponse.h>

@interface SRPSessionKeyResponseWrapper (){
    NSString *_sessionKey;
    NSString *_clientEvidenceMessage;
}

@end

@implementation SRPSessionKeyResponseWrapper

- (instancetype)initWithSRPSessionKeyResponse:(SRPSessionKeyResponse)srpSessionKeyResponse {
    self = [super init];
    if (self) {
        _sessionKey = [NSString stringWithUTF8String:srpSessionKeyResponse.sessionKey.c_str()];
        _clientEvidenceMessage = [NSString stringWithUTF8String:srpSessionKeyResponse.clientEvidenceMessage.c_str()];
    }
    return self;
}

- (NSString *)sessionKey {
    return _sessionKey;
}

- (NSString *)clientEvidenceMessage {
    return _clientEvidenceMessage;
}

@end
