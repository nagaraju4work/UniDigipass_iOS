//
//  DigiPassSharedData.m
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 9/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

#import "DigiPassSharedData.h"
#import "Constants.h"
#include <stdlib.h>
//#import <FirebaseAnalytics/FirebaseAnalytics.h>
#import <MSSDeviceBinding/MSSDeviceBinding.h>
#import "DigiPass-Swift.h"

@class Logger;

@implementation DigiPassSharedData
NSString *teamId = @"V4YMXB7NF8";

+ (instancetype) sharedInstance {
    static dispatch_once_t pred = 0;
    static id _sharedObject = nil;
    dispatch_once(&pred, ^{
        _sharedObject = [[self alloc] init];
    });
    return _sharedObject;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        
        NSError* error;
        @try {
            int r = arc4random_uniform(74);
            NSString* secureCatchFileName = [NSString stringWithFormat:@"%d", r];
            
            NSString* secureStorageFileName = [[DeviceBindingSDK getInstance]
                                             fingerprintForSalt:@"9BF7B93BA05E3B0284F7069918F743C0B503D6D27A6F9E6B89CDEF583611CB83"
                                             inAccessGroup:[DigiPassSharedData getAppPrivateAccessGroup]
                                             error:&error];
            
//            NSString* secureStorageFileName = [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:@"9BF7B93BA05E3B0284F7069918F743C0B503D6D27A6F9E6B89CDEF583611CB83"];
            
            self.secureStorage = [[SecureStorageSDKWrapper alloc]initWithFileName:@"DigiPass" useFingerPrint: secureStorageFileName andIterationNumber:8000 error: &error];
            self.secureCache = [[SecureStorageSDKWrapper alloc]initWithFileName:@"DigiPassTemp" useFingerPrint: secureCatchFileName andIterationNumber:8000 error: &error];
            
        }@catch (NSException * exception) {
//            [FIRAnalytics logEventWithName:@"DigiPass Initilizer"
//                                parameters:@{
//                                             @"error":  exception.reason
//                                             }];
            
            [Logger log:[NSString stringWithFormat:@"DigiPass Initilizer: %@",exception.reason]];
            
            NSLog(@"Error in load");
            
        }@finally {
            
        }
    }
    return self;
}

+ (id<AccessGroup>)getAppPrivateAccessGroup
{
    return [[AppPrivate alloc] initWithTeamId:teamId bundleId:@"com.unicorp.adpolice.gov"];
}

- (NSMutableDictionary *) fetchUserVectors {
    NSMutableDictionary* dict = [NSMutableDictionary dictionary];
    NSDictionary* user = [self currentUser];
    NSString* SVKey = [NSString stringWithFormat:@"%@_%@", [user objectForKey:kUserName], kStaticVectorData];
    NSString* DVKey = [NSString stringWithFormat:@"%@_%@", user[kUserName], kDynamicVectorData];
    NSString* DVPinKey = [NSString stringWithFormat:@"%@_%@", user[kUserName], kDynamicVectorDataPin];
    NSString* pinSelected = user[kIsPinSelected];
    BOOL isPinSelected =  [pinSelected isEqualToString:kPin] ? true : false;
    
    NSError* error = nil;
    NSData* staticVector = [self.secureStorage getBytesForKey:SVKey error:&error];
    NSData* dynamicVector = [self.secureStorage getBytesForKey:isPinSelected ? DVPinKey : DVKey error:&error];
    if (error != nil) {
//        [FIRAnalytics logEventWithName:@"Fetch User Vectors"
//                            parameters:@{
//                                         @"error":  error.localizedDescription
//                                         }];
        
        [Logger log:[NSString stringWithFormat:@"Fetch User Vectors: %@",error.localizedDescription]];
        
    }
    [dict setObject:staticVector forKey:kStaticVectorData];
    [dict setObject:dynamicVector forKey:kDynamicVectorData];
    [dict setObject:pinSelected forKey:kIsPinSelected];
    return dict;
}

- (NSDictionary *) fetchVectorsFromVolatile {
    NSMutableDictionary* dict = [NSMutableDictionary dictionary];
    NSString* userName = [self.secureCache getStringForKey:kUserName error:nil];
    NSData* SV = [self.secureCache getBytesForKey:[NSString stringWithFormat:@"%@_%@", userName, kStaticVectorData] error:nil];
    [dict setObject:SV forKey:kStaticVectorData];
    
    NSError* error;
    NSString* isPinVector = [[NSUserDefaults standardUserDefaults] objectForKey:kActivationType];
    
    if ([isPinVector isEqualToString:@"pin"]) {
        NSData* DV = [self.secureCache getBytesForKey:[NSString stringWithFormat:@"%@_%@", userName, kDynamicVectorDataPin] error:&error];
        [dict setObject:DV forKey:kDynamicVectorData];
    }else {
        NSData* DV = [self.secureCache getBytesForKey:[NSString stringWithFormat:@"%@_%@", userName, kDynamicVectorData] error:&error];
        [dict setObject:DV forKey:kDynamicVectorData];
    }
    [dict setObject:isPinVector forKey:kIsPinSelected];
    
    if (error != nil) {
//        [FIRAnalytics logEventWithName:@"Fetch Vectors From Volatile"
//                            parameters:@{
//                                         @"error":  error.localizedDescription
//                                         }];
        
        [Logger log:[NSString stringWithFormat:@"Fetch Vectors From Volatile: %@",error.localizedDescription]];
        
        return nil;
    }
    return dict;
}

// CALL THIS thrice :
// 1.after MultiDeviceActivateLicense -> PRE_ACTIVATED DIGIPASS
// 2. after MultiDeviceActivateInstance -> FULLY ACTIVATED but not accepted by the server yet
// 3. after generateSignatureFromSecureChannelMessage ->> FULLY ACTIVATED + Accepted by the server
- (void) storeDynamicVectorInVolatile:(NSData *) dv  vectorType:(NSString *) type {
    NSError* error;
    NSString* userName = [self.secureCache getStringForKey:kUserName error:nil];
    
    NSString* key = [type isEqualToString:@"pin"] ?kDynamicVectorDataPin : kDynamicVectorData;
    NSString* dynamicVectorKey = [NSString stringWithFormat:@"%@_%@", userName,  key];
    [self.secureCache putBytesForBytes:dv forKey:dynamicVectorKey error:&error];
    
    if (error != nil) {
//        [FIRAnalytics logEventWithName:@"Story Dynamic Vectors Volatile"
//                            parameters:@{
//                                         @"error":  error.localizedDescription
//                                         }];
        
        [Logger log:[NSString stringWithFormat:@"Story Dynamic Vectors Volatile: %@",error.localizedDescription]];
        
    }
}

- (void) storeVectorsDV: (NSData *) dv  {
    NSError* error;
    NSDictionary* userDict = [self currentUser];
    NSString* userName = (userDict[kUserName]  != nil) ? userDict[kUserName] : [self.secureStorage getStringForKey:kUserName error:&error];
    NSString* type = userDict[kIsPinSelected];
    
    NSString* key = [type isEqualToString:@"pin"] ?kDynamicVectorDataPin : kDynamicVectorData;
    NSString* dynamicVectorKey = [NSString stringWithFormat:@"%@_%@", userName,  key];
    
    @try {
        [self.secureStorage putBytesForBytes:dv forKey:dynamicVectorKey error:&error];
        [[DigiPassSharedData sharedInstance] saveSecureStorage];
    }@catch (NSException* e) {
        if (error != nil) {
//            [FIRAnalytics logEventWithName:@"Store Dynamic Vector"
//                                parameters:@{
//                                             @"error":  error.localizedDescription
//                                             }];
            
            [Logger log:[NSString stringWithFormat:@"Store Dynamic Vector: %@",error.localizedDescription]];
            
        }
    }@finally {
        
    }
    
}

- (void) moveFromCacheToPermanent:(NSString *) type {
    NSError* error;
    
    @try {
        NSString* userName = [self.secureCache getStringForKey:kUserName error:nil];
        NSData* SV = [self.secureCache getBytesForKey:[NSString stringWithFormat:@"%@_%@", userName, kStaticVectorData] error:nil];
        
        [self.secureStorage putBytesForBytes:SV forKey:[NSString stringWithFormat:@"%@_%@", userName, kStaticVectorData] error:&error];
        
        NSString* DVKey = ([type isEqualToString:@"pin"]) ? [NSString stringWithFormat:@"%@_%@", userName, kDynamicVectorDataPin] : [NSString stringWithFormat:@"%@_%@", userName, kDynamicVectorData];
        NSData* DV = [self.secureCache getBytesForKey:DVKey error:&error];
        [self.secureStorage putBytesForBytes:DV forKey:DVKey error:&error];
        [[DigiPassSharedData sharedInstance] saveSecureStorage];
        
    }@catch (NSException * exception) {
//        [FIRAnalytics logEventWithName:@"decryptSecureChannelMessageBody"
//                            parameters:@{
//                                         @"error":  exception.reason
//                                         }];
        
        [Logger log:[NSString stringWithFormat:@"decryptSecureChannelMessageBody: %@",exception.reason]];
        
    }@finally {
        
    }
}

- (void) addUsersToDefaults:(NSDictionary *) userDetails {
    NSArray* storedUsers = [[NSUserDefaults standardUserDefaults] objectForKey:kUsers];
    NSMutableArray* resultUsers = [NSMutableArray arrayWithArray:storedUsers];
    if (storedUsers != nil & storedUsers.count > 0) {
        [resultUsers addObject:userDetails];
    }else {
        [resultUsers addObject:userDetails];
    }
    storedUsers = resultUsers;
    [[NSUserDefaults standardUserDefaults] setObject:storedUsers forKey:kUsers];
    [[NSUserDefaults standardUserDefaults] setObject:userDetails forKey:kCurrentUser];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void) updatePinSelectionForCurrentUser:(NSString *) isPinSelected {
    NSDictionary* userDict = [[NSUserDefaults standardUserDefaults] objectForKey:kCurrentUser];
    NSMutableDictionary* updated = [NSMutableDictionary dictionaryWithDictionary:userDict];
    [updated setObject:isPinSelected forKey:kIsPinSelected];
    [[NSUserDefaults standardUserDefaults] setObject:updated forKey:kCurrentUser];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (NSDictionary *) currentUser {
    NSDictionary* userDetails = [[NSUserDefaults standardUserDefaults] objectForKey:kCurrentUser];
    return userDetails != nil ? userDetails : @{};
}

- (void) deleteUser:(NSDictionary *)user {
    NSArray* users = [[NSUserDefaults standardUserDefaults] objectForKey:kUsers];
    NSMutableArray* tempUsers = [NSMutableArray arrayWithArray:users];
    NSString* deletedName = user[kUserName];
    int index = 0;
    for (NSDictionary* dict in tempUsers) {
        NSString* userName = dict[kUserName];
        if ([userName  isEqualToString:deletedName]) {
            break;
        }
        index ++;
    }
    [tempUsers removeObjectAtIndex:index];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:kCurrentUser];
    users = [tempUsers mutableCopy];
    [[NSUserDefaults standardUserDefaults] setObject:users forKey:kUsers];
}

- (void) saveSecureStorage {
    NSError* error;
    @try {
        NSString* secureStorageFileName = [[DeviceBindingSDK getInstance]
                                         fingerprintForSalt:@"9BF7B93BA05E3B0284F7069918F743C0B503D6D27A6F9E6B89CDEF583611CB83"
                                         inAccessGroup:[DigiPassSharedData getAppPrivateAccessGroup]
                                         error:&error];
        
//        NSString* secureStorageFileName = [DeviceBindingSDK getDeviceFingerPrintWithDynamicSalt:@"9BF7B93BA05E3B0284F7069918F743C0B503D6D27A6F9E6B89CDEF583611CB83"];
        [self.secureStorage writeWithFingerprint:secureStorageFileName andIterationNumber:8000 error:&error];
    }@catch (NSException *exception) {
//        [FIRAnalytics logEventWithName:@"decryptSecureChannelMessageBody"
//                            parameters:@{
//                                         @"error":  exception.reason
//                                         }];
        
        [Logger log:[NSString stringWithFormat:@"decryptSecureChannelMessageBody: %@",exception.reason]];
        
    }@finally { }
}
@end
