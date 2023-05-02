//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <MSSDigipass/DigipassSDK.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This category of DIgipass SDK describes the crypto methods.
 */
@interface DigipassSDK (CryptoMethods)

/**
 * Hash function which can be used during the integration to hash data.
 *
 * @param data Data to hash, MANDATORY, cannot be null
 * @param error raised if there is an error during the process. The following code can be returned:
 * {@link DigipassSDKErrorCodes#returnCodeInputDataNull} if the input data is null
 * @return the hashed data
 */
+ (NSData * _Nullable)sha256Hash:(NSData *)data
                           error:(NSError **)error;

/**
 * Cipher function which can be used during the integration to encrypt data.
 *
 * @param mechanism Cipher mechanism ({@link DigipassSDKConstants#cipherMechanismDes}, {@link DigipassSDKConstants#cipherMechanismDes3}, {@link DigipassSDKConstants#cipherMechanismAes})
 * @param mode Cipher mode ({@link DigipassSDKConstants#cipherModeEcb}, {@link DigipassSDKConstants#cipherModeCbc}, {@link DigipassSDKConstants#cipherModeCfb}, {@link DigipassSDKConstants#cipherModeCtr})
 * @param key Cipher key, MANDATORY, 8 bytes for DES, 16/24 bytes for 3DES, 16/24/32 bytes for AES
 * @param initialVector Initial vector used for the CBC, CFB and CTR modes, MANDATORY in CTR mode, else can be null, fixed length in CBC and CTR modes (8 bytes for DES/3DES, 16 bytes for AES), variable length in CFB mode
 * @param dataIn Data to process, MANDATORY, cannot be null, no length constraint in CFB and CTR modes, length constraint in ECB mode and in CBC mode: 8 bytes multiple for DES/3DES, 16 bytes multiple for AES
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeCryptoMecanismInvalid} if the mechanism is not managed</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeCryptoModeInvalid} if the mode is not managed</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeKeyNull} if the key is null</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeKeyIncorrectLength} if key length is incorrect according to the selected mechanism</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeInputDataNull} if the input bytes array is null</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeInputDataIncorrectLength} if input bytes array length is incorrect according to the selected mechanism</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeInitialVectorIncorrectLength} if the initial vector length is incorrect according to the selected mechanism</li>
 * </ul>
 * @return the encrypted data
 */
+ (NSData * _Nullable)encryptWithMechanism:(UInt8)mechanism
                                      mode:(UInt8)mode
                                       key:(NSData *)key
                             initialVector:(NSData * _Nullable)initialVector
                                    dataIn:(NSData *)dataIn
                                     error:(NSError **)error;

/**
 * Cipher function which can be used during the integration to decrypt data.
 *
 * @param mechanism Cipher mechanism ({@link DigipassSDKConstants#cipherMechanismDes}, {@link DigipassSDKConstants#cipherMechanismDes3}, {@link DigipassSDKConstants#cipherMechanismAes})
 * @param mode Cipher mode ({@link DigipassSDKConstants#cipherModeEcb}, {@link DigipassSDKConstants#cipherModeCbc}, {@link DigipassSDKConstants#cipherModeCfb}, {@link DigipassSDKConstants#cipherModeCtr})
 * @param key Cipher key, MANDATORY, 8 bytes for DES, 16/24 bytes for 3DES, 16/24/32 bytes for AES
 * @param initialVector Initial vector used for the CBC, CFB and CTR modes, MANDATORY in CTR mode, else can be null, fixed length in CBC and CTR modes (8 bytes for DES/3DES, 16 bytes for AES), variable length in CFB mode
 * @param dataIn Data to process, MANDATORY, cannot be null, no length constraint in CFB and CTR modes, length constraint in ECB mode and in CBC mode: 8 bytes multiple for DES/3DES, 16 bytes multiple for AES
 * @param error raised if there is an error during the process. The following codes can be returned:
 * <ul>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeCryptoMecanismInvalid} if the mechanism is not managed</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeCryptoModeInvalid} if the mode is not managed</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeKeyNull} if the key is null</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeKeyIncorrectLength} if key length is incorrect according to the selected mechanism</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeInputDataNull} if the input bytes array is null</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeInputDataIncorrectLength} if input bytes array length is incorrect according to the selected mechanism</li>
 *     <li>{@link DigipassSDKErrorCodes#returnCodeInitialVectorIncorrectLength} if the initial vector length is incorrect according to the selected mechanism</li>
 * </ul>
 * @return the decrypted data
 */
+ (NSData * _Nullable)decryptWithMechanism:(UInt8)mechanism
                                      mode:(UInt8)mode
                                       key:(NSData *)key
                             initialVector:(NSData * _Nullable)initialVector
                                    dataIn:(NSData *)dataIn
                                     error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
