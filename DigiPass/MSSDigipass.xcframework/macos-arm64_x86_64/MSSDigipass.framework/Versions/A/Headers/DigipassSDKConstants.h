//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_REFINED_FOR_SWIFT

/**
 * This class provides the constants of the Digipass SDK.
 */
@interface DigipassSDKConstants : NSObject

/// The DIGIPASS is not activated. An activation must be performed.
@property(class, nonatomic, readonly) NSInteger statusNotActivated;

/// The DIGIPASS is activated. The DIGIPASS is ready to generate OTP or signature.
@property(class, nonatomic, readonly) NSInteger statusActivated;

/// The DIGIPASS is locked. The DIGIPASS could not generate OTP or signature. DIGIPASS must be re-activated.
@property(class, nonatomic, readonly) NSInteger statusLocked;

/// The DIGIPASS generates invalid OTP or invalid signature.
@property(class, nonatomic, readonly) NSInteger statusGenerateInvalidOtp;

/// The DIGIPASS is pre-activated in multi-device activation mode. The license has been provisioned and the second activation step can be performed to provision the instance.
@property(class, nonatomic, readonly) NSInteger statusPreActivated;

/// Index of the first crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp1;

/// Index of the second crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp2;

/// Index of the third crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp3;

/// Index of the fourth crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp4;

/// Index of the fifth crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp5;

/// Index of the sixth crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp6;

/// Index of the seventh crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp7;

/// Index of the eighth crypto application
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexApp8;

/// Index of the activation crypto application (for a multi-device activation purpose)
@property(class, nonatomic, readonly) NSInteger cryptoApplicationIndexAppActivation;

/// Static vector length when using a static vector version lower or equal to 7
@property(class, nonatomic, readonly) NSInteger lengthStaticVectorV7;

/// Static vector maximal length when using a static vector version higher or equal to 8
@property(class, nonatomic, readonly) NSInteger lengthStaticVectorV8Max;

/// Dynamic vector length when using a static vector version lower or equal to 7
@property(class, nonatomic, readonly) NSInteger lengthDynamicVectorV7;

/// Dynamic vector maximal length when using a static vector version higher or equal to 8
@property(class, nonatomic, readonly) NSInteger lengthDynamicVectorV8Max;

/// Data field maximal length
@property(class, nonatomic, readonly) NSInteger lengthDataFieldMax;

/// Data field maximal length for enhanced security
@property(class, nonatomic, readonly) NSInteger lengthDataFieldMaxEnhancedSecurity;

/// Response maximal length
@property(class, nonatomic, readonly) NSInteger lengthResponseMax;

/// Encryption key length
@property(class, nonatomic, readonly) NSInteger lengthHostCodeMax;

/// Encryption key length
@property(class, nonatomic, readonly) NSInteger lengthEncryptionKey;

/// Serial number length
@property(class, nonatomic, readonly) NSInteger lengthSerialNumber;

/// Crypto application name length
@property(class, nonatomic, readonly) NSInteger lengthCryptoApplicationName;

/// Derivation code maximal length
@property(class, nonatomic, readonly) NSInteger lengthDerivationCodeMax;

/// Shared secret maximal length
@property(class, nonatomic, readonly) NSInteger lengthSharedSecretMax;

/// Server public key maximal length
@property(class, nonatomic, readonly) NSInteger lengthServerPublicKeyMax;

/// Master key length
@property(class, nonatomic, readonly) NSInteger lengthMasterKey;

/// Codeword length
@property(class, nonatomic, readonly) NSInteger lengthCodeword;

/// Authentication mode length
@property(class, nonatomic, readonly) NSInteger lengthAuthenticationMode;

/// Secure channel message header length
@property(class, nonatomic, readonly) NSInteger lengthSecureChannelMessageHeader;

/// Secure channel message footer length
@property(class, nonatomic, readonly) NSInteger lengthSecureChannelMessageFooter;

/// Secure channel message maximal length
@property(class, nonatomic, readonly) NSInteger lengthSecureChannelMessageMax;

/// Secure channel message body maximal length
@property(class, nonatomic, readonly) NSInteger lengthSecureChannelMessageBodyMax;

/// Secure channel message nonce length
@property(class, nonatomic, readonly) NSInteger lengthSecureChannelMessageNonce;

/// Maximum number of data fields
@property(class, nonatomic, readonly) NSInteger numberDataFieldMax;

/// DES cipher mechanism
@property(class, nonatomic, readonly) UInt8 cipherMechanismDes;

/// Triple DES cipher mechanism
@property(class, nonatomic, readonly) UInt8 cipherMechanismDes3;

/// AES cipher mechanism
@property(class, nonatomic, readonly) UInt8 cipherMechanismAes;

/// ECB cipher mode
@property(class, nonatomic, readonly) UInt8 cipherModeEcb;

/// CBC cipher mode
@property(class, nonatomic, readonly) UInt8 cipherModeCbc;

/// CFB cipher mode
@property(class, nonatomic, readonly) UInt8 cipherModeCfb;

/// CTR cipher mode
@property(class, nonatomic, readonly) UInt8 cipherModeCtr;

/// The secure channel message is a multi-device license activation message.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageTypeLicenseActivation;

/// The secure channel message is a multi-device instance activation message.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageTypeInstanceActivation;

/// The secure channel message is a deactivation message.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageTypeDeactivation;

/// The secure channel message is a request message.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageTypeRequest;

/// The secure channel message is a response message.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageTypeResponse;

/// The secure channel message is an information message.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageTypeInformationMessage;

/// The jailbreak status is not applicable.
@property(class, nonatomic, readonly) UInt8 jailbreakStatusNa;

/// The jailbreak status is safe.
@property(class, nonatomic, readonly) UInt8 jailbreakStatusSafe;

/// The jailbreak status is unsafe.
@property(class, nonatomic, readonly) UInt8 jailbreakStatusUnsafe;

/// Minimal value for a score when using the Client Score feature.
@property(class, nonatomic, readonly) UInt8 scoreMin;

/// Maximal value for a score when using the Client Score feature.
@property(class, nonatomic, readonly) UInt8 scoreMax;

/// The secure channel message is not protected.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageProtectionNone;

/// The secure channel message is validated using HMAC-SHA256 and its payload is ciphered with AES-128-CTR.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageProtectionHmacAesctr;

/// The secure channel message is validated using HMAC-SHA256 and its payload is not ciphered.
@property(class, nonatomic, readonly) UInt8 secureChannelMessageProtectionHmac;

@end
