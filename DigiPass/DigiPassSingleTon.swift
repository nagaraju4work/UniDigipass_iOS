//
//  DigiPassSingleTon.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/24/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

enum UserCodingKeys: String {
    case user = "userName"
    case registrationID1 = "registrationID1"
    case activationPwd1 = "activationPwd1"
    case registrationID2 = "registrationID2"
    case activationPwd2 = "activationPwd2"
    case serverTime = "getServerTime"
    case deviceCode = "deviceCode"
    case systemBiometric = "systemBiometric"
    case clientEphemeralPrivateKey = "clientEphemeralPrivateKey"
    case clientEphemeralPublicKey = "clientEphemeralPublicKey"
    case clientEvidenceMessage = "clientEvidenceMessage"
    case sessionKey = "sessionKey"
    case serverEphemeralPublicKey = "serverEphemeralPublicKey"
    case salt = "salt"
    case notificationIdentifierText = "notificationIdentifierText"
    case decryptedMessage = "decryptedMessage"
    case activatedMessage = "activatedMessage"
}

@objc class DigiPassSingleTon: NSObject {
    static let shared: DigiPassSingleTon = DigiPassSingleTon()
    
    let STORAGE_NAME = "DigiPass"
    let FINGERPRINT = "12345"
    let ITERATION_NUMBER:Int32 = 8000
    
    @objc class func sharedInstance() -> DigiPassSingleTon {
        return DigiPassSingleTon.shared
    }
    
    private override init() {
        super.init()
//        do {
//        }catch { }
    }
    
    @objc let userIno: UserInfo = UserInfo()

}
