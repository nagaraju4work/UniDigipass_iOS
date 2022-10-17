//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <MSSDigipass/DigipassSDKGenericResponse.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
/**
 * Defines a response to a derivation code generation request.
 */
@interface DigipassSDKGenerateDerivationCodeResponse : DigipassSDKGenericResponse

/// Derivation code.
@property (nonatomic, copy, readonly) NSString *derivationCode;

@end

NS_ASSUME_NONNULL_END
