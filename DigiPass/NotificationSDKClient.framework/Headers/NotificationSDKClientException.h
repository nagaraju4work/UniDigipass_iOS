/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN

@interface NotificationSDKClientException : NSException

/** Indicates the cause of the error */
@property (readonly, nonatomic) int errorCode;

/** The cause of the error as a NSException */
@property (readonly, nonatomic, strong, nullable) NSException * exception;

/**
 * Instanciate and initialize a NotificationSDKClientException
 * @param cause exception which caused the creation of the NotificationSDKClientException. Used with errorCode NotificationSDKClientErrorCodes_INTERNAL_ERROR (see NotificationSDKClientErrorCodes.h).
 * @param errorCode code describing the nature of the error (see NotificationSDKClientErrorCodes.h).
 */
- (instancetype)initWithCause:(NSException *)cause andError:(int)errorCode;

/**
 * Instanciate and initialize a NotificationSDKClientException
 * @param errorCode code describing the nature of the error (see NotificationSDKClientErrorCodes.h).
 */
- (instancetype)initWithError:(int)errorCode;

@end

NS_ASSUME_NONNULL_END
