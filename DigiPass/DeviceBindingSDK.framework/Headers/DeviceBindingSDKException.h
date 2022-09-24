//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) since 1999. VASCO DATA SECURITY
//  All rights reserved. http://www.vasco.com
//
//////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>

/**
 * This exception is thrown when a problem occurs while generating the device fingerprint.
 */
@interface DeviceBindingSDKException : NSException {
    
    int errorCode ;

    NSException * exception ;
    
}

/** Indicates the causes of the error */
@property int errorCode ;

/** The cause of the error as a NSException */
@property (nonatomic , strong) NSException * exception ;

/**
 * Instanciate and init a DeviceBindingSDKException
 */
-(id) initWithError:(int) errorCode ;

/**
 * Instanciate and initialize a DeviceBindingSDKException
 */
-(id) initWithCause:(NSException *) cause ;

@end

