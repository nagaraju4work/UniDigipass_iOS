/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

/** Available Biometric Authentication Method. */
typedef enum {
    
    /** Touch ID sensor must be used */
    BiometricAuthenticationMethodTouchID = 1 << 0,
    
    /** Face ID sensor must be used*/
    BiometricAuthenticationMethodFaceID = 1 << 1,
    
    /** Face ID or Touch ID sensor must be used */
   BiometricAuthenticationMethodAny = BiometricAuthenticationMethodTouchID | BiometricAuthenticationMethodFaceID
    
} BiometricAuthenticationMethod NS_REFINED_FOR_SWIFT;

/** Used Biometric Authentication Method. */
typedef enum {
    
    /** An undetermined method was used */
    UsedBiometricAuthenticationMethodUndetermined,
    
    /** Touch ID method has been used */
    UsedBiometricAuthenticationMethodTouchID,
    
    /** Face ID method has been used */
    UsedBiometricAuthenticationMethodFaceID
    
} UsedBiometricAuthenticationMethod NS_REFINED_FOR_SWIFT;
