
#import <Foundation/Foundation.h>

/** Internal error */
FOUNDATION_EXPORT NSInteger const INTERNAL_ERROR;

/** The crypto mechanism is invalid. */
FOUNDATION_EXPORT NSInteger const CRYPTO_MECHANISM_INVALID;

/** The crypto mode is invalid. */
FOUNDATION_EXPORT NSInteger const CRYPTO_MODE_INVALID;

/** The WBCSDKTable object is invalid. */
FOUNDATION_EXPORT NSInteger const WBCSDK_TABLES_INVALID;

/** The initial vector byte array is null. */
FOUNDATION_EXPORT NSInteger const INITIAL_VECTOR_NULL;

/** The initial vector length is incorrect according to the selected mechanism. */
FOUNDATION_EXPORT NSInteger const INITIAL_VECTOR_INCORRECT_LENGTH;

/** The input byte array is null. */
FOUNDATION_EXPORT NSInteger const INPUT_DATA_NULL;

/** The input bytes array length is incorrect according to the selected mechanism. */
FOUNDATION_EXPORT NSInteger const INPUT_DATA_INCORRECT_LENGTH;

/** The output byte array is null. */
FOUNDATION_EXPORT NSInteger const OUTPUT_DATA_NULL;

/** The output data length is invalid. */
FOUNDATION_EXPORT NSInteger const OUTPUT_DATA_INCORRECT_LENGTH;
