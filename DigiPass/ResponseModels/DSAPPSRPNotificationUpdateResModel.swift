//
//  DSAPPSRPNotificationUpdateResModel.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 8/5/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

class DSAPPSRPNotificationUpdateResModel: Decodable {
    
    let resultCodes : ResultCodes?
    
    enum CodingKeys: String, CodingKey {
        case resultCodes = "resultCodes"
    }
    
    required init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        resultCodes = try values.decodeIfPresent(ResultCodes.self, forKey: .resultCodes)
    }
}

class DSAPPSRPPrepareSecureResModel: Decodable {
    
    let resultCodes : ResultCodes?
    let result : DSAPPPrepareSecureResult?

    enum CodingKeys: String, CodingKey {
        case resultCodes = "resultCodes"
        case result = "result"
    }
    
    required init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        resultCodes = try values.decodeIfPresent(ResultCodes.self, forKey: .resultCodes)
        result = try values.decodeIfPresent(DSAPPPrepareSecureResult.self, forKey: .result)
    }
}

struct DSAPPPrepareSecureResult : Decodable {
    let activationMessage: String?
    
    enum CodingKeys: String, CodingKey {
        case activationMessage = "requestMessage"
    }
    
    init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        activationMessage = try values.decodeIfPresent(String.self, forKey: .activationMessage)
    }
    
}
