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
 * Generic responses to a DIGIPASS SDK request.
 */
@interface DigipassSDKGenericResponse : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Response
@property (nonatomic, readonly, copy, nullable) NSString *response;

/// Dynamic vector
@property (nonatomic, readonly, copy, nullable) NSData *dynamicVector;

/** Attempt left */
@property (nonatomic, readonly) NSUInteger attemptsLeft;

@end

NS_ASSUME_NONNULL_END
