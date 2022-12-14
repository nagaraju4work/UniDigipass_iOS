//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DigipassSDKApplication;

NS_REFINED_FOR_SWIFT
/**
 * Defines a response to a get DIGIPASS properties request.
 */
@interface DigipassPropertiesResponse : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy, nullable) NSString * xfad;
@property (nonatomic, copy, nullable) NSData * staticVector;
@property (nonatomic, copy, nullable) NSData * dynamicVector;

/// Version
@property (nonatomic, readonly) NSInteger version;

/// Status
@property (nonatomic, readonly) NSInteger status;

/// Event counter.
@property (nonatomic, readonly) NSInteger eventCounter;

/// Password mandatory
@property (nonatomic, readonly) BOOL passwordMandatory;

/// Minimum length of the password
@property (nonatomic, readonly) NSInteger passwordMinLength;

/// Maximum length of the password
@property (nonatomic, readonly) NSInteger passwordMaxLength;

/// Password check level
@property (nonatomic, readonly) NSInteger passwordCheckLevel;

/// Password fatal
@property (nonatomic, readonly) NSInteger passwordFatal;

/// Password fatal counter
@property (nonatomic, readonly) NSInteger passwordFatalCounter;

/// Reactivation fatal
@property (nonatomic, readonly) NSInteger reactivationFatal;

/// Reactivation fatal counter
@property (nonatomic, readonly) NSInteger reactivationFatalCounter;

/// Iteration number
@property (nonatomic, readonly) NSInteger iterationNumber;

/// Iteration power
@property (nonatomic, readonly) NSInteger iterationPower;

/// PIN Version
@property (nonatomic, readonly) NSInteger pinVersion;

/// Storage version
@property (nonatomic, readonly) NSInteger storageVersion;

/// Creation version
@property (nonatomic, readonly) NSInteger creationVersion;

/// Number of bits used during the derivation process
@property (nonatomic, readonly) NSInteger deviceIdBitsNumber;

/// Device type, used in multi-device activation mode
@property (nonatomic, readonly) NSInteger deviceType;

/// Sequence number, used in multi-device activation mode
@property (nonatomic, readonly) NSInteger sequenceNumber;

/// Payload key type, 0 for AES-128, used in multi-device activation mode
@property (nonatomic, readonly) NSInteger payloadKeyType;

/// Serial number
@property (nonatomic, copy, readonly) NSString * serialNumber;

/// UTC time
@property (nonatomic, readonly) NSInteger utcTime;

/// Master key
@property (nonatomic, copy, readonly) NSData * masterKey;

/// Weak password control
@property (nonatomic, readonly) BOOL weakPasswordControl;

/// True if a reset action must be applied when the penalty threshold is reached
@property (nonatomic, readonly) BOOL penaltyResetAction;

/// Token derivation supported
@property (nonatomic, readonly) BOOL tokenDerivationSupported;

/// Flag indicating if the Digipass is high security
@property (nonatomic, readonly) BOOL highSecurity;

/// Flag indicating if the activation code format is hexadecimal (else it is decimal)
@property (nonatomic, readonly) BOOL activationCodeFormatHexa;

/// True if a checksum if included in the activation code
@property (nonatomic, readonly) BOOL useChecksumForActivationCode;

/// Password protected
@property (nonatomic, readonly) BOOL passwordProtected;

/// Use secret derivation
@property (nonatomic, readonly) BOOL useSecretDerivation;

/// Token derivation activated
@property (nonatomic, readonly) BOOL tokenDerivationActivated;

/// Password derivation activated
@property (nonatomic, readonly) BOOL passwordDerivationActivated;

/// Multi-device activation enabled
@property (nonatomic, readonly) BOOL multiDeviceActivationEnabled;

/// Secure channel enabled
@property (nonatomic, readonly) BOOL secureChannelEnabled;

/// Applications list (see {@link DigipassSDKApplication})
@property (nonatomic, copy, readonly) NSArray<DigipassSDKApplication *> *applications;

@end

NS_ASSUME_NONNULL_END
