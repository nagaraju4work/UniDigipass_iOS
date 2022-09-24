//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "WBCSDKErrorCodesWrapper.h"

#import <WBCSDK/WBCSDKErrorCodes.h>
using namespace com::vasco::digipass::sdk::utils::wbc;

NSInteger const INTERNAL_ERROR = WBCSDKErrorCodes::INTERNAL_ERROR;

NSInteger const CRYPTO_MECHANISM_INVALID = WBCSDKErrorCodes::CRYPTO_MECHANISM_INVALID;

NSInteger const CRYPTO_MODE_INVALID = WBCSDKErrorCodes::CRYPTO_MODE_INVALID;

NSInteger const WBCSDK_TABLES_INVALID = WBCSDKErrorCodes::WBCSDK_TABLES_INVALID;

NSInteger const INITIAL_VECTOR_NULL = WBCSDKErrorCodes::INITIAL_VECTOR_NULL;

NSInteger const INITIAL_VECTOR_INCORRECT_LENGTH = WBCSDKErrorCodes::INITIAL_VECTOR_INCORRECT_LENGTH;

NSInteger const INPUT_DATA_NULL = WBCSDKErrorCodes::INPUT_DATA_NULL;

NSInteger const INPUT_DATA_INCORRECT_LENGTH = WBCSDKErrorCodes::INITIAL_VECTOR_INCORRECT_LENGTH;

NSInteger const OUTPUT_DATA_NULL = WBCSDKErrorCodes::OUTPUT_DATA_NULL;

NSInteger const OUTPUT_DATA_INCORRECT_LENGTH = WBCSDKErrorCodes::OUTPUT_DATA_INCORRECT_LENGTH;
