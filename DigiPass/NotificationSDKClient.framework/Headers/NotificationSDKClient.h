/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <NotificationSDKClient/NotificationSDKClientErrorCodes.h>
#import <NotificationSDKClient/NotificationSDKClientException.h>

NS_ASSUME_NONNULL_BEGIN

//! Project version number for NotificationSDKClient.
FOUNDATION_EXPORT double NotificationSDKClientVersionNumber;

//! Project version string for NotificationSDKClient.
FOUNDATION_EXPORT const unsigned char NotificationSDKClientVersionString[];

#define NotificationSDKClient_VERSION  @"4.21.1"


/**
 * This class provides the main functions of the Notification SDK Client.
 */
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
 * The VASCO Notification Identifier must be calculated with the NotificationSDKClient::getVASCONotificationIdentifer: method
 * from the success callback:
 * <ul>
 *  <li>(void)application:(UIApplication *)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)</li>
 * </ul>
 * In case of failure, the application will be notified with the following callback:
 * <ul>
 *  <li>(void)application:(UIApplication *)didFailToRegisterForRemoteNotificationsWithError:(NSError *)</li>
 * </ul>
 *
 * @param notificationType notificationType to be used (NotificationSDKClientNotificationTypeBadge | NotificationSDKClientNotificationTypeSound | NotificationSDKClientNotificationTypeAlert).
 *
 * @throws NotificationSDKClientException
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 */
+ (void)registerNotificationServiceWithNotificationSettings:(NotificationSDKClientNotificationType) notificationType;


/**
 * Get the VASCO Notification Identifier as a string from the devToken provided by the dedicated 
 * system callback, after using the NotificationSDKClient::registerNotificationServiceWithNotificationSettings: method.
 *
 * @param devToken received from the server in the dedicated system callback.
 * This parameter cannot be null.
 *
 * @throws NotificationSDKClientException
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_DEVTOKEN_NULL} if the devToken parameter is null.</li>
 * </ul>
 */
+ (NSString*)getVASCONotificationIdentifer:(NSData *)devToken;



/**
 * Check if the provided NSDictionary is a valid VASCO notification.
 *
 * @param notification The NSDictionary provided by the system.
 * @return true if the provided NSDictionary is a valid VASCO notification, false otherwise.
 * @throws NotificationSDKClientException
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 */
+ (BOOL)isVASCONotification:(NSDictionary *)notification;

/**
 * Parses the notification provided as a NSDictionary and returns the associated content as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 * @return the content of the message associated with the notification that has been parsed.
 * @throws NotificationSDKClientException
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 */
+ (nullable NSString*)parseVASCONotification:(NSDictionary *)notification;

/**
 * Get the title from the notification provided as a NSDictionary and returns it as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 * @return the title of the message associated with the notification that has been parsed.
 * @throws NotificationSDKClientException
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 */
+ (NSString*)getTitle:(NSDictionary *)notification;

/**
 * Get the subject from the notification provided as a NSDictionary and returns the associated content as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 * @return the subject of the message associated with the notification that has been parsed.
 * @throws NotificationSDKClientException
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 */
+ (NSString*)getSubject:(NSDictionary *)notification;

/**
 * Get the value of the badge of a VASCO Notification.
 *
 * @param notification The NSDictionary provided by the system.
 * @return the value of the badge field if it is present, -1 otherwise.
 * @throws NotificationSDKClientException
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 */
+ (int)getBadgeValue:(NSDictionary *)notification;

/*!
 * \mainpage Notification SDK Client - Programmer documentation
 * \brief Provides the entry points of the Notification SDK Client framework API:
 * <ul>
 *   <li>Use NotificationSDKClient::registerNotificationServiceWithNotificationSettings: to register to the service. This should be done in the <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFinishLaunchingWithOptions:">(void)application:(UIApplication *)didFinishLaunchingWithOptions:(NSDictionary *)</a> callback.</li>
 *   <li>Use NotificationSDKClient::getVASCONotificationIdentifer: to retrieve the VASCO Notification Identifier as a NSString from the NSData provided by <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didRegisterUserNotificationSettings:">(void)application:(UIApplication *)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)</a>.</li>
 *   <li>Use NotificationSDKClient::isVASCONotification: to check wether a NSDictionary contains a VASCO Notification.</li>
 *   <li>Use NotificationSDKClient::parseVASCONotification: to retrieve the content of a VASCO Notification as a NSString.</li>
 *   <li>Use NotificationSDKClient::getBadgeValue: to retrieve the value of the badge corresponding to a VASCO Notification.</li>
 * </ul>
 
 <br/> The AppDelegate must implement the following callbacks to manage the reponse of the system regarding notification registration:
 * <ul>
 *  <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didRegisterUserNotificationSettings:">(void)application:(UIApplication *)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)</a>: in case of registration success, a call to NotificationSDKClient::getVASCONotificationIdentifer: should be done in order to retrieve the Vasco Notification Identifier that must later be provided to the server.</li>
 *  <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFailToRegisterForRemoteNotificationsWithError:">(void)application:(UIApplication *)didFailToRegisterForRemoteNotificationsWithError:(NSError *)</a>: in order to manage the registration failure cases.</li>
 * </ul>
 
 * <br/> The AppDelegate must implement the following callbacks to manage notification reception, by performing a call to NotificationSDKClient::parseVASCONotification: in order to retrieve the content of the notification:
 * <ul>
 *  <li>Before iOS 7.0:
 *  <ul>
 *   <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFinishLaunchingWithOptions:">(void)application:(UIApplication *)didFinishLaunchingWithOptions:(NSDictionary *)</a>: upon reception of a push message, when the application was in background or not running;</li>
 *   <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didReceiveRemoteNotification:">(void)application:(UIApplication *)didReceiveRemoteNotification:(NSDictionary *)</a>: upon reception of a push message, when the application was in foreground;
 *   <br/>Note: this callback is directly called upon message reception if the application was in foreground (i.e. without the user needing to press any notification).</li>
 *   </ul>
 *  </li>
 * <li>Since iOS 7.0:
 *  <ul>
 *   <li><a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didReceiveRemoteNotification:fetchCompletionHandler:">(void)application:(UIApplication *)didReceiveRemoteNotification:(NSDictionary *)fetchCompletionHandler:</a>: upon reception of a push message (foreground, background or not running).
 <br/>Note: this callback is directly called upon message reception if the application was in foreground (i.e. without the user needing to press any notification).
 <br/>Note: since iOS 7.0, if this callback implemented, the former <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFailToRegisterForRemoteNotificationsWithError:">(void)application:(UIApplication *)didFailToRegisterForRemoteNotificationsWithError:(NSError *)</a> won't be called. Nevertheless, the notification is still availlable in <a href="https://developer.apple.com/library/ios//documentation/UIKit/Reference/UIApplicationDelegate_Protocol/index.html#//apple_ref/occ/intfm/UIApplicationDelegate/application:didFinishLaunchingWithOptions:">(void)application:(UIApplication *)didFinishLaunchingWithOptions:(NSDictionary *)</a> if the application had to be launched.</li>
 *  </ul>
 * </li>
 
 
 * Copyright &copy; since 1999. VASCO DATA SECURITY. All Rights Reserved.
 * @version @release-version@
 */

@end

NS_ASSUME_NONNULL_END
