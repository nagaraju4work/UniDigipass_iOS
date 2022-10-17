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
 * Defines a response to an activation request.
 */
@interface DigipassSDKActivationResponse : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Static vector.
@property (nonatomic, readonly, copy, nullable) NSData *staticVector;

/// Dynamic vector
@property (nonatomic, readonly, copy, nullable) NSData *dynamicVector;

/// Attempt left
@property (nonatomic, readonly) NSUInteger attemptsLeft;

@end

NS_ASSUME_NONNULL_END
