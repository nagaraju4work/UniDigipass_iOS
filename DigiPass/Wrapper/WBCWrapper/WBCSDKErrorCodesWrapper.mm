//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "WBCSDKErrorCodesWrapper.h"

#import <MSSWBC/WBCErrorCodes.h>

using namespace com::vasco::digipass::sdk::utils::wbc;

NSInteger const INTERNAL_ERROR = WBCErrorCodes::INTERNAL_ERROR;

NSInteger const CRYPTO_MECHANISM_INVALID = WBCErrorCodes::CRYPTO_MECHANISM_INVALID;

NSInteger const CRYPTO_MODE_INVALID = WBCErrorCodes::CRYPTO_MODE_INVALID;

NSInteger const WBCSDK_TABLES_INVALID = WBCErrorCodes::WBCSDK_TABLES_INVALID;

NSInteger const INITIAL_VECTOR_NULL = WBCErrorCodes::INITIAL_VECTOR_NULL;

NSInteger const INITIAL_VECTOR_INCORRECT_LENGTH = WBCErrorCodes::INITIAL_VECTOR_INCORRECT_LENGTH;

NSInteger const INPUT_DATA_NULL = WBCErrorCodes::INPUT_DATA_NULL;

NSInteger const INPUT_DATA_INCORRECT_LENGTH = WBCErrorCodes::INITIAL_VECTOR_INCORRECT_LENGTH;

NSInteger const OUTPUT_DATA_NULL = WBCErrorCodes::OUTPUT_DATA_NULL;

NSInteger const OUTPUT_DATA_INCORRECT_LENGTH = WBCErrorCodes::OUTPUT_DATA_INCORRECT_LENGTH;
