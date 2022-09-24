/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <MSSBiometricSensor/BiometricSensorSDKConstants.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
@interface SuccessParameters : NSObject

/** Method used during the authentication */
@property (nonatomic) UsedBiometricAuthenticationMethod usedMethod;

/**
 * Contains policy domain state.
 *
 * This property is set only when evaluatePolicy is called and succesful Touch ID or Face ID authentication
 * was performed, or when canEvaluatePolicy succeeds for a biometric policy.
 * It stays nil for all other cases.
 * If biometric database was modified (fingers or faces were removed or added), evaluatedPolicyDomainState
 * data will change. Nature of such database changes cannot be determined
 * but comparing data of evaluatedPolicyDomainState after different evaluatePolicy
 * will reveal the fact database was changed between calls.
 *
 * @warning Please note that the value returned by this property can change exceptionally between major OS versions even if
 *          the state of biometry has not changed.
 */
@property (nonatomic, strong, nullable) NSData* evaluatedPolicyDomainState;

@end

NS_ASSUME_NONNULL_END
