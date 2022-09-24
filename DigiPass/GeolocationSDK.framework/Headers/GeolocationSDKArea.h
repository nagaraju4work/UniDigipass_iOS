/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN

/**
 * This class represents a geographic area used by the Geolocation SDK.
 * A GeolocationSDKArea is defined by its boundaries : the southern and northern latitudes and the eastern and western longitudes.
 */
@interface GeolocationSDKArea : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Southern boundary latitude, in degrees.
 * Must be in range [-90;90] for the GeolocationSDKArea object to be considered valid.
 */
@property(readonly) double southLatitude;

/**
 * Western boundary longitude, in degrees.
 * Must be in range [-180;180] for the GeolocationSDKArea object to be considered valid.
 */
@property(readonly) double westLongitude;

/**
 * Northern boundary latitude, in degrees.
 * Must be in range [-90;90] and strictly greater than the southLatitude for the GeolocationSDKArea object to be considered valid.
 */
@property(readonly) double northLatitude;

/**
 * Eastern boundary longitude, in degrees.
 * Must be in range [-180;180] and strictly greater than the westLongitude for the GeolocationSDKArea object to be considered valid.
 */
@property(readonly) double eastLongitude;

/**
 * Instanciate and initialize a GeolocationSDKArea
 */
- (instancetype)initWithSouthLatitude:(double)southLatitude AndWestLongitude:(double)westLongitude AndNorthLatitude:(double)northLatitude AndEastLongitude:(double)eastLongitude;

@end

NS_ASSUME_NONNULL_END
