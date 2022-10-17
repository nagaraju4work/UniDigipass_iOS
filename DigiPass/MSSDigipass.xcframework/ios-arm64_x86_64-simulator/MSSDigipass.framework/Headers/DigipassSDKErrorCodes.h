//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_REFINED_FOR_SWIFT

/**
 * This class provides the error codes of the Digipass SDK.
 */
@interface DigipassSDKErrorCodes : NSObject

/// The static vector is null
@property(class, nonatomic, readonly) NSInteger returnCodeStaticVectorNull;

/// The static vector length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeStaticVectorIncorrectLength;

/// The static vector format is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeStaticVectorIncorrectFormat;

/// The dynamic vector is null
@property(class, nonatomic, readonly) NSInteger returnCodeDynamicVectorNull;

/// The dynamic vector length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeDynamicVectorIncorrectLength;

/// The dynamic vector format is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeDynamicVectorIncorrectFormat;

/// The encryption key is null
@property(class, nonatomic, readonly) NSInteger returnCodeEncryptionKeyNull;

/// The encryption key length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeEncryptionKeyIncorrectLength;

/// The serial number suffix is null
@property(class, nonatomic, readonly) NSInteger returnCodeSerialNumberSuffixNull;

/// The serial number is null
@property(class, nonatomic, readonly) NSInteger returnCodeSerialNumberNull;

/// The serial number suffix length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeSerialNumberSuffixIncorrectLength;

/// The serial number length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeSerialNumberIncorrectLength;

/// The activation code is null
@property(class, nonatomic, readonly) NSInteger returnCodeActivationCodeNull;

/// The activation code length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeActivationCodeIncorrectLength;

/// The activation code format is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeActivationCodeIncorrectFormat;

/// The event reactivation counter length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeErcIncorrectLength;

/// The event reactivation counter format is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeErcIncorrectFormat;

/// The event reactivation counter is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeErcInvalid;

/// The XFAD is null
@property(class, nonatomic, readonly) NSInteger returnCodeXfadNull;

/// The XFAD length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeXfadIncorrectLength;

/// The XFAD format is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeXfadIncorrectFormat;

/// The XERC length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeXercIncorrectLength;

/// The XERC format is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeXercIncorrectFormat;

/// The cumulative size of the activation password and the nonce is too high (limit: 512 bytes)
@property(class, nonatomic, readonly) NSInteger returnCodeSharedSecretTooLong;

/// The activation code is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeActivationCodeInvalid;

/// The application has been locked in a reactivation case
@property(class, nonatomic, readonly) NSInteger returnCodeReactivationLock;

/// The password is null
@property(class, nonatomic, readonly) NSInteger returnCodePasswordNull;

/// The password is too short
@property(class, nonatomic, readonly) NSInteger returnCodePasswordLengthTooShort;

/// The password is too long
@property(class, nonatomic, readonly) NSInteger returnCodePasswordLengthTooLong;

/// The password is weak
@property(class, nonatomic, readonly) NSInteger returnCodePasswordWeak;

/// The password cannot be validated
@property(class, nonatomic, readonly) NSInteger returnCodePasswordWrong;

/// The application is locked after too many tries with a wrong password
@property(class, nonatomic, readonly) NSInteger returnCodePasswordLock;

/// The DIGIPASS status is invalid (not activated or locked)
@property(class, nonatomic, readonly) NSInteger returnCodeStatusInvalid;

/// The crypto application index is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeCryptoApplicationIndexInvalid;

/// The crypto application is disabled
@property(class, nonatomic, readonly) NSInteger returnCodeApplicationDisabled;

/// The challenge is null
@property(class, nonatomic, readonly) NSInteger returnCodeChallengeNull;

/// The challenge length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeChallengeIncorrectLength;

/// The data fields array is null
@property(class, nonatomic, readonly) NSInteger returnCodeDataFieldsArrayNull;

/// The number of data fields to sign is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeDataFieldsNumberInvalid;

/// One of the data fields to sign is null
@property(class, nonatomic, readonly) NSInteger returnCodeDataFieldNull;

/// One of the data fields to sign length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeDataFieldIncorrectLength;

/// The response is null
@property(class, nonatomic, readonly) NSInteger returnCodeResponseNull;

/// The response length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeResponseIncorrectLength;

/// The host code is null
@property(class, nonatomic, readonly) NSInteger returnCodeHostCodeNull;

/// The host code length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeHostCodeIncorrectLength;

/// One of the data fields to sign contains invalid characters
@property(class, nonatomic, readonly) NSInteger returnCodeChallengeCharacterInvalid;

/// The server public key length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeServerPublicKeyIncorrectLength;

/// The secret key is null
@property(class, nonatomic, readonly) NSInteger returnCodeEbdSecretKeyNull;

/// The secret key length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeEbdSecretKeyIncorrectLength;

/// The session identifier is null
@property(class, nonatomic, readonly) NSInteger returnCodeEbdSessionIdNull;

/// The key handle is null
@property(class, nonatomic, readonly) NSInteger returnCodeEbdKeyHandleNull;

/// The encrypt function array is null
@property(class, nonatomic, readonly) NSInteger returnCodeEbdEncryptFunctionNull;

/// The crypto mechanism is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeCryptoMecanismInvalid;

/// The crypto mode is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeCryptoModeInvalid;

/// The key is null
@property(class, nonatomic, readonly) NSInteger returnCodeKeyNull;

/// The key length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeKeyIncorrectLength;

/// The input data is null
@property(class, nonatomic, readonly) NSInteger returnCodeInputDataNull;

/// The input data length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeInputDataIncorrectLength;

/// The output data length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeInitialVectorIncorrectLength;

/// The property is unknown
@property(class, nonatomic, readonly) NSInteger returnCodeUnknwonProperty;

/// The derivation code is null
@property(class, nonatomic, readonly) NSInteger returnCodeDerivationCodeNull;

/// The derivation code length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeDerivationCodeIncorrectLength;

/// The token derivation is not supported
@property(class, nonatomic, readonly) NSInteger returnCodeTokenDerivationNotSupported;

/// The platform fingerprint is not defined
@property(class, nonatomic, readonly) NSInteger returnCodePlatformFingerprintNotDefined;

/// The data fields are not contiguous
@property(class, nonatomic, readonly) NSInteger returnCodeDataFieldsNotContiguous;

/// The DIGIPASS is not password protected
@property(class, nonatomic, readonly) NSInteger returnCodeNotPasswordProtected;

/// The secure channel message is null
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageNull;

/// The secure channel message format is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageIncorrectFormat;

/// The secure channel message length is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageIncorrectLength;

/// The secure channel message type is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageIncorrectType;

/// The signature of the secure channel message is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageSignatureInvalid;

/// The jailbreak status is invalid
@property(class, nonatomic, readonly) NSInteger returnCodeJailbreakStatusInvalid;

/// The static vector contained in the secure channel message is not equal to the one provided as parameter
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageStaticVectorInconsistent;

/// The platform activation key is invalid because it cannot be validated against its checksum
@property(class, nonatomic, readonly) NSInteger returnCodePlatformActivationKeyInvalid;

/// The multi-device activation is disabled in the DIGIPASS settings
@property(class, nonatomic, readonly) NSInteger returnCodeMultiDeviceActivationDisabled;

/// The DIGIPASS license is incorrect
@property(class, nonatomic, readonly) NSInteger returnCodeLicenseIncorrect;

/// The secure channel message is not dedicated to the current DIGIPASS
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageIncorrectTarget;

/// The multi-device activation is enabled in the DIGIPASS settings
@property(class, nonatomic, readonly) NSInteger returnCodeMultiDeviceActivationEnabled;

/// The secure channel is disabled in the DIGIPASS settings
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelDisabled;

/// The Client Score feature is disabled
@property(class, nonatomic, readonly) NSInteger returnCodeClientScoreDisabled;

/// The score value must be between 0 and 7
@property(class, nonatomic, readonly) NSInteger returnCodeScoreInvalid;

/// The secure channel message body is null
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageBodyNullOrEmpty;

/// The secure channel message body is too long
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageBodyIncorrectLength;

/// The secure channel message body is not hexadecimal
@property(class, nonatomic, readonly) NSInteger returnCodeSecureChannelMessageBodyIncorrectFormat;

/// The protection type is not supported
@property(class, nonatomic, readonly) NSInteger returnCodeProtectionTypeNotSupported;

/// An unknown error has occurred
@property(class, nonatomic, readonly) NSInteger returnCodeUnknownError;

@end

