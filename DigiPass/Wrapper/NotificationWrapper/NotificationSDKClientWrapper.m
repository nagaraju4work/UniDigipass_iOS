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
    NSLog(@"registerNotificationServiceWithNotificationSettings");
    // We want subscribe to every availlable aspect of the notification
    BOOL registered = [NotificationSDKClientWrapper registerNotificationServiceWithNotificationSettings:notificationType error:error];
    NSLog(@"tt %@",registered);
//    BOOL registered = [NotificationSDKClientWrapper registerNotificationServiceWithNotificationSettings:types error:error];
    if (!registered || error != nil) {
        
        //_myErrorText = [NSString stringWithFormat:@"Error: %@", [AppDelegate getErrorMessageFromError:error]];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"NotificationDataUpdated" object:nil];
        return YES;
    }
    return NO;
}

+ (NSString *)getVASCONotificationIdentifer:(NSData *)devToken error:(NSError **)error
{
    return [NotificationSDKClientWrapper getVASCONotificationIdentifer:devToken error:error];
    /*@try {
        return [NotificationSDKClient getOneSpanNotificationIdentifier:devToken error:error];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (BOOL)isVASCONotification:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClientWrapper isVASCONotification:notification error:error];
    /*@try {
        return [NotificationSDKClient isVASCONotification:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return NO;
    }*/
}

+ (NSString *)parseVASCONotification:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClientWrapper parseVASCONotification:notification error:error];
    
    /*@try {
        return [NotificationSDKClient parseVASCONotification:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (NSString *)getTitle:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClientWrapper getTitle:notification error:error];
    /*@try {
        return [NotificationSDKClient getTitle:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (NSString *)getSubject:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClientWrapper getSubject:notification error:error];
    /*@try {
        return [NotificationSDKClient getSubject:notification];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

+ (NSNumber *)getBadgeValue:(NSDictionary *)notification error:(NSError **)error
{
    return [NotificationSDKClientWrapper getBadgeValue:notification error:error];
    
   /* @try {
        return [NSNumber numberWithInt:[NotificationSDKClient getBadgeValue:notification]];
    } @catch (NotificationSDKClientException *exception) {
        *error = [[NSError alloc] initWithDomain:kDomain code:exception.errorCode userInfo:exception.userInfo];
        return nil;
    }*/
}

    
@end
