//
//  DIGIPassClientSDKWrapper.m
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

#import "DIGIPassClientSDKWrapper.h"
#import <MSSDeviceBinding/MSSDeviceBinding.h>
#import "DigiPass-Swift.h"
#import "DigiPassSharedData.h"
#import "Constants.h"
#import <FirebaseAnalytics/FirebaseAnalytics.h>

@interface NSString (NSStringHexToBytes)

- (NSData *) stringToHexData;

@end

@implementation NSString (NSStringHexToBytes)

- (NSData *) stringToHexData
{
    long len = [self length] / 2;    // Target length
    unsigned char *buf = malloc(len);
    unsigned char *whole_byte = buf;
    char byte_chars[3] = {'\0','\0','\0'};
    
    int i;
    for (i=0; i < [self length] / 2; i++) {
        byte_chars[0] = [self characterAtIndex:i*2];
        byte_chars[1] = [self characterAtIndex:i*2+1];
        *whole_byte = strtol(byte_chars, NULL, 16);
        whole_byte++;
    }
    
    NSData *data = [NSData dataWithBytes:buf length:len];
    free( buf );
    return data;
}

@end


@implementation DIGIPassClientSDKWrapper
NSString *teamId = @"Kannan Nagaian";
NSString *errorDomain = @"DigiPassSDKErrorDomain";

+ (void) zeroAndFreeWithByte:(vds_byte *) toClean length:(vds_int32) length {
    memset(toClean, 0, length);
    free(toClean);
}

+ (SecureChannelMessageWrapper *) parseSecureChannelMessage:(NSString *)message {
    const char* c = [message UTF8String];
    SecureChannelMessage channelMessage;
    vds_int32 returnCode = DPSDK_ParseSecureChannelMessage((char *)c, &channelMessage);
    
    if (returnCode != RETURN_CODE_SUCCESS) {
       
        [FIRAnalytics logEventWithName:@"ParseSecureChannelMessage"
                            parameters:@{
                                         @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                         }];
        return nil;
    }else {
        return [[SecureChannelMessageWrapper alloc] initWithSecureChannel:channelMessage];
    }
}

+ (id<AccessGroup>)getAppPrivateAccessGroup
{
    return [[AppPrivate alloc] initWithTeamId:teamId bundleId:@"com.unicorp.adpolice.gov"];
}

+ (void) multiDeviceLicenceActivation {
    
    @try {
        NSError* error;
        NSString* decrpted = [[[DigiPassSharedData sharedInstance] secureCache] getStringForKey:kDecryptedMessage error:&error];
        SecureChannelMessageWrapper* channelWrapper = [DIGIPassClientSDKWrapper parseSecureChannelMessage:decrpted];
        SecureChannelMessage message = channelWrapper.message;
        
        NSString* platformfingerPrint = [[DeviceBindingSDK getInstance]
                                         fingerprintForSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]
                                         inAccessGroup:[DIGIPassClientSDKWrapper getAppPrivateAccessGroup]
                                         error:&error];
        
//        NSString* platformfingerPrint =  [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]];
        
        vds_ascii *fingerPrint = (vds_ascii*) [platformfingerPrint UTF8String];
        vds_byte jailBreakStatus = 0;
        
        vds_byte staticVector[LENGTH_STATIC_VECTOR_V8_MAX];
        vds_byte dynamicVector[LENGTH_DYNAMIC_VECTOR_V8_MAX];
        vds_int32 staticVectorLength = sizeof(staticVector);
        vds_int32 dynamicVectorLength = sizeof(dynamicVector);
        vds_ascii deviceCode[LENGTH_DERIVATION_CODE_MAX + 1];
        
        memset(staticVector, 0, staticVectorLength);
        memset(dynamicVector, 0, dynamicVectorLength);
        memset(deviceCode, 0, sizeof(deviceCode));
        vds_int32 clientServerTimeShift = [DIGIPassClientSDKWrapper fetchServerTimeSS];
        vds_int32 returnCode = DPSDK_MultiDeviceActivateLicense(&message, NULL, fingerPrint, jailBreakStatus, clientServerTimeShift, staticVector, &staticVectorLength, dynamicVector, &dynamicVectorLength, deviceCode, sizeof(deviceCode));
        
        if (returnCode == RETURN_CODE_SUCCESS) {
            NSData* DC = [NSData dataWithBytes:deviceCode length:sizeof(deviceCode)];
            NSData* staticVectorData = [NSData dataWithBytes:staticVector length:staticVectorLength];
            NSData* dynamicVectorData = [NSData dataWithBytes:dynamicVector length:dynamicVectorLength];
            
            [[[DigiPassSharedData sharedInstance] secureCache] putBytesForBytes:DC forKey:@"deviceCode" error:nil];
            NSString* type = [[NSUserDefaults standardUserDefaults] objectForKey:kActivationType];
            
            NSString* userName =  [[[DigiPassSharedData sharedInstance] secureCache] getStringForKey:kUserName error:nil];
            [[[DigiPassSharedData sharedInstance] secureCache] putBytesForBytes:staticVectorData forKey:[NSString stringWithFormat:@"%@_%@", userName, kStaticVectorData] error: nil];
            
            [[DigiPassSharedData sharedInstance] storeDynamicVectorInVolatile:dynamicVectorData vectorType:type];
            
        }else {
            [FIRAnalytics logEventWithName:@"MultiDeviceLicenceActivation"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                             }];
        }
    } @catch (NSException *exception) {
        [FIRAnalytics logEventWithName:@"MultiDeviceLicenceActivation"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    } @finally {
        
    }
}

+ (MDActivateInstanceModelWrapper *) multiDeviceActivateInstance:(NSString *) password {
    @try {
        
        NSError* error;
        NSString* decrpted = [[[DigiPassSharedData sharedInstance] secureCache] getStringForKey:kActivatedMessage error:&error];
        SecureChannelMessageWrapper* channelWrapper = [DIGIPassClientSDKWrapper parseSecureChannelMessage:decrpted];
        SecureChannelMessage message = channelWrapper.message;
        
        NSString* platformfingerPrint = [[DeviceBindingSDK getInstance]
                                         fingerprintForSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]
                                         inAccessGroup:[DIGIPassClientSDKWrapper getAppPrivateAccessGroup]
                                         error:&error];
        
//        NSString* platformfingerPrint =  [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]];
        
        NSDictionary* vectors = [[DigiPassSharedData sharedInstance] fetchVectorsFromVolatile];
        NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
        NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
        
        vds_int32 svBytesLength = (vds_int32) staticVectorData.length;
        vds_byte* svBytes = (vds_byte*) malloc(sizeof(vds_byte) * svBytesLength);
        [staticVectorData getBytes:svBytes length:svBytesLength];
        
        memset(svBytes, 0, svBytesLength);
        memcpy(svBytes, [staticVectorData bytes], svBytesLength);
        
        vds_int32 dynamicVectorLength = 0;
        vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(svBytes, svBytesLength, &dynamicVectorLength);
        
        if(returnCode1 != RETURN_CODE_SUCCESS) {
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:svBytes length:svBytesLength];
            error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];
//            error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
            return nil;
        }
        
        vds_byte* dvBytes = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
        [dynamicVectorData getBytes:dvBytes length:dynamicVectorLength];
        
        memset(dvBytes, 0, dynamicVectorLength);
        memcpy(dvBytes, [dynamicVectorData bytes], dynamicVectorLength);
        
        vds_ascii* fingerprint = (char *) [platformfingerPrint UTF8String];
        vds_ascii* cPassword = (char *) [password UTF8String];
        
        vds_int32 returnCode = DPSDK_MultiDeviceActivateInstance(svBytes, svBytesLength, dvBytes, dynamicVectorLength, &message, cPassword, fingerprint);
        
        if (returnCode != RETURN_CODE_SUCCESS) {
            [FIRAnalytics logEventWithName:@"multiDeviceActivateInstance"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                             }];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:svBytes length:svBytesLength];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dvBytes length:dynamicVectorLength];
            
        }else {
            NSData* dvd = [NSData dataWithBytes:dvBytes length:dynamicVectorLength];
            [[DigiPassSharedData sharedInstance] storeDynamicVectorInVolatile:dvd vectorType:vectors[kIsPinSelected]];
            
            MDActivateInstanceModelWrapper* model = [[MDActivateInstanceModelWrapper alloc]init];
            model.message = message;
            
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:svBytes length:svBytesLength];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dvBytes length:dynamicVectorLength];
            
            return model;
        }
    } @catch (NSException *exception) {
        [FIRAnalytics logEventWithName:@"multiDeviceActivateInstance"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    } @finally {
       
    }
}

+ (MDGenerateSignatureModelWrapper *) generateSignatureFromPassword: (NSString *) password
                                                              isActivateProcess:(BOOL)isActivate {
    @try {
        
        NSError* error;
        NSString* decrpted = [[[DigiPassSharedData sharedInstance] secureCache] getStringForKey:kActivatedMessage error:&error];
        SecureChannelMessageWrapper* channelWrapper = [DIGIPassClientSDKWrapper parseSecureChannelMessage:decrpted];
        SecureChannelMessage message = channelWrapper.message;
        
        NSString* platformfingerPrint = [[DeviceBindingSDK getInstance]
                                         fingerprintForSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]
                                         inAccessGroup:[DIGIPassClientSDKWrapper getAppPrivateAccessGroup]
                                         error:&error];
        
//        NSString* platformfingerPrint =  [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]];
        
        NSDictionary* vectors = isActivate ? [[DigiPassSharedData sharedInstance] fetchVectorsFromVolatile] : [[DigiPassSharedData sharedInstance] fetchUserVectors];
        NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
        NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
        
        vds_int32 staticVectorLength = (vds_int32) staticVectorData.length;
        vds_byte* staticVector = (vds_byte*) malloc(sizeof(vds_byte) * staticVectorLength);
        [staticVectorData getBytes:staticVector length:staticVectorLength];
        
        memset(staticVector, 0, staticVectorLength);
        memcpy(staticVector, [staticVectorData bytes], staticVectorLength);
        
        vds_int32 dynamicVectorLength = 0;
        vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(staticVector, staticVectorLength, &dynamicVectorLength);
        
        if(returnCode1 != RETURN_CODE_SUCCESS) {
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];
//            error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
            [FIRAnalytics logEventWithName:@"generateSignatureFromPassword"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode1)]
                                             }];
            return nil;
        }
        
        vds_byte* dynamicVector = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
        [dynamicVectorData getBytes:dynamicVector length:dynamicVectorLength];
        
        memset(dynamicVector, 0, dynamicVectorLength);
        memcpy(dynamicVector, [dynamicVectorData bytes], dynamicVectorLength);
        
        vds_ascii* cPassword = (char *) [password UTF8String];
        vds_ascii* fingerprint = (char *) [platformfingerPrint UTF8String];
        
        vds_ascii response[LENGTH_RESPONSE_MAX + 1];
        vds_int32 responseLength = sizeof(response);
        memset(response, 0, responseLength);
        
        vds_ascii hostCode[LENGTH_HOST_CODE_MAX + 1];
        vds_int32 hostCodeLength = sizeof(hostCode);
        memset(hostCode, 0, hostCodeLength);
        
        vds_int32 cryptoApplicationIndex = CRYPTO_APPLICATION_INDEX_APP_1;
        
        vds_int32 clientServerTimeShift = [DIGIPassClientSDKWrapper fetchServerTimeSS];
        vds_int32 returnCode = DPSDK_GenerateSignatureFromSecureChannelMessage(staticVector, staticVectorLength, dynamicVector, dynamicVectorLength, &message, cPassword, clientServerTimeShift, cryptoApplicationIndex, fingerprint, response,responseLength, hostCode, hostCodeLength);
        
        NSData* dvd = [NSData dataWithBytes:dynamicVector length:dynamicVectorLength];
        if (isActivate) {
            [[DigiPassSharedData sharedInstance] storeDynamicVectorInVolatile:dvd vectorType:vectors[kIsPinSelected]];
        }else {
            [[DigiPassSharedData sharedInstance] storeVectorsDV:dvd];
        }
        
        if (returnCode != RETURN_CODE_SUCCESS) {
            [FIRAnalytics logEventWithName:@"generateSignatureFromPassword"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                             }];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
            
        }else {
            
            MDGenerateSignatureModelWrapper* model = [[MDGenerateSignatureModelWrapper alloc]init];
            model.responseData = [NSData dataWithBytes:response length:responseLength];
            model.hostCodeData = [NSData dataWithBytes:hostCode length:hostCodeLength];
            if ([password length] > 0) {
                model.pin = password;
            }
            
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
            
            return model;
        }
    } @catch (NSException *exception) {
        [FIRAnalytics logEventWithName:@"generateSignatureFromPassword"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    } @finally {
       
    }
   
}

+ (BOOL) checkWeakPassword:(NSString *)pin {
    vds_ascii* password = (vds_ascii *) [pin UTF8String];
    vds_bool isPasswordWeak = DPSDK_IsPasswordWeak(password);
    return isPasswordWeak;
}

+ (NSMutableDictionary *) validatePassword: (NSString *) pin {
    NSError* error;
    NSString* platformfingerPrint = [[DeviceBindingSDK getInstance]
                                     fingerprintForSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]
                                     inAccessGroup:[DIGIPassClientSDKWrapper getAppPrivateAccessGroup]
                                     error:&error];
    
//    NSString* platformfingerPrint =  [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]];
    
    vds_ascii* fingerprint = (vds_ascii *) [platformfingerPrint UTF8String];

    NSDictionary* vectors = [[DigiPassSharedData sharedInstance] fetchUserVectors];
    NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
    NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
    
    vds_int32 staticVectorLength = (vds_int32) staticVectorData.length;
    vds_byte* staticVector = (vds_byte*) malloc(sizeof(vds_byte) * staticVectorLength);
    [staticVectorData getBytes:staticVector length:staticVectorLength];
    
    memset(staticVector, 0, staticVectorLength);
    memcpy(staticVector, [staticVectorData bytes], staticVectorLength);
    
    vds_int32 dynamicVectorLength = 0;
    vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(staticVector, staticVectorLength, &dynamicVectorLength);
    
    if(returnCode1 != RETURN_CODE_SUCCESS) {
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
        error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];
//        error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
        [FIRAnalytics logEventWithName:@"validatePassword"
                            parameters:@{
                                         @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode1)]
                                         }];
        return nil;
    }
    
    vds_byte* dynamicVector = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
    [dynamicVectorData getBytes:dynamicVector length:dynamicVectorLength];
    
    memset(dynamicVector, 0, dynamicVectorLength);
    memcpy(dynamicVector, [dynamicVectorData bytes], dynamicVectorLength);
    
    vds_ascii* cPassword = (char *) [pin UTF8String];
    
    vds_ascii encryptionKey[16];
    vds_int32 encryptionKeyLength = sizeof(encryptionKey);
    memset(encryptionKey, 0, encryptionKeyLength);
    
    vds_int32 returnCode = DPSDK_ValidatePasswordWithFingerprint(staticVector, staticVectorLength, dynamicVector, dynamicVectorLength, cPassword, fingerprint, encryptionKey, encryptionKeyLength);
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc]init];
    [dict setObject:[NSNumber numberWithBool:true] forKey:@"status"];
  
    NSData* dvd = [NSData dataWithBytes:dynamicVector length:dynamicVectorLength];
    
    [[DigiPassSharedData sharedInstance] storeVectorsDV:dvd];
    
    [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
    [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
    
    if (returnCode != RETURN_CODE_SUCCESS) {
        [FIRAnalytics logEventWithName:@"validatePassword"
                            parameters:@{
                                         @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                         }];
       NSString* remainsCount = [DIGIPassClientSDKWrapper getDigiPassPropertyInt:PROPERTY_PASSWORD_FATAL_COUNTER cryptoIndex:CRYPTO_APPLICATION_INDEX_APP_2];
        
        NSString* str = [NSString stringWithFormat:@"Entered password is wrong, you have only %@ attempts", remainsCount];
        [dict setObject:[NSNumber numberWithBool:false] forKey:@"status"];
        [dict setObject:str forKey:@"error"];
        return dict;
    }

    return dict;
}

+ (NSString *) generateOTPCodeForPin:(NSString *) pin {

    NSError* error;
    @try {
        NSString* platformfingerPrint = [[DeviceBindingSDK getInstance]
                                         fingerprintForSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]
                                         inAccessGroup:[DIGIPassClientSDKWrapper getAppPrivateAccessGroup]
                                         error:&error];
        
//        NSString* platformfingerPrint =  [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]];
        
        NSDictionary* vectors = [[DigiPassSharedData sharedInstance] fetchUserVectors];
        NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
        NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
        
        vds_int32 staticVectorLength = (vds_int32) staticVectorData.length;
        vds_byte* staticVector = (vds_byte*) malloc(sizeof(vds_byte) * staticVectorLength);
        [staticVectorData getBytes:staticVector length:staticVectorLength];
        
        memset(staticVector, 0, staticVectorLength);
        memcpy(staticVector, [staticVectorData bytes], staticVectorLength);
        
        vds_int32 dynamicVectorLength = 0;
        vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(staticVector, staticVectorLength, &dynamicVectorLength);
        
        if(returnCode1 != RETURN_CODE_SUCCESS) {
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];
//            error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
            [FIRAnalytics logEventWithName:@"generateOTPCodeForPin"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode1)]
                                             }];
            return nil;
        }
        
        vds_byte* dynamicVector = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
        [dynamicVectorData getBytes:dynamicVector length:dynamicVectorLength];
        
        memset(dynamicVector, 0, dynamicVectorLength);
        memcpy(dynamicVector, [dynamicVectorData bytes], dynamicVectorLength);
        
        vds_ascii* cPassword = (char *) [pin UTF8String];
        vds_ascii* fingerprint = (char *) [platformfingerPrint UTF8String];
        
        vds_ascii response[LENGTH_RESPONSE_MAX + 1];
        vds_int32 responseLength = sizeof(response);
        memset(response, 0, responseLength);
        
        vds_ascii hostCode[LENGTH_HOST_CODE_MAX + 1];
        vds_int32 hostCodeLength = sizeof(hostCode);
        memset(hostCode, 0, hostCodeLength);
        
        vds_int32 clientServerTimeShift = [DIGIPassClientSDKWrapper fetchServerTimeSS];

        vds_int32 returnCode = DPSDK_GenerateResponseOnly(staticVector, staticVectorLength, dynamicVector, dynamicVectorLength, cPassword, clientServerTimeShift, CRYPTO_APPLICATION_INDEX_APP_2 , fingerprint, response, responseLength, hostCode, hostCodeLength);
        
        NSData* d = [NSData dataWithBytes:response length:responseLength];
        NSData* dvd = [NSData dataWithBytes:dynamicVector length:dynamicVectorLength];
        
        [[DigiPassSharedData sharedInstance] storeVectorsDV:dvd];
        
        @try {
            if (returnCode != RETURN_CODE_SUCCESS) {
                [FIRAnalytics logEventWithName:@"generateOTPCodeForPin"
                                    parameters:@{
                                                 @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                                 }];
            }else {
                
                return [[NSString alloc]initWithData:d encoding:NSUTF8StringEncoding];
            }
        }  @finally {
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
        }
        
    }@catch (NSException * exception) {
        [FIRAnalytics logEventWithName:@"decryptSecureChannelMessageBody"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    }@finally {
        
    }
}

+ (vds_int32) computeClientServerTimeShiftFromServerTime:(vds_int32) time {
    @try {
        vds_int32 timeShift = DPSDK_ComputeClientServerTimeShiftFromServerTime(time);
        return timeShift;
    }@catch (NSException *e) {
        [FIRAnalytics logEventWithName:@"computeClientServerTimeShift"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
    }@finally {
        
    }
}

+ (vds_int32) fetchServerTimeSS  {
    NSError* error;
    @try {
        NSString* timeStr = [[[DigiPassSharedData sharedInstance] secureStorage] getStringForKey:kServerTime error:&error];
        vds_int32 serverTime = [timeStr intValue];
        return serverTime;
    }@catch (NSException *e) {
        [FIRAnalytics logEventWithName:@"computeClientServerTimeShift"
                            parameters:@{
                                         @"error":  e.reason
                                         }];
    }@finally {
        
    }
}


#pragma mark Notification methods

+ (SecureChannelMessageWrapper *) generateSecureChannelINotificationToken:(NSString *)notificationToken  {
    NSError* error;
    NSString* platformfingerPrint = [[DeviceBindingSDK getInstance]
                                     fingerprintForSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]
                                     inAccessGroup:[DIGIPassClientSDKWrapper getAppPrivateAccessGroup]
                                     error:&error];
//    NSString* platformfingerPrint =  [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]];

    NSDictionary* vectors = [[DigiPassSharedData sharedInstance] fetchUserVectors];
    NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
    NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
    
    vds_int32 staticVectorLength = (vds_int32) staticVectorData.length;
    vds_byte* staticVector = (vds_byte*) malloc(sizeof(vds_byte) * staticVectorLength);
    [staticVectorData getBytes:staticVector length:staticVectorLength];
    
    memset(staticVector, 0, staticVectorLength);
    memcpy(staticVector, [staticVectorData bytes], staticVectorLength);
    
    vds_int32 dynamicVectorLength = 0;
    vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(staticVector, staticVectorLength, &dynamicVectorLength);
    
    if(returnCode1 != RETURN_CODE_SUCCESS) {
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
        error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];
//        error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
        [FIRAnalytics logEventWithName:@"generateSecureChannelINotificationToken"
                            parameters:@{
                                         @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode1)]
                                         }];
        return nil;
    }
    
    vds_byte* dynamicVector = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
    [dynamicVectorData getBytes:dynamicVector length:dynamicVectorLength];
    
    memset(dynamicVector, 0, dynamicVectorLength);
    memcpy(dynamicVector, [dynamicVectorData bytes], dynamicVectorLength);

    vds_ascii* notification = (char *) [notificationToken UTF8String];
    vds_ascii* fingerprint = (char *) [platformfingerPrint UTF8String];
    SecureChannelMessage channelMessage;
    
    vds_int32 returnCode = DPSDK_GenerateSecureChannelInformationMessage(staticVector, staticVectorLength, dynamicVector,dynamicVectorLength, notification, SECURE_CHANNEL_MESSAGE_PROTECTION_HMAC_AESCTR, fingerprint, &channelMessage);
   
    
    @try {
        if (returnCode != RETURN_CODE_SUCCESS) {
            [FIRAnalytics logEventWithName:@"generateSecureChannelINotificationToken"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                             }];
        }else {
            SecureChannelMessageWrapper* model = [[SecureChannelMessageWrapper alloc] initWithSecureChannel:channelMessage];
            return model;
        }
    } @catch (NSException *exception) {
        [FIRAnalytics logEventWithName:@"generateSecureChannelINotificationToken"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    } @finally {
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];

    }
    
}

+ (NSString *) getDigiPassPropertyInt:(vds_int32) property cryptoIndex:(vds_int32) cryptoAppIdx {
   
    NSDictionary* vectors = [[DigiPassSharedData sharedInstance] fetchUserVectors];
    NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
    NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
    
    vds_int32 staticVectorLength = (vds_int32) staticVectorData.length;
    vds_byte* staticVector = (vds_byte*) malloc(sizeof(vds_byte) * staticVectorLength);
    [staticVectorData getBytes:staticVector length:staticVectorLength];
    
    memset(staticVector, 0, staticVectorLength);
    memcpy(staticVector, [staticVectorData bytes], staticVectorLength);
    
    vds_int32 dynamicVectorLength = 0;
    vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(staticVector, staticVectorLength, &dynamicVectorLength);
    NSError *error;
    
    if(returnCode1 != RETURN_CODE_SUCCESS) {
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
        error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];
//        error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
        [FIRAnalytics logEventWithName:@"getDigiPassProperty"
                            parameters:@{
                                         @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode1)]
                                         }];
        return nil;
    }
    
    vds_byte* dynamicVector = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
    [dynamicVectorData getBytes:dynamicVector length:dynamicVectorLength];
    
    memset(dynamicVector, 0, dynamicVectorLength);
    memcpy(dynamicVector, [dynamicVectorData bytes], dynamicVectorLength);

    vds_byte value;
    
    vds_int32 returnCode = DPSDK_GetDigipassProperty(staticVector, staticVectorLength, dynamicVector, dynamicVectorLength, property, &value, sizeof(value), cryptoAppIdx);
    
   
    @try {
        if (returnCode != RETURN_CODE_SUCCESS) {
            NSLog(@"%@", [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]);
            [FIRAnalytics logEventWithName:@"getDigiPassProperty"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                             }];
        }else {
            return [NSString stringWithFormat:@"%hhu", value];
        }
    } @catch (NSException *exception) {
        [FIRAnalytics logEventWithName:@"getDigiPassProperty"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    } @finally {
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
    }
}

+ (NSString *) getDigiPassPropertyStr:(vds_int32) property valueLength: (vds_int32) valueLength
                          cryptoIndex:(vds_int32) cryptoAppIdx {
   
    NSDictionary* vectors = [[DigiPassSharedData sharedInstance] fetchUserVectors];
    NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
    NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
    
    vds_int32 staticVectorLength = (vds_int32) staticVectorData.length;
    vds_byte* staticVector = (vds_byte*) malloc(sizeof(vds_byte) * staticVectorLength);
    [staticVectorData getBytes:staticVector length:staticVectorLength];
    
    memset(staticVector, 0, staticVectorLength);
    memcpy(staticVector, [staticVectorData bytes], staticVectorLength);
    
    vds_int32 dynamicVectorLength = 0;
    vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(staticVector, staticVectorLength, &dynamicVectorLength);
    NSError *error;
    
    if(returnCode1 != RETURN_CODE_SUCCESS) {
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
        error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];

//        error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
        [FIRAnalytics logEventWithName:@"getDigiPassProperty"
                            parameters:@{
                                         @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode1)]
                                         }];
        return nil;
    }
    
    vds_byte* dynamicVector = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
    [dynamicVectorData getBytes:dynamicVector length:dynamicVectorLength];
    
    memset(dynamicVector, 0, dynamicVectorLength);
    memcpy(dynamicVector, [dynamicVectorData bytes], dynamicVectorLength);

    vds_ascii* value;
    value = (vds_ascii*)malloc(sizeof(vds_ascii) * valueLength);
    memset(value, 0, valueLength);
    
    vds_int32 returnCode = DPSDK_GetDigipassProperty(staticVector, staticVectorLength, dynamicVector, dynamicVectorLength, property, value, valueLength, cryptoAppIdx);
    
    @try {
        if (returnCode != RETURN_CODE_SUCCESS) {
            NSLog(@"%@", [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]);
            [FIRAnalytics logEventWithName:@"getDigiPassProperty"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                             }];
        }else {
            return [NSString stringWithFormat:@"%s", value];
        }
    } @catch (NSException *exception) {
        [FIRAnalytics logEventWithName:@"getDigiPassProperty"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    } @finally {
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
        [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
    }
}

+ (NSString *) decryptSecureChannelMessageBody {
    
    @try {
        NSError* error;
        NSString* decrpted = [[[DigiPassSharedData sharedInstance] secureCache] getStringForKey:kActivatedMessage error:&error];
        SecureChannelMessageWrapper* channelWrapper = [DIGIPassClientSDKWrapper parseSecureChannelMessage:decrpted];
        SecureChannelMessage message = channelWrapper.message;
        
        NSString* platformfingerPrint = [[DeviceBindingSDK getInstance]
                                         fingerprintForSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]
                                         inAccessGroup:[DIGIPassClientSDKWrapper getAppPrivateAccessGroup]
                                         error:&error];
//        NSString* platformfingerPrint =  [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:[[[DigiPassSingleTon sharedInstance] userIno] SALT_DIGIPASS]];
        
        NSDictionary* vectors = [[DigiPassSharedData sharedInstance] fetchUserVectors];
        NSData* staticVectorData = [vectors objectForKey:kStaticVectorData];
        NSData* dynamicVectorData = [vectors objectForKey:kDynamicVectorData];
        
        vds_int32 staticVectorLength = (vds_int32) staticVectorData.length;
        vds_byte* staticVector = (vds_byte*) malloc(sizeof(vds_byte) * staticVectorLength);
        [staticVectorData getBytes:staticVector length:staticVectorLength];
        
        memset(staticVector, 0, staticVectorLength);
        memcpy(staticVector, [staticVectorData bytes], staticVectorLength);
        
        vds_int32 dynamicVectorLength = 0;
        vds_int32 returnCode1 = DPSDK_GetDynamicVectorLength(staticVector, staticVectorLength, &dynamicVectorLength);
        
        if(returnCode1 != RETURN_CODE_SUCCESS) {
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            error = [[NSError alloc] initWithDomain:errorDomain code:(NSUInteger) returnCode1 userInfo:@{@"message": @"Dynamic Vector length failed"}];
//            error = [[NSError alloc] initWithCode:(NSUInteger) returnCode1 message:@"Dynamic Vector length failed"]; // log the error code!
            [FIRAnalytics logEventWithName:@"decryptSecureChannelMessageBody"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode1)]
                                             }];
            return nil;
        }
        
        vds_byte* dynamicVector = (vds_byte*) malloc(sizeof(vds_byte) * dynamicVectorLength);
        [dynamicVectorData getBytes:dynamicVector length:dynamicVectorLength];
        
        memset(dynamicVector, 0, dynamicVectorLength);
        memcpy(dynamicVector, [dynamicVectorData bytes], dynamicVectorLength);
        
        vds_ascii* fingerprint = (char *) [platformfingerPrint UTF8String];
        
        vds_ascii messageBody[LENGTH_SECURE_CHANNEL_MESSAGE_BODY_MAX + 1] = {0};
        vds_int32 messageBodyLength = sizeof(messageBody);
        memset(messageBody, 0, messageBodyLength);
        
        vds_int32 returnCode = DPSDK_DecryptSecureChannelMessageBody(staticVector, staticVectorLength, dynamicVector, dynamicVectorLength, &message, fingerprint, messageBody, sizeof(messageBody));
        
        size_t len = strlen(messageBody);
        char * newBuf = (char *)malloc(len);
        memcpy(newBuf, messageBody, len);
        
        NSData* d = [NSData dataWithBytes:messageBody length:sizeof(messageBody)];
        
        if (returnCode != RETURN_CODE_SUCCESS) {
            [FIRAnalytics logEventWithName:@"decryptSecureChannelMessageBody"
                                parameters:@{
                                             @"error": [NSString stringWithUTF8String: DPSDK_GetMessageForReturnCode(returnCode)]
                                             }];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
        }else {
            NSString* result = [[NSString alloc]initWithData:d encoding:NSASCIIStringEncoding];
            NSData* hexBytes = [result stringToHexData];
            NSString* finalResult = [[NSString alloc]initWithData:hexBytes encoding:NSASCIIStringEncoding];
         
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:staticVector length:staticVectorLength];
            [DIGIPassClientSDKWrapper zeroAndFreeWithByte:dynamicVector length:dynamicVectorLength];
            
            return finalResult;
        }
    } @catch (NSException *exception) {
        [FIRAnalytics logEventWithName:@"decryptSecureChannelMessageBody"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
    } @finally {
        
    }
   
}

+ (NSString *) stringToHex:(NSString *)str
{
    NSString* finalStr = [str stringByReplacingOccurrencesOfString:@"\0" withString:@""];
    NSUInteger len = [finalStr length];
    unichar *chars = malloc(len * sizeof(unichar));
    [finalStr getCharacters:chars];
    
    NSMutableString *hexString = [[NSMutableString alloc] init];
    for(NSUInteger i = 0; i < len; i++ )
    {
        [hexString appendString:[NSString stringWithFormat:@"%x", chars[i]]];
    }
    free(chars);
    
    return hexString;
}
@end

