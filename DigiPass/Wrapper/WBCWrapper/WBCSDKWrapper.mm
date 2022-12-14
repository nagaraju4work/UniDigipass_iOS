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
    //    try {
    //Create a new WBCSDKTables object that will access your tables.
    //The WBCSDKTablesImpl file must be generated with the WBCSDKTableGenerator.exe
    WBCSDKTablesImpl wbcTables;
    
    // create and format input and output data
    /*long int inputLength = dataIn.length;
     long int encryptedLength = inputLength;
     unsigned char* input = (unsigned char*) [dataIn bytes];
     
     //We add 1 to the length to account for the end of string character
     unsigned char encrypted[encryptedLength + 1];
     
     //Convert the string input into a byte array input
     memset(encrypted, 0, encryptedLength + 1);
     
     //Convert NSArray to unsigned char*
     long int ivLength = [initialVector count];
     unsigned char iv[ivLength];
     memset(iv, 0, ivLength + 1);
     for (int i = 0; i<ivLength; i++) {
     iv[i] = [initialVector[i] unsignedCharValue];
     }*/
    
    NSData *encryptedData = [WBC encryptWithMechanism: mechanism
                                                 mode: mode
                                        initialVector: initialVector
                                               dataIn: dataIn
                                                table: [[WBCTableContainer alloc] initWithTable:&wbcTables]
                                                error: error];
    if (error) {
        // Handle the error and return.
        NSLog(@"Error with encryption - errorCode: %ld", error);
    }
    return encryptedData;
    
    //        WBCSDK::encrypt(mechanism, mode, &wbcTables, iv, ivLength, input, inputLength, encrypted, &encryptedLength);
    
    //        NSData* data = [NSData dataWithBytes:(const void *)encryptedData length:encryptedLength];
    
    //        return data;
    //    }
    //    catch (WBCSDKException &e) {
    //        *error = [[NSError alloc] initWithDomain:kDomain code:e.getErrorCode() userInfo:nil];
    //        return nil;
    //    }
}

+ (NSData *)decrypt:(const unsigned char)mechanism mode:(const unsigned char)mode initialVector:(NSArray<NSNumber *>*)initialVector dataIn:(NSData *)dataIn error:(NSError **)error {
    //    try {
    //Create a new WBCSDKTables object that will access your tables.
    //The WBCSDKTablesImpl file must be generated with the WBCSDKTableGenerator.exe
    WBCSDKTablesImpl wbcTables;
    
    // create and format input and output data
    /*long int inputLength = dataIn.length;
     long int decryptedLength = inputLength;
     unsigned char* input = (unsigned char*) [dataIn bytes];
     
     //We add 1 to the length to account for the end of string character
     unsigned char decrypted[decryptedLength + 1];
     
     //Convert the string input into a byte array input
     memset(decrypted, 0, decryptedLength + 1);
     
     //Convert NSArray to unsigned char*
     long int ivLength = [initialVector count];
     unsigned char iv[ivLength];
     memset(iv, 0, ivLength + 1);
     for (int i = 0; i<ivLength; i++) {
     iv[i] = [initialVector[i] unsignedCharValue];
     }*/
    
    NSData *decryptedData = [WBC decryptWithMechanism: mechanism
                                                 mode: mode
                                        initialVector: initialVector
                                               dataIn: dataIn
                                                table: [[WBCTableContainer alloc] initWithTable:&wbcTables]
                                                error: error];
    if (error) {
        // Handle the error and return.
        NSLog(@"Error with decryption - errorCode: %s", error);
    }
    return decryptedData;
    
    /*WBCSDK::encrypt(mechanism, mode, &wbcTables, iv, ivLength, input, inputLength, decrypted, &decryptedLength);
     
     NSData* data = [NSData dataWithBytes:(const void *)decrypted length:decryptedLength];
     
     return data;
     }
     catch (WBCSDKException &e) {
     *error = [[NSError alloc] initWithDomain:kDomain code:e.getErrorCode() userInfo:nil];
     return nil;
     }*/
}

@end
