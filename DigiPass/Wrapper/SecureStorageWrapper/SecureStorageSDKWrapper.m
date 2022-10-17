//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "SecureStorageSDKWrapper.h"
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
        _secureStorage = [[SecureStorageSDK alloc] initWithFileName:filename fingerprint:fingerprint iterationNumber:iterationNumber error:error];
        if (error != nil) {
            [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperInit"
                                parameters:@{
                                             @"error":  @"error SecureStorageSDKWrapper:initWithFileName.method"
                                             }];
            return  nil;
        }
        /*@try {
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
        }*/
    }
    return self;
}

- (BOOL)writeWithFingerprint:(NSString *)fingerPrint andIterationNumber:(int)iterationNumber error:(NSError**)error {
    return [_secureStorage writeWithFingerPrint:fingerPrint iterationNumber:iterationNumber error:error];
    /*@try {
        [_secureStorage writeWithFingerPrint:fingerPrint andIterationNumber:iterationNumber];
        return TRUE;
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        return FALSE;
    }*/
}

- (BOOL)putStringForValue:(NSString *)value forKey:(NSString *)key error:(NSError**)error {
    BOOL shouldStorage = [_secureStorage putWithString:value key:key error:error];
    if (!shouldStorage) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperPutString"
                            parameters:@{
                                         @"error": @"error SecureStorageSDKWrapper:putWithString.method"
        }];
    }
    return shouldStorage;
    /*@try {
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
    }*/
}

- (BOOL)putBytesForBytes:(NSData *)value forKey:(NSString *)key error:(NSError**)error {
    BOOL shouldBytes = [_secureStorage putWithData:value key:key error:error];
    if (!shouldBytes) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperPutBytes"
                            parameters:@{
                                         @"error": @"error SecureStorageSDKWrapper:putWithData.method"
                                         }];
    }
    return shouldBytes;
    /*@try {
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
    }*/
}

- (BOOL)removeForKey:(NSString *)key error:(NSError**)error {
    BOOL shouldRemove = [_secureStorage removeValueWithKey:key error:error];
    if (!shouldRemove) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperRemoveKey"
                            parameters:@{
                                         @"error": @"error SecureStorageSDKWrapper:removeValueWithKey.method"
                                         }];
    }
    return shouldRemove;
    /*@try {
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
    }*/
}

- (NSString *_Nullable)getStringForKey:(NSString *)key error:(NSError **)error {
    NSString* shouldGetString = [_secureStorage getStringWithKey:key error:error];
    if (!shouldGetString) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperGetString"
                            parameters:@{
                                         @"error": @"error: SecureStorageSDKWrapper:getStringWithKey.method "
                                         }];
    }
    return shouldGetString;
    /*@try {
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
    }*/
}

- (NSData *_Nullable)getBytesForKey:(NSString *)key error:(NSError **)error {
    NSData* shouldGetBytes = [_secureStorage getDataWithKey:key error:error];
    if (!shouldGetBytes) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperGetBytes"
                            parameters:@{
                                         @"error": @"error: SecureStorageSDKWrapper:getDataWithKey.method "
                                         }];
    }
    return shouldGetBytes;
    
    /*@try {
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
    }*/
}

- (NSDictionary * _Nullable)getAllWithError:(NSError **)error {
    NSDictionary* shouldGetAll = [_secureStorage getAllAndReturnError:error];
    if (!shouldGetAll) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperGetAll"
                            parameters:@{
                                         @"error": @"error: SecureStorageSDKWrapper:getAllAndReturnError.method "
                                         }];
    }
    return  shouldGetAll;
    
    /*@try {
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
    }*/
}

+ (BOOL)deleteWithFileName:(NSString *)filename error:(NSError **)error {
    BOOL shouldDelete = [SecureStorageSDK deleteWithFileName:filename error:error];
    if (!shouldDelete) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperDeleteFileName"
                            parameters:@{
                                         @"error": @"error: SecureStorageSDKWrapper:deleteWithFileName.method "
                                         }];
    }
    return shouldDelete;
    /*@try {
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
    }*/
}

- (BOOL)containsKey:(NSString *)key error:(NSError **)error {
    return [_secureStorage containsWithKey:key];
    
    /*@try {
        return [_secureStorage containsKey:key];
    }
    @catch (SecureStorageSDKException *e) {
        NSString * message = e.exception ? e.exception.reason : @"";
        *error = [[NSError alloc] initWithDomain:kDomain code:e.errorCode userInfo:@{kMessage:message}];
        
        return FALSE;
    }*/
}

- (BOOL)clearWithError:(NSError **)error {
    BOOL shouldClear = [_secureStorage clearAndReturnError:error];
    if (!shouldClear) {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperClear"
                            parameters:@{
                                         @"error": @"error: SecureStorageSDKWrapper:clearAndReturnError.method "
                                         }];
    }
    return shouldClear;
    /*@try {
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
    }*/
}

+ (BOOL)isProtectedBySecureHardware{
    return [SecureStorageSDK isProtectedBySecureHardware];
}

@end
