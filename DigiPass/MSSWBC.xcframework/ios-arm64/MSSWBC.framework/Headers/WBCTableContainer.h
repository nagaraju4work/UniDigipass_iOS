////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This object encapsulates a Crypto Table (CPP file)
 */
@interface WBCTableContainer: NSObject
/**
 * Initialize a WBCTableContainer with a WBCSDKTables
 * @param table the WBCSDKTables object generated with the WBCSDKTableGenerator.exe
 */
-(instancetype)initWithTable:(void*)table;
+(instancetype)new NS_UNAVAILABLE;
-(instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
