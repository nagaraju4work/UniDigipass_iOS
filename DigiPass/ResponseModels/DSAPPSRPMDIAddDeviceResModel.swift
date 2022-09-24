//
//  DSAPPSRPAddDeviceResModel.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/23/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

class DSAPPSRPMDIAddDeviceResModel: Decodable {
    
    let resultCodes : ResultCodes?
    let result : DSAPPAddDeviceResult?
    
    enum CodingKeys: String, CodingKey {
        case resultCodes = "resultCodes"
        case result = "result"
    }
    
    required init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        resultCodes = try values.decodeIfPresent(ResultCodes.self, forKey: .resultCodes)
        result = try values.decodeIfPresent(DSAPPAddDeviceResult.self, forKey: .result)
    }
}

struct DSAPPAddDeviceResult : Decodable {
    let activationMessage: String?
    
    enum CodingKeys: String, CodingKey {
        case activationMessage = "instanceActivationMessage"
    }
    
    init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        activationMessage = try values.decodeIfPresent(String.self, forKey: .activationMessage)
    }
    
}
