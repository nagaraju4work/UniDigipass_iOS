/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN

@interface GeolocationSDKLocation : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Latitude coordinate. Must be in range [-90;90] for the GeolocationSDKLocation object to be considered valid.
 */
@property(readonly) double latitude;

/**
 * Longitude coordinate. Must be in range [-180;180] for the GeolocationSDKLocation object to be considered valid.
 */
@property(readonly) double longitude;

/**
 * Accuracy (in meters) of the position.
 */
@property(readonly) double accuracy;

/**
 * Timestamp of the position acquisition since epoch, in seconds.
 */
@property(readonly) long timestamp;

/**
 * Instanciate and initialize a GeolocationSDKLocation
 */
- (instancetype)initWithLatitude:(double)latitude AndLongitude:(double)longitude AndAccuracy:(double)accuracy AndTimestamp:(double)timestamp;

@end

NS_ASSUME_NONNULL_END
