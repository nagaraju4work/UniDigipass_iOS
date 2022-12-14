//
//  UserInfo.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import UIKit

@objc class UserInfo: NSObject {
    override init() {
        super.init()
        
        let storageData: Data = X_SALT_STORAGE.data(using: .ascii)!
        let digipassData: Data = X_SALT_DIGIPASS.data(using: .ascii)!
        let apikeyData: Data = X_API_KEY.data(using: .ascii)!
        
        do {
           let encryptStorage = try  WBCSDKWrapper.encrypt(CRYPTO_MECHANISM_AES, mode: CRYPTO_MODE_CTR, initialVector: IV_Storage, dataIn: storageData)
            let encryptDigipass = try  WBCSDKWrapper.encrypt(CRYPTO_MECHANISM_AES, mode: CRYPTO_MODE_CTR, initialVector: IV_DigiPass, dataIn: digipassData)
            let encryptAPIKey = try  WBCSDKWrapper.encrypt(CRYPTO_MECHANISM_AES, mode: CRYPTO_MODE_CTR, initialVector: IV_APIKey, dataIn: apikeyData)

            let storageDecryptedData = try WBCSDKWrapper.decrypt(CRYPTO_MECHANISM_AES, mode: CRYPTO_MODE_CTR, initialVector: IV_Storage, dataIn: encryptStorage)
            
            SALT_STORAGE = String(data: storageDecryptedData, encoding: .ascii)!
            
            let digipassDecryptedData = try WBCSDKWrapper.decrypt(CRYPTO_MECHANISM_AES, mode: CRYPTO_MODE_CTR, initialVector: IV_DigiPass, dataIn: encryptDigipass)
            
            SALT_DIGIPASS = String(data: digipassDecryptedData, encoding: .ascii)!
            
            let apiKeyDecryptedData = try WBCSDKWrapper.decrypt(CRYPTO_MECHANISM_AES, mode: CRYPTO_MODE_CTR, initialVector: IV_APIKey, dataIn: encryptAPIKey)
            APIKey = String(data: apiKeyDecryptedData, encoding: .ascii)!
            
        } catch {
            // TODO Crashlytics
        }
    }

    let IV_Storage: [NSNumber] = [0x24, 0x16, 0x43, 0x08, 0x4D, 0x1A, 0x33, 0x40, 0x39, 0x29, 0x40, 0x04, 0x5E, 0x14, 0x32, 0x38]
    let IV_DigiPass: [NSNumber] = [0x4A, 0x4F, 0x20, 0x17, 0x19, 0x0C, 0x5E, 0x14, 0x07, 0x15, 0x10, 0x44, 0x2E, 0x24, 0x00, 0x30]
    let IV_APIKey: [NSNumber] = [0xA5, 0x46, 0x10, 0xA6, 0x58, 0xD3, 0x73, 0xB5, 0xE5, 0x65, 0xA7, 0x74, 0xF5, 0xA7, 0x74, 0xF5]

    var APIKey: String = ""
    var vascoDeviceIdentifier: String? = nil
    
    private let X_API_KEY = "4AD105399DA22EDFAB42E2AD7EEBCEC5DD68F99F018FB3668D2F59C10C1D5467"/*"5E7A51B33629147F2F0022B471048F937755165CDC5135F72D220C46663D2F7C"*/
//    private let X_SALT_STORAGE = "A8216219ABC582A5F377AD3BE7EEF1106E54CA10398400F514287F4AA678B95A"
    private let X_SALT_STORAGE = "69F9BED16935A97367A7EC210DA135AF3A35099335441C863A1780703E47539C"
//    private let X_SALT_DIGIPASS = "9BF7B93BA05E3B0284F7069918F743C0B503D6D27A6F9E6B89CDEF583611CB83"
    private let X_SALT_DIGIPASS = "9C928B616BEAA96C7F95E0335238DE8B5EF0BE8ECB08AC6FCC221C82DFA6D4F9"
    
    @objc  var SALT_STORAGE = "";
    @objc var SALT_DIGIPASS = "";
    
    @objc  var staticVector = ""
}
