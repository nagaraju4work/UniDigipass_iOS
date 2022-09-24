/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "NotificationSDKClientWrapper.h"

static NSString *const kDomain = @"NotificationSDKClient";

@implementation NotificationSDKClientWrapper

+ (BOOL)registerNotificationServiceWithNotificationSettings:(NotificationSDKClientNotificationType) notificationType error:(NSError **)error
{
    @try {
        [NotificationSDKClient registerNotificationServiceWithNotificationSettings:notificationType];
        return YES;
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return NO;
    }
}

+ (NSString *)getVASCONotificationIdentifer:(NSData *)devToken error:(NSError **)error
{
    @try {
        return [NotificationSDKClient getVASCONotificationIdentifer:devToken];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }
}

+ (BOOL)isVASCONotification:(NSDictionary *)notification error:(NSError **)error
{
    @try {
        return [NotificationSDKClient isVASCONotification:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return NO;
    }
}

+ (NSString *)parseVASCONotification:(NSDictionary *)notification error:(NSError **)error
{
    @try {
        return [NotificationSDKClient parseVASCONotification:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }
}

+ (NSString *)getTitle:(NSDictionary *)notification error:(NSError **)error
{
    @try {
        return [NotificationSDKClient getTitle:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }
}

+ (NSString *)getSubject:(NSDictionary *)notification error:(NSError **)error
{
    @try {
        return [NotificationSDKClient getSubject:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }
}

+ (NSNumber *)getBadgeValue:(NSDictionary *)notification error:(NSError **)error
{
    @try {
        return [NSNumber numberWithInt:[NotificationSDKClient getBadgeValue:notification]];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }
}

    
@end
