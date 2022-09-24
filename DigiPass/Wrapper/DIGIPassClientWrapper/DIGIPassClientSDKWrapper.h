//
//  DIGIPassClientSDKWrapper.h
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SecureChannelMessageWrapper.h"
#import <DigipassSDK/DP4Capi.h>
#import "MDActivateModelWrapper.h"

NS_ASSUME_NONNULL_BEGIN


@interface DIGIPassClientSDKWrapper : NSObject

+ (SecureChannelMessageWrapper *) parseSecureChannelMessage:(NSString *) message;

+ (void) multiDeviceLicenceActivation;

+ (MDActivateInstanceModelWrapper *) multiDeviceActivateInstance:(NSString *) password;

+ (MDGenerateSignatureModelWrapper *) generateSignatureFromPassword: (NSString *) password
                                                  isActivateProcess:(BOOL)isActivate;

+ (NSMutableDictionary *) validatePassword: (NSString *) pin;

+ (BOOL) checkWeakPassword:(NSString *) pin;

+ (NSString *) generateOTPCodeForPin:(NSString *) pin;

+ (SecureChannelMessageWrapper *) generateSecureChannelINotificationToken:(NSString *)notificationToken;


+ (NSString *) getDigiPassPropertyInt:(vds_int32) property cryptoIndex:(vds_int32) cryptoAppIdx;

+ (NSString *) getDigiPassPropertyStr:(vds_int32) property valueLength: (vds_int32) valueLength
                          cryptoIndex:(vds_int32) cryptoAppIdx;

+ (NSString *) decryptSecureChannelMessageBody;

+ (NSString *) stringToHex:(NSString *)str;

+ (vds_int32) computeClientServerTimeShiftFromServerTime:(vds_int32) time;

+ (vds_int32) fetchServerTimeSS ;

@end

NS_ASSUME_NONNULL_END
