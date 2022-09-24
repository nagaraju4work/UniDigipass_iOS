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
@interface AuthenticationParameters : NSObject

- (instancetype)initReason:(NSString *)reason methods:(BiometricAuthenticationMethod)methods fallbackMechanismText:(NSString *)fallbackMechanismText;

/**
 * Indicates whether a fallback mechanism button should be displayed for the user to choose.
 * The default value is NO.
 */
- (BOOL)usesFallbackMechanism;

/**
 * Indicates the choosed authentication method. It must be one of these values : BiometricAuthenticationMethodTouchID, BiometricAuthenticationMethodFaceID or BiometricAuthenticationMethodAny
 * The default value is BiometricAuthenticationMethodAny.
 */
@property (nonatomic) BiometricAuthenticationMethod methods;

/** The text that should be displayed on the fallback mechanism button, should the fallback mechanism be used. This parameter cannot be null or empty if the fallback mechanism is used. */
@property (nonatomic, copy, nullable) NSString* fallbackMechanismText;

/** This is the text the device will display in the biometric view giving the reason for the biometric authentication. */
@property (nonatomic, copy, nullable) NSString* reason;

@end

NS_ASSUME_NONNULL_END
