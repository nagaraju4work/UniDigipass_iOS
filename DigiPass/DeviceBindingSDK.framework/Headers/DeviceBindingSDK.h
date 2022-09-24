//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define DeviceBindingSDK_VERSION  @"4.21.1"

/**
 * This class provides a method to generate a device fingerprint
 */
@interface DeviceBindingSDK : NSObject

/**
 * Gets a device fingerprint.<br/>
 * The salt is used when creating the fingerprint.<br/>
 * Once the fingerprint has been added in the keychain, it is not regenerated, so the salt won't be used anymore.
 * @deprecated use DeviceBindingSDK::getDeviceFingerPrintWithDynamicSalt: method.
 * @param salt Optional salt which can be added to the device fingerprint computation process.
 * @return 64 hexadecimal characters uniquely identifying the iOS device.
 * @throws DeviceBindingSDKException If a problem occurs while generating the device fingerprint.<br/>
 * The exception can contain one of the following error codes:
 * <ul>
 *  <li>DeviceBindingSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see DeviceBindingSDKErrorCodes.h).</li>
 * </ul>
 */
+(NSString * ) getDeviceFingerPrintWithSalt:(NSString *) salt
__deprecated_msg("use DeviceBindingSDK::getDeviceFingerPrintWithDynamicSalt: method.")
;

/**
 * Gets a device fingerprint diversifed by using the salt.<br/>
 * Contrary to the getDeviceFingerPrintWithSalt method, the current method diversifies the fingerprint with the salt each time a fingerprint is requested.<br/>
 * @param salt Optional salt which can be added to the device fingerprint computation process.
 * @return 64 hexadecimal characters uniquely identifying the iOS device.
 * @throws DeviceBindingSDKException If a problem occurs while generating the device fingerprint.<br/>
 * The exception can contain one of the following error codes:
 * <ul>
 *  <li>DeviceBindingSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see DeviceBindingSDKErrorCodes.h).</li>
 * </ul>
 */
+(NSString * ) getDeviceFingerPrintWithDynamicSalt:(NSString *) salt;

/**
 * Deletes the device fingerprint for a renewal purpose.<br/>
 * This method must be used if a migration is required.
 * @throws DeviceBindingSDKException If a problem occurs while generating the device fingerprint.<br/>
 * The exception can contain one of the following error codes:
 * <ul>
 *  <li>DeviceBindingSDKErrorCodes_INTERNAL_ERROR if an internal error occurs (see DeviceBindingSDKErrorCodes.h).</li>
 * </ul>
 */
+(void) deleteDeviceFingerPrint;

/*!
 * \mainpage DeviceBinding SDK - Programmer documentation
 * \brief Provides the entry points of the DeviceBinding SDK framework API:
 * <ul>
 *  <li>Calling the method [DeviceBindingSDK getDeviceFingerPrint] generates and stores a unique device fingerprint </li>
 *  <li>DeviceBindingSDKException is thrown if an internal error occured.</li>
 * </ul>
 * Copyright &copy; since 1999. VASCO DATA SECURITY. All Rights Reserved.
 * @version 4.21.1
 */


@end
