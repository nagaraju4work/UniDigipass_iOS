/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <MSSBiometricSensor/BiometricSensorSDKConstants.h>
#import <MSSBiometricSensor/SuccessParameters.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
@protocol AuthenticationDelegate <NSObject>

/// Notifies the delegate that authentication succeeded.
/// - Parameter parameters: details regading the successful authentication.
- (void)biometricAuthenticationDidSucceedWithParameters:(SuccessParameters*)parameters;

/// Notifies the delegate that authentication failed.
/// - Parameter method: used method for authentication.
- (void)biometricAuthenticationDidFailForMethod:(UsedBiometricAuthenticationMethod)method;

/// Notifies the delegate that the fallback mechanism was called.
- (void)biometricAuthenticationDidCallFallbackMethod;

/// Notifies the delegate that authentication was cancelled.
- (void)biometricAuthenticationDidCancel;

/// Notifies the delegate that an error occurred during the authentication process.
- (void)biometricAuthenticationDidReceive:(NSError*)error;

@end

NS_ASSUME_NONNULL_END
