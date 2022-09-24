//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "SecureStorageSDKWrapper.h"
#import <SecureStorageSDK/SecureStorageSDKException.h>
#import <FirebaseAnalytics/FirebaseAnalytics.h>

static NSString *const kDomain = @"SecureStorageSDK";
static NSString *const kMessage = @"message";

@interface SecureStorageSDKWrapper (){
    SecureStorageSDK *_secureStorage;
}

@end


@implementation SecureStorageSDKWrapper

- (instancetype)initWithFileName:(NSString *)filename useFingerPrint:(NSString *) fingerprint andIterationNumber:(int)iterationNumber error:(NSError**)error {
    self = [super init];
    if (self) {
        @try {
            _secureStorage = [[SecureStorageSDK alloc] initWithFileName:filename useFingerPrint:fingerprint andIterationNumber:iterationNumber];
        }
        @catch (SecureStorageSDKException *e) {
            NSString * message = e.exception ? e.exception.reason : @"";
            *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
            [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperInit"
                                parameters:@{
                                             @"error":  e.reason
                                             }];
            return nil;
        }
    }
    return self;
}

- (BOOL)writeWithFingerprint:(NSString *)fingerPrint andIterationNumber:(int)iterationNumber error:(NSError**)error {
    @try {
        [_secureStorage writeWithFingerPrint:fingerPrint andIterationNumber:iterationNumber];
        return TRUE;
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        return FALSE;
    }
}

- (BOOL)putStringForValue:(NSString *)value forKey:(NSString *)key error:(NSError**)error {
    @try {
        [_secureStorage putString:value forKey:key];
        return TRUE;
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperPutString"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return FALSE;
    }
}

- (BOOL)putBytesForBytes:(NSData *)value forKey:(NSString *)key error:(NSError**)error {
    @try {
        [_secureStorage putBytes:value forKey:key];
        return TRUE;
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperPutBytes"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return FALSE;
    }
}

- (BOOL)removeForKey:(NSString *)key error:(NSError**)error {
    @try {
        [_secureStorage removeForKey:key];
        return TRUE;
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperRemoveKey"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return FALSE;
    }
}

- (NSString *_Nullable)getStringForKey:(NSString *)key error:(NSError **)error {
    @try {
        return [_secureStorage getStringForKey:key];
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperGetString"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return nil;
    }
}

- (NSData *_Nullable)getBytesForKey:(NSString *)key error:(NSError **)error {
    @try {
        return [_secureStorage getBytesForKey:key];
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperGetBytes"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return nil;
    }
}

- (NSDictionary * _Nullable)getAllWithError:(NSError **)error {
    @try {
        return [_secureStorage getAll];
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperGetAll"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return nil;
    }
}

+ (BOOL)deleteWithFileName:(NSString *)filename error:(NSError **)error {
    @try {
        [SecureStorageSDK deleteWithFileName:filename];
        return TRUE;
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperDeleteFileName"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return FALSE;
    }
}

- (BOOL)containsKey:(NSString *)key error:(NSError **)error {
    @try {
        return [_secureStorage containsKey:key];
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        
        return FALSE;
    }
}

- (BOOL)clearWithError:(NSError **)error {
    @try {
        [_secureStorage clear];
        return TRUE;
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperClear"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
        return FALSE;
    }
}

- (NSNumber * _Nullable)sizeWithError:(NSError **)error {
    @try {
        return [[NSNumber alloc] initWithInt:[_secureStorage size]];
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        return nil;
    }
}

+ (BOOL)isProtectedBySecureHardware{
    return [SecureStorageSDK isProtectedBySecureHardware];
}

@end
