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
 * Represents a crypto application.
 */
@interface DigipassSDKApplication : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Application index.
@property (nonatomic, readonly, assign) NSInteger index;

/// Application name.
@property (nonatomic, readonly, copy) NSString * name;

/// Indicated if the application is enabled.
@property (nonatomic, readonly, assign) BOOL isEnabled;

/// Response length.
@property (nonatomic, readonly, assign) NSInteger responseLength;

/// Host code length.
@property (nonatomic, readonly, assign) NSInteger hostCodeLength;

/// Check digit flag.
@property (nonatomic, readonly, assign) BOOL checkDigit;

/// Data fields number.
@property (nonatomic, readonly, assign) NSInteger dataFieldNumber;

/// Data fields min length.
@property (nonatomic, readonly, copy) NSData *dataFieldsMinLength;

/// Data fields max length.
@property (nonatomic, readonly, copy) NSData *dataFieldsMaxLength;

/// Event counter.
@property (nonatomic, readonly, assign) NSInteger eventCounter;

/// Last time used.
@property (nonatomic, readonly, assign) NSInteger lastTimeUsed;

/// if the DIGIPASS is time based
@property (nonatomic, readonly, assign) BOOL timeBased;

/// if the DIGIPASS is event based
@property (nonatomic, readonly, assign) BOOL eventBased;

/// Output type.
@property (nonatomic, readonly, assign) NSInteger outputType;

/// Codeword (algorithm and the operating mode).
@property (nonatomic, readonly, copy) NSData * codeword;

/// The time step used during the one-time password computation.
@property (nonatomic, readonly, assign) NSInteger timeStep;

/// Authentication mode.
@property (nonatomic, readonly, copy) NSString * authenticationMode;

/// if a crypto application can generate score-based OTPs.
@property (nonatomic, readonly, assign) BOOL scoreCapable;

@end

NS_ASSUME_NONNULL_END
