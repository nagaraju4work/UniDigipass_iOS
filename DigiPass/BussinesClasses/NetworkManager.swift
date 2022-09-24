//
//  NetworkManager.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 7/22/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation
import FirebaseAnalytics

class NetworkManager:NSObject, URLSessionDelegate {
    let scheme: String = "https://"
    let host: String = "mfa.adpolice.gov.ae" //"mfa.adpolice.gov.ae" //unicorptech.com"
    let port: String = "11080"

    static let shared: NetworkManager = NetworkManager()
    
    private override init() {
        super.init()
    }
    
    func generateDSAPPSRPGenerateEphemeralKey(registraion: String, clientPublicKey: String, completionHandler: @escaping (_ response: DSAPPEphemeralResponseModel?, _ error: Error?) -> Void) {
        let path = "/rest/v2/provisioning/DSAPPSRPGenerateEphemeralKey"
        let urlStr = "\(scheme)\(host):\(port)\(path)"
        let jsonDict = ["clientEphemeralPublicKey": clientPublicKey, "registrationIdentifier": registraion]
        let body = try? JSONSerialization.data(withJSONObject: jsonDict, options: .prettyPrinted)
        if let url = URL(string: urlStr) {
            execute(url: url, body: body) { (data, response, error) in
                
                if let d = data {
                    do {
                        let jsonDecoder = JSONDecoder()
                        let responseModel = try jsonDecoder.decode(DSAPPEphemeralResponseModel.self, from: d)
                        completionHandler(responseModel, error)
                    }catch let error {
                        Analytics.logEvent("generateDSAPPSRPGenerateEphemeralKey", parameters: [
                            "error": error.localizedDescription as NSObject,
                            ])
                    }
                    
                }
            }
        }
    }
    
    func generateDSAPPSRPGenerateActivationData(registraion: String, clientEvidenceMessage: String, completionHandler: @escaping (_ response: DSAPPSRPActivationModel?, _ error: Error?) -> Void) {
        let path = "/rest/v2/provisioning/DSAPPSRPGenerateActivationData"
        let urlStr = "\(scheme)\(host):\(port)\(path)"
        let jsonDict = ["clientEvidenceMessage": clientEvidenceMessage, "registrationIdentifier": registraion]
        let body = try? JSONSerialization.data(withJSONObject: jsonDict, options: .prettyPrinted)
        if let url = URL(string: urlStr) {
            execute(url: url, body: body) { (data, response, error) in
                
                if let d = data {
                    do {
//                        print("Response for \(#function): \(String(data: d, encoding: .utf8))")
                        let jsonDecoder = JSONDecoder()
                        let responseModel = try jsonDecoder.decode(DSAPPSRPActivationModel.self, from: d)
                        completionHandler(responseModel, error)
                    }catch let error {
                        Analytics.logEvent("generateDSAPPSRPGenerateActivationData", parameters: [
                            "error": error.localizedDescription as NSObject,
                            ])
                    }
                    
                }
            }
        }
    }
    
    func DSAPPSRPMDIAddDeviceRequest(registraion: String, deviceCode: String, completionHandler: @escaping (_ response: DSAPPSRPMDIAddDeviceResModel?, _ error: Error?) -> Void) {
        let path = "/rest/v2/provisioning/MdlAddDevice"
        let urlStr = "\(scheme)\(host):\(port)\(path)"
        let jsonDict = ["deviceCode": deviceCode, "registrationIdentifier": registraion]
        let body = try? JSONSerialization.data(withJSONObject: jsonDict, options: .prettyPrinted)
        if let url = URL(string: urlStr) {
            execute(url: url, body: body) { (data, response, error) in
                
                if let d = data {
                    do {
                        let jsonDecoder = JSONDecoder()
                        let responseModel = try jsonDecoder.decode(DSAPPSRPMDIAddDeviceResModel.self, from: d)
                        completionHandler(responseModel, error)
                    }catch let error {
                        Analytics.logEvent("DSAPPSRPMDIAddDeviceRequest", parameters: [
                            "error": error.localizedDescription as NSObject,
                            ])
                    }
                }
            }
        }
    }
    
    func DSAPPSRPMDIActivateRequest(registraion: String, signature: String, completionHandler: @escaping (_ response: DSAPPSRPMDIActivateResModel?, _ error: Error?) -> Void) {
        let path = "/rest/v2/provisioning/MdlActivate"
        let urlStr = "\(scheme)\(host):\(port)\(path)"
        let jsonDict = ["signature": signature, "registrationIdentifier": registraion]
        let body = try? JSONSerialization.data(withJSONObject: jsonDict, options: .prettyPrinted)
        if let url = URL(string: urlStr) {
            execute(url: url, body: body) { (data, response, error) in
                
                if let d = data {
                    do {
                        let jsonDecoder = JSONDecoder()
                        let responseModel = try jsonDecoder.decode(DSAPPSRPMDIActivateResModel.self, from: d)
                        completionHandler(responseModel, error)
                    }catch let error {
                        Analytics.logEvent("DSAPPSRPMDIActivateRequest", parameters: [
                            "error": error.localizedDescription as NSObject,
                            ])
                    }
                }
            }
        }
    }
    
    func getServerTime(completionHandler: @escaping (_ response: DSAPPSRPServerTimeResModel?, _ error: Error?) -> Void) {
        let path = "/rest/v2/provisioning/getServerTime"
        let urlStr = "\(scheme)\(host):\(port)\(path)"
        if let url = URL(string: urlStr) {
            execute(url: url, body: nil) { (data, response, error) in
                if let d = data {
                    do {
                        let jsonDecoder = JSONDecoder()
                        let responseModel = try jsonDecoder.decode(DSAPPSRPServerTimeResModel.self, from: d)
                        completionHandler(responseModel, error)
                    }catch let error {
                        Analytics.logEvent("getServerTime", parameters: [
                            "error": error.localizedDescription as NSObject,
                            ])
                    }
                    
                }
            }
        }
    }
    
    func updateNotificationID(notificationToken: String, completionHandler: @escaping (_ response: DSAPPSRPNotificationUpdateResModel?, _ error: Error?) -> Void) {
        
        let userObj = DigiPassSharedData.sharedInstance().currentUser()
        
        if let userName = userObj["userName"] as? String, userName.count > 0 {
            let jsonBody: (String) -> Data? = { (token) in
                
                let messageModel = DIGIPassClientSDKWrapper.generateSecureChannelINotificationToken(notificationToken)
                let sequenceNumber = DIGIPassClientSDKWrapper.getDigiPassPropertyInt(vds_int32(PROPERTY_SEQUENCE_NUMBER), cryptoIndex: vds_int32(CRYPTO_APPLICATION_INDEX_APP_1))
                let serialNumber = messageModel.serialNumber
                let finalStr = "\(serialNumber)-\(sequenceNumber)"
                
                let domain = "unicorptech.com"//"auh.police" //"unicorptech.com"
                let encryptionNotificationID = messageModel.rawData
                let userID = userName
                
                let requestBody = ["digipassInstanceID": finalStr,
                                   "domain": domain,
                                   "encryptedNotificationID": encryptionNotificationID,
                                   "userID": userID]
                
                do {
                    let body = try JSONSerialization.data(withJSONObject: requestBody, options: .prettyPrinted)
                    return body
                }catch let error {
                    Analytics.logEvent("updateNotificationID", parameters: [
                        "error": error.localizedDescription as NSObject,
                        ])
                }
                return nil
            }
            
            let path = "/rest/v2/notification/push/updateNotificationID"
            let urlStr = "\(scheme)\(host):\(port)\(path)"
            
            if let url = URL(string: urlStr) {
                execute(url: url, body: jsonBody(notificationToken)) { (data, response, error) in
                    if let d = data {
                        do {
                            let jsonDecoder = JSONDecoder()
                            let responseModel = try jsonDecoder.decode(DSAPPSRPNotificationUpdateResModel.self, from: d)
                            completionHandler(responseModel, error)
                        }catch let error {
                            Analytics.logEvent("updateNotificationID", parameters: [
                                "error": error.localizedDescription as NSObject,
                                ])
                        }
                        
                    }
                }
            }
        }
    }
    
    func authenticateUserLoginRequest(requestBody: [String: Any], completionHandler: @escaping (_ response: [String: Any]?, _ error: Error?) -> Void) {
        
        let path = "/rest/v2/authentication/push/authUser"
        let urlStr = "\(scheme)\(host):\(port)\(path)"
//        print(requestBody)
        do {
            let body = try JSONSerialization.data(withJSONObject: requestBody, options: .prettyPrinted)
            if let url = URL(string: urlStr) {
                execute(url: url, body: body) { (data, response, error) in
                    if let d = data {
//                        print("Response: \(String(data: d, encoding: .utf8) ?? "")")
                        do {
                            let json = try JSONSerialization.jsonObject(with: d, options: .mutableContainers) as? [String: Any]
                            completionHandler(json, error)
                        }catch let error {
                            Analytics.logEvent("authenticateUserLoginRequest", parameters: [
                                "error": error.localizedDescription as NSObject,
                                ])
                        }
                    }
                }
            }
        }catch {  }
    }
    
    func cancelUserLoginRequest(requestBody: [String: Any], completionHandler: @escaping (_ response: [String: Any]?, _ error: Error?) -> Void) {
        
        let path = "/rest/v2/authentication/push/cancelAuthUser"
        let urlStr = "\(scheme)\(host):\(port)\(path)"
//        print(requestBody)
        if let url = URL(string: urlStr) {
            do {
                let body = try JSONSerialization.data(withJSONObject: requestBody, options: .prettyPrinted)
                execute(url: url, body: body) { (data, response, error) in
                    if let d = data {
                        do {
//                            print("Response: \(String(data: d, encoding: .utf8) ?? "")")
                            let json = try JSONSerialization.jsonObject(with: d, options: .mutableContainers) as? [String: Any]
                            completionHandler(json, error)
                        }catch let error {
                            Analytics.logEvent("cancelUserLoginRequest", parameters: [
                                "error": error.localizedDescription as NSObject,
                                ])
                        }
                    }
                }
            }catch {   }
        }
    }
    
    func preparedSecureChannel(message: SecureChannelMessageWrapper, challengeKey: String, completionHandler: @escaping (_ response: DSAPPSRPPrepareSecureResModel?, _ error: Error?) -> Void) {
       
        let userObj = DigiPassSharedData.sharedInstance().currentUser()
        
        if let userName = userObj["userName"] as? String, userName.count > 0 {
            let jsonBody: (SecureChannelMessageWrapper,String) -> Data? = { (message,challenge) in
                
                let sequenceNumber = DIGIPassClientSDKWrapper.getDigiPassPropertyInt(vds_int32(PROPERTY_SEQUENCE_NUMBER), cryptoIndex: vds_int32(CRYPTO_APPLICATION_INDEX_APP_1))
                let serialNumber = message.serialNumber
                let finalStr = "\(serialNumber)-\(sequenceNumber)"
                
                let requestBody = ["serialNumber": finalStr,
                                   "challengeKey": challenge]
                
                do {
                    let body = try JSONSerialization.data(withJSONObject: requestBody, options: .prettyPrinted)
                    return body
                }catch let error {
                    Analytics.logEvent("preparedSecureChannel", parameters: [
                        "error": error.localizedDescription as NSObject,
                        ])
                }
                return nil
            }
            
            let path = "/rest/v2/authentication/push/getPreparedSecureChallenge"
            let urlStr = "\(scheme)\(host):\(port)\(path)"
            
            if let url = URL(string: urlStr) {
                execute(url: url, body: jsonBody(message, challengeKey)) { (data, response, error) in
                    if let d = data {
                        do {
                            let jsonDecoder = JSONDecoder()
                            let responseModel = try jsonDecoder.decode(DSAPPSRPPrepareSecureResModel.self, from: d)
                            completionHandler(responseModel, error)
                        }catch let error {
                            Analytics.logEvent("preparedSecureChannel", parameters: [
                                "error": error.localizedDescription as NSObject,
                                ])
                        }
                        
                    }
                }
            }
        }
    }
    
    func execute(url: URL, body: Data?, completionHandler: @escaping (_ data: Data?, _ response: URLResponse?, _ error: Error?) -> Void) {
        
        let format = "\(DigiPassSingleTon.shared.userIno.APIKey):"
        let baseEncodedStr = format.data(using: .utf8)
        if let data = baseEncodedStr {
            let base64Encoded = data.base64EncodedString(options: Data.Base64EncodingOptions(rawValue: 0))
            let token = "Basic \(base64Encoded)"
            var request = URLRequest(url: url)
            request.addValue(token, forHTTPHeaderField: "Authorization")
            request.addValue("application/json", forHTTPHeaderField: "Content-Type")
            request.httpMethod = "POST"
            if let data = body {
                request.httpBody = data
            }
            let session = URLSession(configuration: URLSessionConfiguration.default, delegate: self, delegateQueue: nil)
            session.dataTask(with: request) { (data, response, error) in
                completionHandler(data, response, error)
                }.resume()
        }
    }
    
    func urlSession(_ session: URLSession, didReceive challenge: URLAuthenticationChallenge, completionHandler: @escaping (URLSession.AuthChallengeDisposition, URLCredential?) -> Void) {
        if (challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodClientCertificate) {
            completionHandler(.rejectProtectionSpace, nil)
        }
        if (challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodServerTrust) {
            let credential = URLCredential(trust: challenge.protectionSpace.serverTrust!)
            completionHandler(.useCredential, credential)
        }
    }
}

