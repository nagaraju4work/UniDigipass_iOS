//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import "WBCSDKWrapper.h"
#import "WBCSDKTablesImpl.h"
#import <MSSWBC/WBC.h>
#import <MSSWBC/WBCConstants.h>

using namespace com::vasco::digipass::sdk::utils::wbc;

static NSString *const kDomain = @"WBCSDK";

//NSString *const WBCSDK_VERSION = [NSString stringWithUTF8String:VERSION.c_str()];

@implementation WBCSDKWrapper

+ (NSData *)encrypt:(const unsigned char)mechanism mode:(const unsigned char)mode initialVector:(NSArray<NSNumber *>*)initialVector dataIn:(NSData *)dataIn error:(NSError **)error {
    
    WBCSDKTablesImpl wbcTables;
   
    NSData *encryptedData = [WBC encryptWithMechanism: mechanism
                                                 mode: mode
                                        initialVector: initialVector
                                               dataIn: dataIn
                                                table: [[WBCTableContainer alloc] initWithTable:&wbcTables]
                                                error: error];
    return encryptedData;
}

+ (NSData *)decrypt:(const unsigned char)mechanism mode:(const unsigned char)mode initialVector:(NSArray<NSNumber *>*)initialVector dataIn:(NSData *)dataIn error:(NSError **)error {
   
    WBCSDKTablesImpl wbcTables;
    
    NSData *decryptedData = [WBC decryptWithMechanism: mechanism
                                                 mode: mode
                                        initialVector: initialVector
                                               dataIn: dataIn
                                                table: [[WBCTableContainer alloc] initWithTable:&wbcTables]
                                                error: error];

    return decryptedData;
}

@end
