//
//  DSAPPEphemeralResponseModel.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/22/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

class DSAPPEphemeralResponseModel: Decodable {
    
    let resultCodes : ResultCodes?
    let result : DSAPPEphemeralResult?
    
    enum CodingKeys: String, CodingKey {
        
        case resultCodes = "resultCodes"
        case result = "result"
    }
    
    required init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        resultCodes = try values.decodeIfPresent(ResultCodes.self, forKey: .resultCodes)
        result = try values.decodeIfPresent(DSAPPEphemeralResult.self, forKey: .result)
    }
}

struct DSAPPEphemeralResult : Decodable {
    let serverEphemeralPublicKey : String?
    let salt : String?
    
    enum CodingKeys: String, CodingKey {
        
        case serverEphemeralPublicKey = "serverEphemeralPublicKey"
        case salt = "salt"
    }
    
    init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        serverEphemeralPublicKey = try values.decodeIfPresent(String.self, forKey: .serverEphemeralPublicKey)
        salt = try values.decodeIfPresent(String.self, forKey: .salt)
    }
    
}

struct ResultCodes : Decodable {
    let returnCodeEnum : String?
    let statusCodeEnum : String?
    let returnCode : Int?
    let statusCode : Int?
    
    enum CodingKeys: String, CodingKey {
        
        case returnCodeEnum = "returnCodeEnum"
        case statusCodeEnum = "statusCodeEnum"
        case returnCode = "returnCode"
        case statusCode = "statusCode"
    }
    
    init(from decoder: Decoder) throws {
        let values = try decoder.container(keyedBy: CodingKeys.self)
        returnCodeEnum = try values.decodeIfPresent(String.self, forKey: .returnCodeEnum)
        statusCodeEnum = try values.decodeIfPresent(String.self, forKey: .statusCodeEnum)
        returnCode = try values.decodeIfPresent(Int.self, forKey: .returnCode)
        statusCode = try values.decodeIfPresent(Int.self, forKey: .statusCode)
    }
    
}
