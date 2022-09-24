//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "SRPClientEphemeralKeyResponseWrapper.h"
#import <DSAPP_Client/SRPClientEphemeralKeyResponse.h>

@interface SRPClientEphemeralKeyResponseWrapper (){
    NSString *_clientEphemeralPublicKey;
    NSString *_clientEphemeralPrivateKey;
}

@end

@implementation SRPClientEphemeralKeyResponseWrapper

- (instancetype)initWithSRPClientEphemeralKeyResponse:(SRPClientEphemeralKeyResponse)srpClientEphemeralKeyResponse {
    self = [super init];
    if (self) {
        _clientEphemeralPublicKey = [NSString stringWithUTF8String:srpClientEphemeralKeyResponse.clientEphemeralPublicKey.c_str()];
        _clientEphemeralPrivateKey = [NSString stringWithUTF8String:srpClientEphemeralKeyResponse.clientEphemeralPrivateKey.c_str()];
    }
    return self;
}

- (NSString *)clientEphemeralPublicKey {
    return _clientEphemeralPublicKey;
}

- (NSString *)clientEphemeralPrivateKey {
    return _clientEphemeralPrivateKey;
}

@end
