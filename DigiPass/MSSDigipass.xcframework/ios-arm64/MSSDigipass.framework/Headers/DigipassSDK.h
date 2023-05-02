//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT

/**
 * Provides the entry points of the DIGIPASS SDK:
 * <ul>
 *     <li>Offline/Online activation/reactivation</li>
 *     <li>One-Time Password generation</li>
 *     <li>Challenge / Response</li>
 *     <li>Data signing with or without enhanced security</li>
 *  <li>Password management</li>
 *  <li>Device binding</li>
 *  <li>Multi-device activation</li>
 *  <li>Secure channel</li>
 *  <li>Utility methods:
 *   <ul>
 *    <li>DIGIPASS properties</li>
 *    <li>Enable/Disable application</li>
 *    <li>Cryptographic methods</li>
 *    <li>Client/Server time shift management</li>
 *    <li>Error code message converter</li>
 *   </ul>
 *  </li>
 * </ul>
 *
 * @since 4.0.
 * @version 4.31.0
 */
@interface DigipassSDK : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Version of the Digipass SDK current version
+ (NSString *)version;

/*!
 * \mainpage Digipass SDK - Programmer documentation
 * \brief This documentation describes the methods and the constants provided by the DIGIPASS SDK.<br/>
 * <br/>
 * They are exposed by the {@link DigipassSDK} header file.<br/>
 * <br/>
 * @OneSpanCopyright
 * @version 4.31.0
 */
@end

NS_ASSUME_NONNULL_END

