//
//  DSAPPSRPServerTimeResModel.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/23/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

class DSAPPSRPServerTimeResModel: Decodable {
    
    let resultCodes : ResultCodes?
    let result : DSAPPServerTimeResult?
    
    enum CodingKeys: String, CodingKey {
        
        case resultCodes = "resultCodes"
        case result = "result"
    }
    
    required init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        resultCodes = try values.decodeIfPresent(ResultCodes.self, forKey: .resultCodes)
        result = try values.decodeIfPresent(DSAPPServerTimeResult.self, forKey: .result)
    }
}

struct DSAPPServerTimeResult : Decodable {
    let serverTime: vds_int32?
    
    enum CodingKeys: String, CodingKey {
        
        case serverTime = "serverTime"
    }
    
    init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        serverTime = try values.decodeIfPresent(vds_int32.self, forKey: .serverTime)
    }
    
}
