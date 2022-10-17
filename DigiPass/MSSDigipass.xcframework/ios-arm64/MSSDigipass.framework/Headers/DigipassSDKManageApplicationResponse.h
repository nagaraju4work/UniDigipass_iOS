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
 * Defines a response to a enable / disable application request.
 */
@interface DigipassSDKManageApplicationResponse : NSObject

/// Dynamic vector
@property (nonatomic, readonly, copy, nullable) NSData *dynamicVector;

@end

NS_ASSUME_NONNULL_END
