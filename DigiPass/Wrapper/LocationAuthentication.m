//
//  LocationAuthentication.m
//  OrchestrationSDKSample
//
//  Created by Unicorp Technologies LLC on 4/24/19.
//  Copyright © 2019 vasco. All rights reserved.
//

#import "LocationAuthentication.h"
#import <FirebaseAnalytics/FirebaseAnalytics.h>

// 2, 10 and 20 seconds timeout for the location request
#define TIMEOUT_02 2
#define TIMEOUT_10 10
#define TIMEOUT_30 30

// 2, 80 and 500 meters minimum accuracy for the location request
#define MINIMUM_ACCURACY_2 2
#define MINIMUM_ACCURACY_80 80
#define MINIMUM_ACCURACY_500 500

@implementation LocationAuthentication

static LocationAuthentication *_sharedMySingleton = nil;

+(LocationAuthentication *)sharedMySingleton {
    @synchronized([LocationAuthentication class]) {
        if (!_sharedMySingleton)
            _sharedMySingleton = [[self alloc] init];
        return _sharedMySingleton;
    }
    return nil;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        [self setup];
    }
    return self;
}

- (void) setup {
    
}

- (void) checkCurrentLocationInAreaList:(void(^)(bool))callback {
   
   // dispatch_async(dispatch_get_main_queue(), ^{
        [self checkLocationServices:^(bool allow) {
            if (allow) {
                GeolocationSDKLocation* location = [self getCurrentLocation];
                NSMutableArray* areaList = [[NSMutableArray alloc] init];
                
                // Define northern hemisphere zone
                GeolocationSDKArea* areaNorthernHemisphere = [[GeolocationSDKArea alloc] initWithSouthLatitude:0 AndWestLongitude:-180 AndNorthLatitude:90 AndEastLongitude:180];
//                GeolocationSDKArea* areaNorthernHemisphere = [[GeolocationSDKArea alloc] initWithSouthLatitude:24.286476 AndWestLongitude:54.283631 AndNorthLatitude:24.560430 AndEastLongitude:54.609864];

                [areaList addObject:areaNorthernHemisphere];
                
                // Check if the current location is in the selected zone
                if([GeolocationSDK isLocationAuthorizedWithLocation:location andAreaList:areaList]) {
                    callback(true);
                } else {
                    callback(false);
                }
            }else {
                callback(false);
            }
        }];
    
}

- (void) checkLocationServices:(void(^)(bool))callback {
    
    //dispatch_async(dispatch_get_main_queue(), ^{
        @try {
            callback([GeolocationSDK isLocationServiceEnabled]);
        } @catch (GeolocationSDKException* exception) {
            [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperClear"
                                parameters:@{
                                             @"error":  exception.reason
                                             }];
            [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                // Something went wrong
                if(exception.errorCode == GeolocationSDKErrorCodes_LOCATION_TIMEOUT) {
                    //NSLog(@"The location process has timed out.");
                }
                else if(exception.errorCode == GeolocationSDKErrorCodes_LOCATION_UNAVAILABLE) {
                    //NSLog(@"Location service unavailable. Please enable it.");
                } else  {
                    //NSLog(@"An unexpected error has occurred.");
                }
            }];
        } @finally {
            
        }
    //});
    
}

- (GeolocationSDKLocation *) getCurrentLocation {
   
    @try
    {
        //NSLog(@"View: Getting location");
        
        // Check service availablility
        if([GeolocationSDK isLocationServiceEnabled])
        {
            // Get location
            GeolocationSDKLocation* location = [GeolocationSDK getLocationWithTimeout:TIMEOUT_30 andMinimumAccuracy:MINIMUM_ACCURACY_80 andAllowBackground:NO];
            
            //NSLog(@"%f, %f, %2f", location.latitude, location.longitude, location.accuracy);

            return location;
        } else {
            //NSLog(@"Location service is not enabled.");
        }
    }
    @catch (GeolocationSDKException* exception)
    {
        [FIRAnalytics logEventWithName:@"SecureStorageSDKWrapperClear"
                            parameters:@{
                                         @"error":  exception.reason
                                         }];
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            // Something went wrong
            if(exception.errorCode == GeolocationSDKErrorCodes_LOCATION_TIMEOUT) {
                //NSLog(@"The location process has timed out.");
            }
            else if(exception.errorCode == GeolocationSDKErrorCodes_LOCATION_UNAVAILABLE) {
                //NSLog(@"Location service unavailable. Please enable it.");
            } else  {
                //NSLog(@"An unexpected error has occurred.");
            }
        }];
    }
    @finally
    {
       
    }
}

@end
