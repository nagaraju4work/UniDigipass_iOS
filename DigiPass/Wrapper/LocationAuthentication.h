//
//  LocationAuthentication.h
//  OrchestrationSDKSample
//
//  Created by Unicorp Technologies LLC on 4/24/19.
//  Copyright © 2019 vasco. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GeolocationSDK/GeolocationSDK.h>
#import <GeolocationSDK/GeolocationSDKArea.h>
#import <GeolocationSDK/GeolocationSDKException.h>
#import <GeolocationSDK/GeolocationSDKErrorCodes.h>

NS_ASSUME_NONNULL_BEGIN

@interface LocationAuthentication : NSObject

+(LocationAuthentication *)sharedMySingleton;

- (GeolocationSDKLocation *) getCurrentLocation;

- (void) checkLocationServices:(void(^)(bool))callback;

- (void) checkCurrentLocationInAreaList:(void(^)(bool))callback;

@end

NS_ASSUME_NONNULL_END
