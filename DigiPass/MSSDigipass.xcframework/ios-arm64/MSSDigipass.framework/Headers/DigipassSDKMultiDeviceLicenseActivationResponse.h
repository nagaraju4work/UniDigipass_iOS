//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <MSSDigipass/DigipassSDKActivationResponse.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
/**
 * A response object for the first step of the multi-device activation process.
 */
@interface DigipassSDKMultiDeviceLicenseActivationResponse : DigipassSDKActivationResponse

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Generated device code.
@property (nonatomic, readonly, copy, nullable) NSString *deviceCode;

@end

NS_ASSUME_NONNULL_END
