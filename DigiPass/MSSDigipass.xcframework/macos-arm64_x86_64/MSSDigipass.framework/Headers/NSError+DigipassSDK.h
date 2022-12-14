//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This category add properties assessors on NSError to retrieve some Digipass information.
 */
@interface NSError (DigipassSDK)

/// Gets the message associated with the error code
@property (nonatomic, copy, readonly, nullable) NSString *message;

///  Dynamic vector, contains the DIGIPASS data, MANDATORY, <b>must be stored after the call</b>
@property (nonatomic, copy, readonly, nullable) NSData *dynamicVector;

/// Returns the attempt left.
@property (nonatomic, readonly) NSUInteger attemptsLeft;

@end

NS_ASSUME_NONNULL_END
