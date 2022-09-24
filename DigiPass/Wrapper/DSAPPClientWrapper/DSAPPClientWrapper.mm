//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "DSAPPClientWrapper.h"
#import <DSAPP_Client/DSAPPClient.h>
#import <DigipassSDK/DP4Capi.h>

@interface SRPSessionKeyResponseWrapper (Wrapper)

- (instancetype)initWithSRPSessionKeyResponse:(SRPSessionKeyResponse)srpSessionKeyResponse;

@end

@interface SRPClientEphemeralKeyResponseWrapper (Wrapper)

- (instancetype)initWithSRPClientEphemeralKeyResponse:(SRPClientEphemeralKeyResponse)srpClientEphemeralKeyResponse;

@end


@implementation DSAPPClientWrapper

+ (NSString *)DSAPPClient_VERSION {
    return [NSString stringWithUTF8String:DSAPPClient_VERSION.c_str()];
}


+ (BOOL)validateSRPUserPasswordChecksum:(NSString *)password error:(NSError * _Nullable * _Nullable)error {
    try {
        string passwordCStr = string([password cStringUsingEncoding:NSUTF8StringEncoding]);
        DSAPPClient::validateSRPUserPasswordChecksum(passwordCStr);
        return YES;
    } catch (DSAPPException &e) {
        *error = [self generateExceptionFromDSAPPError:e.getErrorCode() message:e.getMessage()];
        return NO;
    }
}

+ (SRPClientEphemeralKeyResponseWrapper *)generateSRPClientEphemeralKeyWithError:(NSError * _Nullable *)error {
    try {
        SRPClientEphemeralKeyResponse clientEphemeralKeyResponse;
        DSAPPClient::generateSRPClientEphemeralKey(clientEphemeralKeyResponse);
        return [[SRPClientEphemeralKeyResponseWrapper alloc] initWithSRPClientEphemeralKeyResponse:clientEphemeralKeyResponse];
    } catch (DSAPPException &e) {
        *error = [self generateExceptionFromDSAPPError:e.getErrorCode() message:e.getMessage()];
    }
    return nil;
}

+ (SRPSessionKeyResponseWrapper *)generateSRPSessionKeyWithClientEphemeralPublicKey:(NSString *)clientEphemeralPublicKey
                                                     clientEphemeralPrivateKey:(NSString *)clientEphemeralPrivateKey
                                                      serverEphemeralPublicKey:(NSString *)serverEphemeralPublicKey
                                              registrationIdentifier:(NSString *)registrationIdentifier
                                                            activationPassword:(NSString *)activationPassword
                                                                          salt:(NSString *)salt
                                                                         error:(NSError * _Nullable * _Nullable)error {
    try {
        string clientEphemeralPublicKeyCStr = string([clientEphemeralPublicKey cStringUsingEncoding:NSUTF8StringEncoding]);
        string clientEphemeralPrivateKeyCStr = string([clientEphemeralPrivateKey cStringUsingEncoding:NSUTF8StringEncoding]);
        string serverEphemeralPublicKeyCStr = string([serverEphemeralPublicKey cStringUsingEncoding:NSUTF8StringEncoding]);
        string registrationIdentifierNoPasswordCStr = string([registrationIdentifier cStringUsingEncoding:NSUTF8StringEncoding]);
        string activationPasswordCStr = string([activationPassword cStringUsingEncoding:NSUTF8StringEncoding]);
        string saltCStr = string([salt cStringUsingEncoding:NSUTF8StringEncoding]);
        
        SRPSessionKeyResponse sessionKeyResponse;
        DSAPPClient::generateSRPSessionKey(clientEphemeralPublicKeyCStr,
                                           clientEphemeralPrivateKeyCStr,
                                           serverEphemeralPublicKeyCStr,
                                           registrationIdentifierNoPasswordCStr,
                                           activationPasswordCStr,
                                           saltCStr,
                                           sessionKeyResponse);
        
        return [[SRPSessionKeyResponseWrapper alloc] initWithSRPSessionKeyResponse:sessionKeyResponse];
    } catch (DSAPPException &e) {
        *error = [self generateExceptionFromDSAPPError:e.getErrorCode() message:e.getMessage()];
    }
    return nil;
}

+ (BOOL)verifySRPServerEvidenceMessageWithClientEphemeralPublicKey:(NSString *)clientEphemeralPublicKey
                                             clientEvidenceMessage:(NSString *)clientEvidenceMessage
                                             serverEvidenceMessage:(NSString *)serverEvidenceMessage
                                                  clientSessionKey:(NSString *)clientSessionKey
                                                             error:(NSError * _Nullable * _Nullable)error {
    try {
        string clientEphemeralPublicKeyCStr = std::string([clientEphemeralPublicKey cStringUsingEncoding:NSUTF8StringEncoding]);
        string clientEvidenceMessageCStr = std::string([clientEvidenceMessage cStringUsingEncoding:NSUTF8StringEncoding]);
        string serverEvidenceMessageCStr = std::string([serverEvidenceMessage cStringUsingEncoding:NSUTF8StringEncoding]);
        string clientSessionKeyCStr = std::string([clientSessionKey cStringUsingEncoding:NSUTF8StringEncoding]);
        
        DSAPPClient::verifySRPServerEvidenceMessage(clientEphemeralPublicKeyCStr,
                                                    clientEvidenceMessageCStr,
                                                    serverEvidenceMessageCStr,
                                                    clientSessionKeyCStr);
        return YES;
    } catch (DSAPPException &e) {
        *error = [self generateExceptionFromDSAPPError:e.getErrorCode() message:e.getMessage()];
        return NO;
    }
}

+ (NSString *)decryptSRPDataWithClientSessionKey:(NSString *)clientSessionKey
                                   encryptedData:(NSString *)encryptedData
                                encryptedCounter:(NSString *)encryptedCounter
                                             MAC:(NSString *)MAC
                                           error:(NSError * _Nullable * _Nullable)error {
    byte *decryptedDataBytes = NULL;
    try {
        string clientSessionKeyCStr = std::string([clientSessionKey cStringUsingEncoding:NSUTF8StringEncoding]);
        string encryptedDataCStr = std::string([encryptedData cStringUsingEncoding:NSUTF8StringEncoding]);
        string encryptedCounterCStr = std::string([encryptedCounter cStringUsingEncoding:NSUTF8StringEncoding]);
        string macCStr = std::string([MAC cStringUsingEncoding:NSUTF8StringEncoding]);
        
        long decryptedDataBufferLength = encryptedDataCStr.length() / 2;
        decryptedDataBytes = (byte *) malloc(decryptedDataBufferLength * sizeof(unsigned char));
        memset(decryptedDataBytes, 0, (size_t) decryptedDataBufferLength);
        DSAPPClient::decryptSRPData(clientSessionKeyCStr,
                                    encryptedDataCStr,
                                    encryptedCounterCStr,
                                    macCStr,
                                    decryptedDataBytes,
                                    &decryptedDataBufferLength);
        
        NSString *decryptedData = [[NSString alloc] initWithBytes:decryptedDataBytes length:(NSUInteger) decryptedDataBufferLength encoding:NSUTF8StringEncoding];
        free(decryptedDataBytes);
        
        return decryptedData;
    } catch (DSAPPException &e) {
        free(decryptedDataBytes);
        *error = [self generateExceptionFromDSAPPError:e.getErrorCode() message:e.getMessage()];
    }
    return nil;
}


+ (BOOL)verifySRPMACWithClientSessionKey:(NSString *)clientSessionKey
                           bytesToVerify:(NSData *)bytesToVerify
                                     MAC:(NSString *)MAC
                                   error:(NSError * _Nullable * _Nullable)error {
    byte *bytes = NULL;
    try {
        string macCStr = std::string([MAC cStringUsingEncoding:NSUTF8StringEncoding]);
        string clientSessionKeyCStr = std::string([clientSessionKey cStringUsingEncoding:NSUTF8StringEncoding]);
        NSUInteger bytesBufferLength = [bytesToVerify length];
        bytes = (byte *) malloc(bytesBufferLength);
        memcpy(bytes, [bytesToVerify bytes], bytesBufferLength);
        
        DSAPPClient::verifySRPMAC(clientSessionKeyCStr, bytes, (long) bytesBufferLength, macCStr);
        free(bytes);
        return YES;
    } catch (DSAPPException &e) {
        free(bytes);
        *error = [self generateExceptionFromDSAPPError:e.getErrorCode() message:e.getMessage()];
        return NO;
    }
}

#pragma mark - private

+ (NSError *)generateExceptionFromDSAPPError:(int)errorCode message:(string)message {
    return [[NSError alloc] initWithCode:errorCode message:[NSString stringWithUTF8String:message.c_str()]];
}

@end
