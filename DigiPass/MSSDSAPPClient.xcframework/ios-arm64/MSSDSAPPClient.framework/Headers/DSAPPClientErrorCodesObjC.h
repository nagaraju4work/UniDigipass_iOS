#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
/**
 * Error codes which can be returned by the DSAPP library in case of error.
 */
@interface DSAPPClientErrorCodesObjC : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/** Internal error */
@property(class, nonatomic, readonly) NSInteger internalError;

/** The checksum cannot be validated. */
@property(class, nonatomic, readonly) NSInteger checksumValidationFailed;

/** Client ephemeral key null or empty */
@property(class, nonatomic, readonly) NSInteger srpClientEphemeralKeyNullOrEmpty;

/** Client ephemeral key too long. Limited to {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} characters */
@property(class, nonatomic, readonly) NSInteger srpClientEphemeralKeyIncorrectLength;

/** Client ephemeral key invalid */
@property(class, nonatomic, readonly) NSInteger srpClientEphemeralKeyInvalid;

/** Client ephemeral key incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpClientEphemeralKeyIncorrectFormat;

/** User identifier null or empty */
@property(class, nonatomic, readonly) NSInteger srpUserIdNullOrEmpty;

/** User identifier too long or too short. Limited to between {@link DSAPPClientConstantsObjC#srpUserIdMinLength} and {@link DSAPPClientConstantsObjC#srpUserIdMaxLength} characters  */
@property(class, nonatomic, readonly) NSInteger srpUserIdIncorrectLength;

/** Password null or empty */
@property(class, nonatomic, readonly) NSInteger srpPasswordNullOrEmpty;

/** Password too long or too short. Limited to between {@link DSAPPClientConstantsObjC#srpPwdMinLength} and {@link DSAPPClientConstantsObjC#srpPwdMaxLength} characters  */
@property(class, nonatomic, readonly) NSInteger srpPasswordIncorrectLength;

/** Salt null or empty */
@property(class, nonatomic, readonly) NSInteger srpSaltNullOrEmpty;

/** Salt incorrect length. Length must be {@link DSAPPClientConstantsObjC#srpSaltLength} characters */
@property(class, nonatomic, readonly) NSInteger srpSaltIncorrectLength;

/** Salt incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpSaltIncorrectFormat;

/** Server ephemeral key null or empty */
@property(class, nonatomic, readonly) NSInteger srpServerEphemeralKeyNullOrEmpty;

/** Server ephemeral key too long. Limited to {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} characters */
@property(class, nonatomic, readonly) NSInteger srpServerEphemeralKeyIncorrectLength;

/** Server ephemeral key invalid */
@property(class, nonatomic, readonly) NSInteger srpServerEphemeralKeyInvalid;

/** Server ephemeral key incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpServerEphemeralKeyIncorrectFormat;

/** Client private key null or empty */
@property(class, nonatomic, readonly) NSInteger srpClientPrivateKeyNullOrEmpty;

/** Client private key too long. Limited to {@link DSAPPClientConstantsObjC#srpEphemeralKeyMaxLength} characters */
@property(class, nonatomic, readonly) NSInteger srpClientPrivateKeyIncorrectLength;

/** Client private key invalid. It does not match client ephemeral key */
@property(class, nonatomic, readonly) NSInteger srpClientPrivateKeyInvalid;

/** Client private key incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpClientPrivateKeyIncorrectFormat;

/** Session key null or empty */
@property(class, nonatomic, readonly) NSInteger srpSessionKeyNullOrEmpty;

/** Session key incorrect length. Length must be {@link DSAPPClientConstantsObjC#srpSessionKeyLength} characters */
@property(class, nonatomic, readonly) NSInteger srpSessionKeyIncorrectLength;

/** Session key incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpSessionKeyIncorrectFormat;

/** Client verification message null or empty */
@property(class, nonatomic, readonly) NSInteger srpClientMessageNullOrEmpty;

/** Client verification message incorrect length. Length must be {@link DSAPPClientConstantsObjC#srpEvidenceMessageLength} characters */
@property(class, nonatomic, readonly) NSInteger srpClientMessageIncorrectLength;

/** Client verification message incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpClientMessageIncorrectFormat;

/** Server verification message null or empty */
@property(class, nonatomic, readonly) NSInteger srpServerMessageNullOrEmpty;

/** Server verification message incorrect length. Length must be {@link DSAPPClientConstantsObjC#srpEvidenceMessageLength} characters */
@property(class, nonatomic, readonly) NSInteger srpServerMessageIncorrectLength;

/** Server verification message incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpServerMessageIncorrectFormat;

/** MAC null or empty */
@property(class, nonatomic, readonly) NSInteger srpMacNullOrEmpty;

/** MAC incorrect length. Length must be {@link DSAPPClientConstantsObjC#srpMacLength} characters */
@property(class, nonatomic, readonly) NSInteger srpMacIncorrectLength;

/** MAC incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpMacIncorrectFormat;

/** Encryption counter null or empty */
@property(class, nonatomic, readonly) NSInteger srpEncryptionCounterNullOrEmpty;

/** Encryption counter incorrect length. Length must be {@link DSAPPConstants_SRP_ENCRYPTION_COUNTER_LENGTH} characters */
@property(class, nonatomic, readonly) NSInteger srpEncryptionCounterIncorrectLength;

/** Encryption counter incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpEncryptionCounterIncorrectFormat;

/** Encrypted data null or empty */
@property(class, nonatomic, readonly) NSInteger srpEncryptedDataNullOrEmpty;

/** Encrypted data incorrect format. It must be hexadecimal */
@property(class, nonatomic, readonly) NSInteger srpEncryptedDataIncorrectFormat;

/** Incorrect decrypted data format. Must be a hexadecimal string.*/
@property(class, nonatomic, readonly) NSInteger srpDecryptedDataIncorrectFormat;

/** Message verification failed */
@property(class, nonatomic, readonly) NSInteger srpMessageVerificationFailed;

/** MAC verification failed */
@property(class, nonatomic, readonly) NSInteger srpMacVerificationFailed;

/** Null or empty data */
@property(class, nonatomic, readonly) NSInteger srpDataNullOrEmpty;

@end

NS_ASSUME_NONNULL_END
