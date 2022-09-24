/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <NotificationSDKClient/NotificationSDKClient.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This class provides the main functions of the Notification SDK Client.
 */
@interface NotificationSDKClientWrapper : NSObject

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
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
+ (BOOL)registerNotificationServiceWithNotificationSettings:(NotificationSDKClientNotificationType)notificationType error:(NSError **)error;

/**
 * Get the VASCO Notification Identifier as a string from the devToken provided by the dedicated
 * system callback, after using the NotificationSDKClient::registerNotificationServiceWithNotificationSettings: method.
 *
 * @param devToken received from the server in the dedicated system callback.
 * This parameter cannot be null.
 *
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_DEVTOKEN_NULL} if the devToken parameter is null.</li>
 * </ul>
 * @return Yes if the call is successful, If an error occurred the reason will be put in the error.
 */
+ (NSString * _Nullable)getVASCONotificationIdentifer:(NSData *)devToken error:(NSError **)error;

/**
 * Check if the provided NSDictionary is a valid VASCO notification.
 *
 * @param notification The NSDictionary provided by the system.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 * </ul>
 * @return true if the provided NSDictionary is a valid VASCO notification, false otherwise. If an error occurred the reason will be put in the error.
 */
+ (BOOL)isVASCONotification:(NSDictionary *)notification error:(NSError **)error;

/**
 * Parses the notification provided as a NSDictionary and returns the associated content as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 * @return the content of the message associated with the notification that has been parsed. If an error occurred the reason will be put in the error.
 */
+ (NSString * _Nullable)parseVASCONotification:(NSDictionary *)notification error:(NSError **)error;

/**
 * Get the title from the notification provided as a NSDictionary and returns it as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 * @return the title of the message associated with the notification that has been parsed. If an error occurred the reason will be put in the error.
 */
+ (NSString* _Nullable)getTitle:(NSDictionary *)notification error:(NSError**)error;

/**
 * Get the subject from the notification provided as a NSDictionary and returns the associated content as a NString.
 *
 * @param notification The NSDictionary provided by the system.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 * @return the subject of the message associated with the notification that has been parsed. If an error occurred the reason will be put in the error.
 */
+ (NSString * _Nullable)getSubject:(NSDictionary *)notification error:(NSError **)error;

/**
 * Get the value of the badge of a VASCO Notification.
 *
 * @param notification The NSDictionary provided by the system.
 * @param error a NSError raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *  <li>{@link NotificationSDKClientErrorCodes_INTERNAL_ERROR} if an internal error occurred.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_NULL} if notification is Null.</li>
 *  <li>{@link NotificationSDKClientErrorCodes_NOTIFICATION_INVALID} if notification is invalid.</li>
 * </ul>
 * @return the value of the badge field if it is present, -1 otherwise. If an error occurred the reason will be put in the error.
 */
+ (NSNumber * _Nullable)getBadgeValue:(NSDictionary *)notification error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
