/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////


/** An Internal error has occurred */
#define GeolocationSDKErrorCodes_INTERNAL_ERROR -4700

/** The value of the timeout is invalid. Must be > 0. */
#define GeolocationSDKErrorCodes_TIMEOUT_INVALID -4701

/** The value of the minimum accuracy is invalid. Must be >= 0. */
#define GeolocationSDKErrorCodes_ACCURACY_INVALID -4702

/** The location cannot be retrieved because no location method is available. */
#define GeolocationSDKErrorCodes_LOCATION_UNAVAILABLE -4703

/** The location has not been retrieved before the timeout expiration. */
#define GeolocationSDKErrorCodes_LOCATION_TIMEOUT -4704

/** The location provided as parameter is NULL. */
#define GeolocationSDKErrorCodes_LOCATION_NULL -4705

/** The value of the latitude is invalid. Must be >=-90 and <=90. */
#define GeolocationSDKErrorCodes_LOCATION_LATITUDE_INVALID -4706

/** The value of the longitude is invalid. Must be >=-180 and <=180. */
#define GeolocationSDKErrorCodes_LOCATION_LONGITUDE_INVALID -4707

/** The area list is NULL. */
#define GeolocationSDKErrorCodes_AREA_LIST_NULL -4708

/** The area list is empty. */
#define GeolocationSDKErrorCodes_AREA_LIST_EMPTY -4709

/** An area in the area list is NULL. */
#define GeolocationSDKErrorCodes_AREA_LIST_AREA_NULL -4710

/** The value of a latitude start contained in an area is invalid. Must be >=-90 and <=90. */
#define GeolocationSDKErrorCodes_AREA_LIST_SOUTH_LATITUDE_INVALID -4711

/** The value of a latitude end contained in an area is invalid. Must be >=-90 and <=90. */
#define GeolocationSDKErrorCodes_AREA_LIST_NORTH_LATITUDE_INVALID -4712

/** One of the provided area has a latitude start higher than the latitude end. */
#define GeolocationSDKErrorCodes_AREA_LIST_LATITUDES_INVALID -4713

/** The value of a longitude start contained in an area is invalid. Must be >=-180 and <=180. */
#define GeolocationSDKErrorCodes_AREA_LIST_WEST_LONGITUDE_INVALID -4714

/** The value of a longitude end contained in an area is invalid. Must be >=-180 and <=180. */
#define GeolocationSDKErrorCodes_AREA_LIST_EAST_LONGITUDE_INVALID -4715

/** One of the provided area has a longitude start higher than the longitude end. */
#define GeolocationSDKErrorCodes_AREA_LIST_LONGITUDES_INVALID -4716

/** One of the NSLocationAlwaysUsageDescription, NSLocationWhenInUseUsageDescription or NSLocationAlwaysAndWhenInUseUsageDescription plist entry is missing. */
#define GeolocationSDKErrorCodes_INTEGRATION_ISSUE -4719



