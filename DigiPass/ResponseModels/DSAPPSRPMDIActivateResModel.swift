//
//  DSAPPSRPMDIActivateResModel.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/23/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

class DSAPPSRPMDIActivateResModel: Decodable {
    
    let resultCodes : ResultCodes?
    
    enum CodingKeys: String, CodingKey {
        case resultCodes = "resultCodes"
    }
    
    required init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        resultCodes = try values.decodeIfPresent(ResultCodes.self, forKey: .resultCodes)
    }
}


