//
//  MDActivateModelWrapper.h
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DigipassSDK/DP4Capi.h>

NS_ASSUME_NONNULL_BEGIN

@interface MDActivateInstanceModelWrapper : NSObject

@property SecureChannelMessage message;

@end

@interface MDGenerateSignatureModelWrapper : NSObject

@property (strong, nonatomic) NSData* responseData;
@property (strong, nonatomic) NSData* hostCodeData;
@property (strong, nonatomic) NSString* pin;

@end

NS_ASSUME_NONNULL_END
