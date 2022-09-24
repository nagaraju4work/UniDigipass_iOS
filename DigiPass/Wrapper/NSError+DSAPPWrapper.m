//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "NSError+DSAPPWrapper.h"

static NSString * const kDomain = @"DSAPP";
static NSString * const kMessage = @"message";

@implementation NSError (DSAPPWrapper)

- (instancetype)initWithCode:(NSInteger)errorCode message:(NSString *)message
{
    self = [self initWithDomain:kDomain code:errorCode userInfo:@{kMessage:message}];
    if (self) {
        
    }
    return self;
}

+ (instancetype)newWithCode:(NSInteger)errorCode message:(NSString *)message {
    return [[self alloc] initWithCode:errorCode message:message];
}

- (NSString *)message {
    return self.userInfo[kMessage];
}

@end
