//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

/**
 * This exception is thrown when a problem occurs while managing a secure storage.
 */
@interface SecureStorageSDKException : NSException {
    
    int errorCode ;
    
    NSException * exception ;
    
}

/**
 * Instanciate and init a SecureStorageSDKException
 */
-(id) initWithCause:(NSException *) cause andError:(int) errorCode ;

/**
 * Instanciate and init a SecureStorageSDKException 
 */
-(id) initWithError:(int) errorCode ;

/** Indicates the causes of the error */
@property int errorCode ;

/** The cause of the error as a NSException */
@property (nonatomic , strong) NSException * exception ;

@end
