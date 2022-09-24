/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#define BiometricSensorSDK_VERSION  @"4.25.1"
#import <Foundation/Foundation.h>
#import <MSSBiometricSensor/BiometricSensorSDKConstants.h>
#import <MSSBiometricSensor/BiometricSensorSDKErrorCodes.h>
#import <MSSBiometricSensor/BiometricSensorSDKReturnCodes.h>
#import <MSSBiometricSensor/AuthenticationDelegate.h>
#import <MSSBiometricSensor/AuthenticationParameters.h>
#import <MSSBiometricSensor/SuccessParameters.h>

NS_ASSUME_NONNULL_BEGIN
/**
 * This class provides the main functions of the Biometric Sensor SDK.
 */

NS_REFINED_FOR_SWIFT
@interface BiometricSensorSDK : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * This method checks if the platform supports the biometric authentication feature (i.e. the hardware and the software both support biometric authentication feature).
 *
 * @param methods indicates which biometric authentication method must be checked (see BiometricSensorSDKConstants.h):
 * - BiometricAuthenticationMethodTouchID if Touch ID authentication method must be checked
 * - BiometricAuthenticationMethodFaceID if Face ID authentication method must be checked
 * - BiometricAuthenticationMethodAny if both Touch ID and Face ID authentication methods must be checked
 *
 * @param error raised if there is an error during the process.
 * The error can contain the following codes (see BiometricSensorSDKErrorCodes.h):
 * - BiometricSensorSDKErrorCodes_BIOMETRIC_AUTHENTICATION_METHOD_INVALID if biometric authentication method parameter is invalid.
 * - BiometricSensorSDKErrorCodes_BIOMETRIC_UNDETERMINED if the biometric authentication method available cannot be determined.
 *
 * @return true if the required biometric authentication feature is supported by the device and false otherwise
 */
+ (BOOL)isBiometricAuthenticationSupportedFor:(BiometricAuthenticationMethod)methods error:(NSError * _Nullable __autoreleasing * _Nullable)error NS_SWIFT_NOTHROW;

/**
 * This method checks if the biometric authentication feature is currently usable (i.e. supported by the platform and fully enabled by the user).
 *
 * @param methods indicates which biometric authentication method must be checked (see BiometricSensorSDKConstants.h):
 * - BiometricAuthenticationMethodTouchID if Touch ID authentication method must be checked
 * - BiometricAuthenticationMethodFaceID if Face ID authentication method must be checked
 * - BiometricAuthenticationMethodAny if both Touch ID and Face ID authentication methods must be checked
 *
 * @param error raised if there is an error during the process.
 * The error can contain the following codes (see BiometricSensorSDKErrorCodes.h):
 * - BiometricSensorSDKErrorCodes_BIOMETRIC_AUTHENTICATION_METHOD_INVALID if biometric authentication method parameter is invalid.
 * - BiometricSensorSDKErrorCodes_NOT_ENROLLED if no biometric information has been enrolled in the system
 * - BiometricSensorSDKErrorCodes_BIOMETRIC_UNDETERMINED if the biometric authentication method available cannot be determined.
 *
 * @return true if the biometric authentication feature is currently usable
 */
+ (BOOL)isBiometricAuthenticationEnrolledFor:(BiometricAuthenticationMethod)methods error:(NSError * _Nullable __autoreleasing * _Nullable)error NS_SWIFT_NOTHROW;

/**
 * Starts the user authentication.
 *
 * @param parameters Params used to configure user authentication process.
 * @param delegate The delegate to be notified of the authentication events.
 *
 * @param error raised if there is an error during the process.
 * The error can contain the following codes (see BiometricSensorSDKErrorCodes.h):
 * - BiometricSensorSDKErrorCodes_BIOMETRIC_AUTHENTICATION_METHOD_INVALID if biometric authentication method defined inside AuthenticationParameters param is invalid.
 * - BiometricSensorSDKErrorCodes_FALLBACK_MECHANISM_TEXT_PARAMETER_NULL_OR_EMPTY if the value of the fallback mechanism button text defined inside AuthenticationParameters param is null or empty.
 * - BiometricSensorSDKErrorCodes_NOT_ENROLLED if no biometric information has been enrolled in the system
 * - BiometricSensorSDKErrorCodes_BIOMETRIC_UNDETERMINED if the biometric authentication method available cannot be determined.
 *
 * @return true if the biometric authentication is successful for given parameters
 */
+ (BOOL)startBiometricAuthenticationWithParameters:(AuthenticationParameters *)parameters delegate:(id<AuthenticationDelegate>)delegate error:(NSError * _Nullable __autoreleasing * _Nullable)error;

/**
 * Stop the user authentication.
 * If no user authentication is in progress, nothing happens.
 */
+ (void)stopBiometricAuthentication;

/*!
 * \mainpage BiometricSensor SDK - Programmer documentation
 * \brief Provides the entry points of the BiometricSensor SDK framework API:
 * <ul>
 *   <li>Use {@link BiometricSensorSDK#isBiometricAuthenticationSupportedFor:error:} to check whether the platform supports the biometric authentication feature (i.e. the hardware and the software both support biometric authentication feature)</li>
 *   <li>Use {@link BiometricSensorSDK#isBiometricAuthenticationEnrolledFor:error:} to check whether the biometric authentication feature is currently usable (i.e. supported by the platform and fully enabled by the user)</li>
 *   <li>Use {@link BiometricSensorSDK#startBiometricAuthenticationWithParameters:delegate:error:} to start user's biometric authentication</li>
 *   <li>Use {@link BiometricSensorSDK#stopBiometricAuthentication} to stop the user's biometric authentication</li>
 * </ul>
 * @OneSpanCopyright
 * @version 4.25.1
 */

@end

NS_ASSUME_NONNULL_END
