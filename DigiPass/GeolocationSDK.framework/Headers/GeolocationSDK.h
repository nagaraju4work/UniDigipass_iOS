/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import "GeolocationSDKLocation.h"
NS_ASSUME_NONNULL_BEGIN

#define GeolocationSDK_VERSION  @"4.21.1"

/**
 * This class provides the main functions of the Geolocation SDK.
 */
@interface GeolocationSDK : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * This method checks whether the location service is enabled.
 *
 * @return true if the location service is enabled
 */
+(BOOL) isLocationServiceEnabled;


/**
 * This method checks whether a location is contained in an area list.
 *
 * @param location the GeolocationSDKLocation to be checked.
 * This parameter cannot be null and must be valid.
 * @param areaList the vector containing the GeolocationSDKArea used for the check.
 * This parameter cannot be null or empty. The areas must be valid.
 *
 * @return true if the location is contained in one of the provided areas
 *
 * @throws GeolocationSDKException This exception contains one of the following error codes (see GeolocationSDKErrorCodes.h):
 * - GeolocationSDKErrorCodes_LOCATION_LATITUDE_INVALID if the latitude of the location is invalid.
 * - GeolocationSDKErrorCodes_LOCATION_LONGITUDE_INVALID if the longitude of the location is invalid.
 * - GeolocationSDKErrorCodes_AREA_LIST_AREA_NULL if an area in the list of areas is null.
 * - GeolocationSDKErrorCodes_AREA_LIST_NULL if the list of area is null.
 * - GeolocationSDKErrorCodes_AREA_LIST_EMPTY if the list of area is empty.
 * - GeolocationSDKErrorCodes_AREA_LIST_SOUTH_LATITUDE_INVALID if the value of a southern latitude contained in an area is invalid.
 * - GeolocationSDKErrorCodes_AREA_LIST_NORTH_LATITUDE_INVALID if the value of a northern latitude contained in an area is invalid.
 * - GeolocationSDKErrorCodes_AREA_LIST_LATITUDES_INVALID  if one of the provided area has a southern latitude higher than its northern latitude.
 * - GeolocationSDKErrorCodes_AREA_LIST_WEST_LONGITUDE_INVALID if the value of a western longitude contained in an area is invalid.
 * - GeolocationSDKErrorCodes_AREA_LIST_EAST_LONGITUDE_INVALID if the value of a eastern longitude contained in an area is invalid.
 * - GeolocationSDKErrorCodes_AREA_LIST_LONGITUDES_INVALID  if one of the provided area has a western longitude higher than its eastern longitude.
 */
+(BOOL) isLocationAuthorizedWithLocation: (GeolocationSDKLocation*)location andAreaList: (NSArray*)areaList;

/**
 * This method returns the current location of the device by using a newly allocated GeolocationSDKLocation object.
 * The function tries to get a location with an accuracy smaller or equal to the minimumAccuracy during timeout seconds.
 * The process is as follows:
 *  - during timeout seconds, every time a location is received :
 *      - if it has a sufficient accuracy (smaller or equal to minimumAccuracy), it is directly returned;
 *      - if it has a non-sufficient accuracy (greater than minimumAccuracy), the location with the smaller accuracy is stored.
 *  - at the end of the timer :
 *      - if at least one location has been received (with an non-sufficient accuracy), it is returned;
 *      - if no location has been received a GeolocationSDKException is raised with error code LOCATION_TIMEOUT.
 *
 * @param timeout Used to prevent deadlock during location computation. In seconds, must be greater than 0.
 * @param minimumAccuracy The minimum accuracy (in meters) required for the location. This parameter cannot be null.
 * @param allowBackground Allow the location service to start even if the application is in the background (Note: this is only relevant for iOS 8 and above).
 *
 * @return a new GeolocationSDKLocation object corresponding to the current location. It is up to the caller to
 * free this memory when needed.
 *
 * @throws GeolocationSDKException This exception contains one of the following error codes (see GeolocationSDKErrorCodes.h):
 * - GeolocationSDKErrorCodes_INTERNAL_ERROR if an internal error occurred.
 * - GeolocationSDKErrorCodes_TIMEOUT_INVALID if the value of the timeout is invalid.
 * - GeolocationSDKErrorCodes_ACCURACY_INVALID if the value of the accuracy is invalid.
 * - GeolocationSDKErrorCodes_LOCATION_UNAVAILABLE if the location cannot be retrieved because no location method is available.
 * - GeolocationSDKErrorCodes_LOCATION_TIMEOUT if the location has not been retrieved before the timeout expiration.
 */
+(GeolocationSDKLocation*) getLocationWithTimeout:(int)timeout andMinimumAccuracy:(double)minimumAccuracy andAllowBackground:(bool)allowBackground;

/*!
 * \mainpage Geolocation SDK - Programmer documentation
 * \brief Provides the entry points of the Geolocation SDK framework API:
 * <ul>
 *   <li>Use GeolocationSDK::getLocationWithTimeout:andMinimumAccuracy:andAllowBackground: to retrieve the current location of the device</li>
 *   <li>Use GeolocationSDK::isLocationAuthorizedWithLocation:andAreaList: to check if a location is within an authorized area</li>
 * </ul>
 * Copyright &copy; since 1999. VASCO DATA SECURITY. All Rights Reserved.
 * @version 4.21.1
 */

@end

NS_ASSUME_NONNULL_END
