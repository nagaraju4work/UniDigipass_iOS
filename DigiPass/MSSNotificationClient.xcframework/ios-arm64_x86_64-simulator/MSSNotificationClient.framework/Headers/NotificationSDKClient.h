/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////
#import <Foundation/Foundation.h>

#define NotificationSDKClient_VERSION  @"4.29.2"

NS_ASSUME_NONNULL_BEGIN
/**
 * This class provides the main functions of the Notification SDK Client.
 */
NS_REFINED_FOR_SWIFT
@interface NotificationSDKClient : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * NotificationSDKClientNotificationType object used to configure the type
 * of interactions the created notification should have with the user and the system.<br/>
 * Values that can be used (composition with binary or |):
 * <ul>
 *  <li>NotificationSDKClientNotificationTypeNone: no alteration;</li>
 *  <li>NotificationSDKClientNotificationTypeBadge: use the badge on icon;</li>
 *  <li>NotificationSDKClientNotificationTypeSound: use a sound for the notification;</li>
 *  <li>NotificationSDKClientNotificationTypeAlert: use an alert for the notification.</li>
 * </ul>
 */
typedef NS_OPTIONS(NSUInteger, NotificationSDKClientNotificationType) {
    NotificationSDKClientNotificationTypeNone    = 0,
    NotificationSDKClientNotificationTypeBadge   = 1 << 0,
    NotificationSDKClientNotificationTypeSound   = 1 << 1,
    NotificationSDKClientNotificationTypeAlert   = 1 << 2,
};


/**
 * Register to the Apple push notification service.
 * The OneSpan Notification Identifier must be calculated with the {@link NotificationSDKClient#getOneSpanNotificationIdentifier:error:} method
 * from the success callback:
 *  (void)application:(UIApplication *)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)
 * In case of failure, the application will be notified with the following callback:
 *  (void)application:(UIApplication *)didFailToRegisterForRemoteNotificationsWithError:(NSError *)
 *
 *
 * @param notificationType notificationType to be used ({@link NotificationSDKClientNotificationTypeBadge} | {@link NotificationSDKClientNotificationTypeSound} | {@link NotificationSDKClientNotificationTypeAlert}).
 * @param error a NSError raised if there is an error during the process.
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>

 * @return true if the call is successful, If an error occurred the reason will be put in the error.
 */
+ (BOOL)registerNotificationServiceWithNotificationSettings:(NotificationSDKClientNotificationType)notificationType error:(NSError **_Nullable)error;

/**
 * Get the OneSpan Notification Identifier as a string from the devToken provided by the dedicated
 * system callback, after using the {@link NotificationSDKClient#registerNotificationServiceWithNotificationSettings:error:} method.
 *
 * @param devToken received from the server in the dedicated system callback.
 * This parameter cannot be null.
 * @param error a NSError raised if there is an error during the process.
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_DEVTOKEN_NULL} if the devToken parameter is null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if the devToken parameter is empty.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 *
 * @returns the calculated OneSpan notification identifier
 */
+ (NSString *_Nullable)getOneSpanNotificationIdentifier:(NSData *)devToken error:(NSError **_Nullable)error;

/**
 * Check if the provided NSDictionary is a valid OneSpan notification.
 *
 * @param notification The NSDictionary provided by the system.
 *
 * @return true if the provided NSDictionary is a valid OneSpan notification, false otherwise.
 */
+ (BOOL)isOneSpanNotification:(NSDictionary *)notification;

/**
 * Parses the notification provided as a NSDictionary and returns the associated content as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 * @param error a NSError raised if there is an error during the process.
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if the notification dictionary is nil.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if the notification dictionary is not an OneSpan payload.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 *
 * @return the content of the message associated with the notification that has been parsed.
 */
+ (NSString *_Nullable)parseOneSpanNotification:(NSDictionary *)notification error:(NSError **_Nullable)error;

/**
 * Get the title from the notification provided as a NSDictionary and returns it as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 *
 * @return the title of the message associated with the notification that has been parsed.
 */
+ (NSString *_Nullable)getTitle:(NSDictionary *)notification;

/**
 * Get the subject from the notification provided as a NSDictionary and returns the associated content as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 *
 * @return the subject of the message associated with the notification that has been parsed.
 */
+ (NSString *_Nullable)getSubject:(NSDictionary *)notification;

/**
 * Get the value of the badge of a OneSpan Notification.
 *
 * @param notification The NSDictionary provided by the system.
 *
 * @return the value of the badge field if it is present, nil otherwise.
 */
+ (NSNumber *_Nullable)getBadgeValue:(NSDictionary *)notification;

/**
 * Get the custom Attributes of a OneSpan Notification.
 *
 * @param notification The NSDictionary provided by the system.
 *
 * @return the custom attributes if found, else returns nill.
 */
+ (NSDictionary<NSString *,NSString *> *_Nullable)getCustomAttributes:(NSDictionary *)notification;

/*!
 * \mainpage Notification SDK Client - Programmer documentation
 * \brief Provides the entry points of the Notification SDK Client framework API:
 * <ul>
 *   <li>Use {@link NotificationSDKClient#registerNotificationServiceWithNotificationSettings:error:} to register to the service. This should be done in the <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFinishLaunchingWithOptions:">(void)application:(UIApplication *)didFinishLaunchingWithOptions:(NSDictionary *)</a> callback.</li>
 *   <li>Use {@link NotificationSDKClient#getOneSpanNotificationIdentifier:error:} to retrieve the OneSpan Notification Identifier as a NSString from the NSData provided by <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didRegisterUserNotificationSettings:">(void)application:(UIApplication *)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)</a>.</li>
 *   <li>Use {@link NotificationSDKClient#isOneSpanNotification:} to check wether a NSDictionary contains a OneSpan Notification.</li>
 *   <li>Use {@link NotificationSDKClient#parseOneSpanNotification:error:} to retrieve the content of a OneSpan Notification as a NSString.</li>
 *   <li>Use {@link NotificationSDKClient#getBadgeValue:} to retrieve the value of the badge corresponding to a OneSpan Notification.</li>
 * </ul>
 *
 * <br/> The AppDelegate must implement the following callbacks to manage the reponse of the system regarding notification registration:
 * <ul>
 *  <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didRegisterUserNotificationSettings:">(void)application:(UIApplication *)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)</a>: in case of registration success, a call to {@link NotificationSDKClient#getOneSpanNotificationIdentifier:error:} should be done in order to retrieve the OneSpan Notification Identifier that must later be provided to the server.</li>
 *  <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFailToRegisterForRemoteNotificationsWithError:">(void)application:(UIApplication *)didFailToRegisterForRemoteNotificationsWithError:(NSError *)</a>: in order to manage the registration failure cases.</li>
 * </ul>
 *
 * <br/> The AppDelegate must implement the following callbacks to manage notification reception, by performing a call to {@link NotificationSDKClient#parseOneSpanNotification:error:} in order to retrieve the content of the notification:
 * <ul>
 * <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didReceiveRemoteNotification:fetchCompletionHandler:">(void)application:(UIApplication *)didReceiveRemoteNotification:(NSDictionary *)fetchCompletionHandler:</a>: upon reception of a push message (foreground, background or not running).
 * <br/>Note: this callback is directly called upon message reception if the application was in foreground (i.e. without the user needing to press any notification).
 * <br/>Note: if this callback is implemented, the former <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFailToRegisterForRemoteNotificationsWithError:">(void)application:(UIApplication *)didFailToRegisterForRemoteNotificationsWithError:(NSError *)</a> won't be called. Nevertheless, the notification is still availlable in <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFinishLaunchingWithOptions:">(void)application:(UIApplication *)didFinishLaunchingWithOptions:(NSDictionary *)</a> if the application had to be launched.</li>
 *  </ul>
 * </li>
 *
 *
 * @OneSpanCopyright
 * @version 4.29.2
 */

@end

NS_ASSUME_NONNULL_END
