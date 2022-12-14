#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
/**
 * Constants used by the DSAPP library.
 */
@interface DSAPPClientConstantsObjC : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/** Minimum length of the SRP password */
@property(class, nonatomic, readonly) NSInteger srpPwdMinLength;

/** Maximum length of the SRP password */
@property(class, nonatomic, readonly) NSInteger srpPwdMaxLength;

/** Maximum length of the SRP user identifier */
@property(class, nonatomic, readonly) NSInteger srpUserIdMaxLength;

/** Minimum length of the SRP user identifier */
@property(class, nonatomic, readonly) NSInteger srpUserIdMinLength;

/** Length of the session SRP salt */
@property(class, nonatomic, readonly) NSInteger srpSaltLength;

/** Maximum length of the SRP ephemeral key */
@property(class, nonatomic, readonly) NSInteger srpEphemeralKeyMaxLength;

/** Length of the SRP evidence message */
@property(class, nonatomic, readonly) NSInteger srpEvidenceMessageLength;

/** Length of the SRP session key */
@property(class, nonatomic, readonly) NSInteger srpSessionKeyLength;

/** Length of the SRP MAC */
@property(class, nonatomic, readonly) NSInteger srpMacLength;

/** Length of SRP encryption counter */
@property(class, nonatomic, readonly) NSInteger srpEncryptionCounterLength;

@end

NS_ASSUME_NONNULL_END
