//
//  DigiPassSharedData.h
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 9/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SecureStorageWrapper/SecureStorageSDKWrapper.h"
#import "DIGIPassClientWrapper/MDActivateModelWrapper.h"
//#import <MSSDeviceBinding/MSSDeviceBinding.h>
//#import <MSSDigipass/DP4Capi.h>

NS_ASSUME_NONNULL_BEGIN

@interface DigiPassSharedData : NSObject

+ (instancetype) sharedInstance;

- (NSMutableDictionary *) fetchUserVectors;
- (void) storeDynamicVectorInVolatile:(NSData *) dv  vectorType:(NSString *) type;
- (NSDictionary *) fetchVectorsFromVolatile;
- (void) addUsersToDefaults:(NSDictionary *) userDetails;
- (NSDictionary *) currentUser;
- (void) deleteUser:(NSDictionary *) user;
- (void) updatePinSelectionForCurrentUser:(NSString *) isPinSelected;
- (void) moveFromCacheToPermanent:(NSString *) type;
- (void) storeVectorsDV: (NSData *) dv;
- (void) saveSecureStorage;

@property (strong, nonatomic) SecureStorageSDKWrapper* secureStorage; // PERM SENSITIVE DATA

@property (strong, nonatomic) SecureStorageSDKWrapper* secureCache; // TEMP SENSITIVE DATA

@end

NS_ASSUME_NONNULL_END
