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
    NSError* sdkError = nil;
    // We want subscribe to every availlable aspect of the notification
    NotificationSDKClientNotificationType types = NotificationSDKClientNotificationTypeBadge | NotificationSDKClientNotificationTypeSound | NotificationSDKClientNotificationTypeAlert;
    
    BOOL registered = [NotificationSDKClient registerNotificationServiceWithNotificationSettings:types error:&error];
    if (!registered || error != nil) {
        
        //_myErrorText = [NSString stringWithFormat:@"Error: %@", [AppDelegate getErrorMessageFromError:error]];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"NotificationDataUpdated" object:nil];
        return YES;
    }
    return NO;
}

+ (NSString *)getVASCONotificationIdentifer:(NSData *)devToken error:(NSError **)error
{
    return [NotificationSDKClient getOneSpanNotificationIdentifier:devToken error:error];
    /*@try {
        return [NotificationSDKClient getOneSpanNotificationIdentifier:devToken error:error];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (BOOL)isVASCONotification:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClient isOneSpanNotification:notification];
    /*@try {
        return [NotificationSDKClient isVASCONotification:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return NO;
    }*/
}

+ (NSString *)parseVASCONotification:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClient parseOneSpanNotification:notification error:error];
    
    /*@try {
        return [NotificationSDKClient parseVASCONotification:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (NSString *)getTitle:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClient getTitle:notification];
    /*@try {
        return [NotificationSDKClient getTitle:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (NSString *)getSubject:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClient getSubject:notification];
    /*@try {
        return [NotificationSDKClient getSubject:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (NSNumber *)getBadgeValue:(NSDictionary *)notification error:(NSError **)error
{
    return [NSNumber numberWithInt:[NotificationSDKClient getBadgeValue:notification]];
    
   /* @try {
        return [NSNumber numberWithInt:[NotificationSDKClient getBadgeValue:notification]];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

    
@end
