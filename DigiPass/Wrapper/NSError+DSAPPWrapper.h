//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSError (DSAPPWrapper)

- (instancetype)initWithCode:(NSInteger)errorCode message:(NSString *)message;
+ (instancetype)newWithCode:(NSInteger)errorCode message:(NSString *)message;

/**
 * Gets a default error message associated with the error code
 * @return The error message
 */
@property (nonatomic, strong, readonly, nullable) NSString* message;

@end

NS_ASSUME_NONNULL_END
