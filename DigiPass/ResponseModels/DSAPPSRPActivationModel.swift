//
//  DSAPPSRPActivationModel.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/22/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

class DSAPPSRPActivationModel: Decodable {
    
    let resultCodes : ResultCodes?
    let result : DSAPPActivationResult?
    
    enum CodingKeys: String, CodingKey {
        
        case resultCodes = "resultCodes"
        case result = "result"
    }
    
    required init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        resultCodes = try values.decodeIfPresent(ResultCodes.self, forKey: .resultCodes)
        result = try values.decodeIfPresent(DSAPPActivationResult.self, forKey: .result)
    }
}

struct DSAPPActivationResult : Decodable {
    let serverEvidenceMessage: String?
    let encryptedLicenseActivationMessage: String?
    let encryptedCounter: String?
    let mac: String?
    
    enum CodingKeys: String, CodingKey {
       
        case serverEvidenceMessage = "serverEvidenceMessage"
        case encryptedLicenseActivationMessage = "encryptedLicenseActivationMessage"
        case encryptedCounter = "encryptedCounter"
        case mac = "mac"
    }
    
    init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        serverEvidenceMessage = try values.decodeIfPresent(String.self, forKey: .serverEvidenceMessage)
        encryptedLicenseActivationMessage = try values.decodeIfPresent(String.self, forKey: .encryptedLicenseActivationMessage)
        encryptedCounter = try values.decodeIfPresent(String.self, forKey: .encryptedCounter)
        mac = try values.decodeIfPresent(String.self, forKey: .mac)
    }
    
}
