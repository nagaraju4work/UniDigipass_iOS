//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <MSSDigipass/DigipassSDKGenericResponse.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
/**
 * Defines a response to a generation request.
 */
@interface DigipassSDKGenerationResponse : DigipassSDKGenericResponse

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Generated host code.
@property (nonatomic, copy, readonly) NSString *hostCode;

@end

NS_ASSUME_NONNULL_END
