/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN

@interface GeolocationSDKException : NSException

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/** Indicates the cause of the error */
@property(readonly) int errorCode;

/** The cause of the error as a NSException */
@property (readonly, nullable, nonatomic , strong) NSException * exception;

/**
 * Instanciate and initialize a GeolocationSDKException
 */
- (instancetype)initWithCause:(NSException *)cause andError:(int)errorCode;

/**
 * Instanciate and initialize a GeolocationSDKException
 */
- (instancetype)initWithError:(int)errorCode;

@end

NS_ASSUME_NONNULL_END
