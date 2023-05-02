//
//  DigiPassActivation.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 8/2/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation
//import FirebaseAnalytics

protocol DigiPassActivationDelegate {
    func showPinScreen(handler: @escaping ((_ pin: String?) -> Void))
    func confirmPin(pin: String, handler: @escaping ((_ confirmPin: String?) -> Void))
    func didCompleteActivateProcess()
    func didFailedActivationProcess()
}

enum ActivationErrors: Error {
    case failed(String)
    case requiredCredentials
}

class DigiPassActivation {
    
    enum Activation {
        case withRegistrationIDOne
        case withRegistrationIDTwo
    }
    
    enum AuthenticationType {
        case pin
        case biometric
    }
    
    var delegate: DigiPassActivationDelegate? = nil
    var activationModel:DSAPPSRPActivationModel!
    var activationType: Activation = .withRegistrationIDOne

    func getCredentials() -> (String, String)? {
        let registrationIDKey = activationType == .withRegistrationIDOne ? UserCodingKeys.registrationID1.rawValue : UserCodingKeys.registrationID2.rawValue
        let passwordKey = activationType == .withRegistrationIDOne ? UserCodingKeys.activationPwd1.rawValue : UserCodingKeys.activationPwd2.rawValue

        do {
            let registrationID1 = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(registrationIDKey)
            let password1 = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(passwordKey)
            return (registrationID1,password1)
            
        }catch let error {
            
            print("getCredentials")
            
            Logger.log("getCredentials: "+error.localizedDescription)
            
//            Analytics.logEvent("getCredentials", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
        }
        return nil
    }
    
    func startActivateUser(activate: Activation) {
        self.activationType = activate
        let type = activate == .withRegistrationIDOne ? "pin" : "biometric"
        UserDefaults.standard.set(type, forKey: "activationType")

        do {
            guard let (registration, password) =  getCredentials() else {
                throw ActivationErrors.requiredCredentials
                self.delegate?.didFailedActivationProcess()
            }
            
            try validateSRPUserPasswordChecksum(password: password)
          
            try demoGenerateSRPClientEphemeralKey()
          
            try generatEphemeralKey()

            try self.generateSRPSessionKey(userName: registration, password: password)
            
            generateActivationData(registration: registration)
            
            try self.verifySRPServerEvidenceMessage(activationModel: activationModel)
            
            try self.multiDeviceActivateLicence()
            
            multiDeviceActivateInstance()

        }catch let error {
//            Analytics.logEvent("startActivateUser", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
            
            Logger.log("startActivateUser: "+error.localizedDescription)
            
            print("startActivateUser")

            
            DispatchQueue.main.async {
                
                
//                self.delegate?.didFailedActivationProcess()
//                AppDelegate.shared.window?.rootViewController?.displayAlert(titleText: "Error", messageText: error.localizedDescription)
                
            }
        }
    }
    
    private func validateSRPUserPasswordChecksum(password: String) throws
    {
        do {
            try DSAPPClientWrapper.validateSRPUserPasswordChecksum(password)
           // print("SRP user password checksum validation successful \n\n")
        } catch let error {
            
            print("validateSRPUserPasswordChecksum")
            
            Logger.log("validateSRPUserPasswordChecksum: "+error.localizedDescription)
            
//            Analytics.logEvent("validateSRPUserPasswordChecksum", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
        }
    }
    
    private  func demoGenerateSRPClientEphemeralKey() throws
    {
        do {
            let clientKeyResponse = try DSAPPClientWrapper.generateSRPClientEphemeralKey();
            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: clientKeyResponse.clientEphemeralPrivateKey, forKey: UserCodingKeys.clientEphemeralPrivateKey.rawValue)
            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: clientKeyResponse.clientEphemeralPublicKey, forKey: UserCodingKeys.clientEphemeralPublicKey.rawValue)

        } catch let error as NSError {
            delegate?.didFailedActivationProcess()
            
            print("demoGenerateSRPClientEphemeralKey")
            
            Logger.log("demoGenerateSRPClientEphemeralKey: "+error.localizedDescription)
            
//            Analytics.logEvent("demoGenerateSRPClientEphemeralKey", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
        }
    }
    
    private func generatEphemeralKey(handler: (() -> Void)? = nil) throws {
        
        guard let (registration, _) =  getCredentials() else {
            throw ActivationErrors.requiredCredentials
        }
        
        let semaphore = DispatchSemaphore(value: 0)
        
        do {
            let clientEphemeralPublicKey = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.clientEphemeralPublicKey.rawValue)
            NetworkManager.shared.generateDSAPPSRPGenerateEphemeralKey(registraion: registration, clientPublicKey: clientEphemeralPublicKey) { (responseModel, error) in
                if let model = responseModel {
                    if let result = model.resultCodes?.returnCode, result == 0 {
                        try? DigiPassSharedData.sharedInstance().secureCache.putString(forValue: model.result?.serverEphemeralPublicKey ?? "", forKey: UserCodingKeys.serverEphemeralPublicKey.rawValue)
                        try? DigiPassSharedData.sharedInstance().secureCache.putString(forValue: model.result?.salt ?? "", forKey: UserCodingKeys.salt.rawValue)

                        //self.ephemeralModel = model
                    }else {
                        self.delegate?.didFailedActivationProcess()
                    }
                }else {
                    self.delegate?.didFailedActivationProcess()
                }
                semaphore.signal()
            }
            _ = semaphore.wait(timeout: DispatchTime.distantFuture)
        }catch let error {
            delegate?.didFailedActivationProcess()
            
            print("generatEphemeralKey")
            
            Logger.log("generatEphemeralKey: "+error.localizedDescription)
            
//            Analytics.logEvent("generatEphemeralKey", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
        }
        
    }
    
    private func generateSRPSessionKey(userName: String,
                                       password: String) throws
    {
        do {
             let clientEphemeralPublicKey = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.clientEphemeralPublicKey.rawValue)
             let clientEphemeralPrivateKey = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.clientEphemeralPrivateKey.rawValue)
            let serverEphemeralPublicKey = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.serverEphemeralPublicKey.rawValue)
            let salt = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.salt.rawValue)

            let sessionKeyResponse =
                try DSAPPClientWrapper.generateSRPSessionKey(withClientEphemeralPublicKey: clientEphemeralPublicKey,
                                                             clientEphemeralPrivateKey: clientEphemeralPrivateKey,
                                                             serverEphemeralPublicKey: serverEphemeralPublicKey,
                                                             registrationIdentifier: userName,
                                                             activationPassword: password,
                                                             salt: salt)
            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: sessionKeyResponse.sessionKey, forKey: UserCodingKeys.sessionKey.rawValue)
            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: sessionKeyResponse.clientEvidenceMessage, forKey: UserCodingKeys.clientEvidenceMessage.rawValue)
            
        } catch let error as NSError {
            delegate?.didFailedActivationProcess()
            
            print("generateSRPSessionKey")
            
            Logger.log("generateSRPSessionKey: "+error.localizedDescription)
            
//            Analytics.logEvent("generateSRPSessionKey", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
            throw ActivationErrors.failed(error.localizedDescription)
        }
    }
    
    private func generateActivationData(registration: String, handler: (() -> Void)? = nil) {
        
        do {
            let semaphore = DispatchSemaphore(value: 0)
            let clientEvidenceMessage = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.clientEvidenceMessage.rawValue)
            
            NetworkManager.shared.generateDSAPPSRPGenerateActivationData(registraion: registration, clientEvidenceMessage: clientEvidenceMessage) { (responseModel, error) in
                if let model = responseModel {
                    if let result = model.resultCodes?.returnCode, result == 0 {
                        self.activationModel = model
                    }else {
                        self.delegate?.didFailedActivationProcess()
                    }
                }else {
                    self.delegate?.didFailedActivationProcess()
                }
                semaphore.signal()
            }
            _ = semaphore.wait(timeout: DispatchTime.distantFuture)
        }catch let error {
            delegate?.didFailedActivationProcess()
            
            print("generateActivationData")
            
            Logger.log("generateActivationData: "+error.localizedDescription)
            
//            Analytics.logEvent("generateActivationData", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
        }
    }
    
    private func verifySRPServerEvidenceMessage(activationModel: DSAPPSRPActivationModel) throws
    {
        
        do {
            // Tries to verify the Server Evidence Message
            let clientEphemeralPublicKey = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.clientEphemeralPublicKey.rawValue)
            let clientEvidenceMessage = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.clientEvidenceMessage.rawValue)
            let sessionKey = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.sessionKey.rawValue)

            try DSAPPClientWrapper.verifySRPServerEvidenceMessage(withClientEphemeralPublicKey: clientEphemeralPublicKey,
                                                                  clientEvidenceMessage: clientEvidenceMessage,
                                                                  serverEvidenceMessage: activationModel.result?.serverEvidenceMessage ?? "",
                                                                  clientSessionKey: sessionKey)
                        
            let decrypted: String = try DSAPPClientWrapper.decryptSRPData(
                withClientSessionKey: sessionKey,
                encryptedData: activationModel.result!.encryptedLicenseActivationMessage!,
                encryptedCounter: activationModel.result!.encryptedCounter!,
                mac: activationModel.result!.mac!)
           
            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: decrypted, forKey: UserCodingKeys.decryptedMessage.rawValue)
            
            //message = parseSecureChannelMessage(decrypted: decrypted)
    
        } catch let error as NSError {
            delegate?.didFailedActivationProcess()
            
            print("verifySRPServerEvidenceMessage")
            
            Logger.log("verifySRPServerEvidenceMessage: "+error.localizedDescription)
            
//            Analytics.logEvent("verifySRPServerEvidenceMessage", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
            throw ActivationErrors.failed(error.localizedDescription)
        }
    }
    
    private func multiDeviceActivateLicence() throws {
        
        DIGIPassClientSDKWrapper.multiDeviceLicenceActivation()
       
        do {
            let deviceCode = try DigiPassSharedData.sharedInstance().secureCache.getBytesForKey(UserCodingKeys.deviceCode.rawValue)
            let deviceCodeStr = String(bytes: deviceCode, encoding: .utf8)?.replacingOccurrences(of: "\0", with: "")
            
            guard let (registration, _) =  getCredentials() else {
                throw ActivationErrors.requiredCredentials
            }
            
            let semaphore = DispatchSemaphore(value: 0)

            NetworkManager.shared.DSAPPSRPMDIAddDeviceRequest(registraion: registration, deviceCode: deviceCodeStr!) { (response, error) in
                if let model = response {
                    if let result = model.resultCodes?.returnCode, result == 0 {
                        if let activateMsg = model.result?.activationMessage {
                            do {
                                try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: activateMsg, forKey: UserCodingKeys.activatedMessage.rawValue)
                            }catch { }
                            //self.message = self.parseSecureChannelMessage(decrypted: activateMsg)
                        }
                    }else {
                        self.delegate?.didFailedActivationProcess()
                    }
                }else {
                    self.delegate?.didFailedActivationProcess()
                }
                semaphore.signal()
            }
            _ = semaphore.wait(timeout: DispatchTime.distantFuture)
        } catch let error as NSError {
            delegate?.didFailedActivationProcess()
            
            print("verifySRPServerEvidenceMessage")
            
            Logger.log("verifySRPServerEvidenceMessage: "+error.localizedDescription)
            
//            Analytics.logEvent("verifySRPServerEvidenceMessage", parameters: [
//                "error": error.localizedDescription as NSObject,
//                ])
            throw ActivationErrors.failed(error.localizedDescription)
        }

    }
    
    private func multiDeviceActivateInstance() {
        
        let activate: (String) throws -> Void = { (pin) in
            let activateInstanceModel = DIGIPassClientSDKWrapper.multiDeviceActivateInstance(pin);

            let signaureModel: MDGenerateSignatureModelWrapper = DIGIPassClientSDKWrapper.generateSignature(fromPassword: pin, isActivateProcess: true)
            if let response = String(data: signaureModel.responseData, encoding: .utf8) {
                try self.MDIActivateRequest(signature: response, signatureModel: signaureModel)
            }
        }
        
        if activationType == .withRegistrationIDOne {
            showPinView { (pin) in
                try? activate(pin ?? "")
            }
        }else {
            try? activate("")
        }
    }
    
    private func MDIActivateRequest(signature: String, signatureModel: MDGenerateSignatureModelWrapper) throws {
        guard let (registration, _) =  getCredentials() else {
            throw ActivationErrors.requiredCredentials
        }
        NetworkManager.shared.DSAPPSRPMDIActivateRequest(registraion: registration, signature: signature) { (response, error) in
            if let model = response {
                if let result = model.resultCodes?.returnCode, result == 0 {
                    
                    if self.activationType == .withRegistrationIDOne {
                        let isBiometricSupport = self.willCheckDeviceBiometricSensorSupport()
                        
                        DigiPassSharedData.sharedInstance().moveFromCache(toPermanent: "pin")
                        
                        if isBiometricSupport {
                            self.startActivateUser(activate: .withRegistrationIDTwo)
                        }else {
                            // store active user
                            do {
                                let userName = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.user.rawValue)
                                let dict = ["userName": userName, "isPinSelected": "pin"] as [String : Any]
                                DigiPassSharedData.sharedInstance().addUsers(toDefaults: dict)
                                
                            }catch { }
                            
                            DispatchQueue.main.async {
                                self.delegate?.didCompleteActivateProcess()
                            }
                        }
                    } else {
                        do {
                            // WARNING !! NEVER WRITE THE SECURE CACHE
                            DigiPassSharedData.sharedInstance().moveFromCache(toPermanent: "biometric")
                            
                            let userName = try DigiPassSharedData.sharedInstance().secureCache.getStringForKey(UserCodingKeys.user.rawValue)
                            let dict = ["userName": userName, "isPinSelected": "biometric"] as [String : Any]
                            DigiPassSharedData.sharedInstance().addUsers(toDefaults: dict)

                        }catch { }
                        DispatchQueue.main.async {
                            self.delegate?.didCompleteActivateProcess()
                        }
                    }
                }else {
                    self.delegate?.didFailedActivationProcess()
                }
            }
        }
    }
    
    func willCheckDeviceBiometricSensorSupport() -> Bool {
        let isTouchID = checkDeviceBiometricTouchSensorSupport()
        let isFaceID = checkDeviceBiometricFaceIDSensorSupport()
        if isTouchID || isFaceID {
            return true
        }
        return false
    }
    
    func checkDeviceBiometricTouchSensorSupport() -> Bool {
        do {
            let isTouchIDSupport = try BiometricSensorSDK.isBiometricAuthenticationSupported(for: .touchId)
            let isTouchIDUsable = try BiometricSensorSDK.isBiometricAuthenticationEnrolled(for: .touchId)
            return (isTouchIDUsable && isTouchIDSupport)
        } catch {
            
        }
        return false
    }
    
    func checkDeviceBiometricFaceIDSensorSupport() -> Bool {
        do {
            let isFaceIDSupport = try BiometricSensorSDK.isBiometricAuthenticationSupported(for: .faceId)
            let isFaceIDUsable = try BiometricSensorSDK.isBiometricAuthenticationEnrolled(for: .faceId)
            return (isFaceIDUsable && isFaceIDSupport)
        } catch {
            
        }
        return false
    }
    
    func generatePin(entered pin: String, handler: @escaping (_ pin: String) -> Void) {
           /* let registrationId: (MDUserActivateModelWrapper) -> String = { (activatedUser) in
                if activatedUser.isPinSelected {
                    return activatedUser.registrationIdentifier1
                }
                return activatedUser.registrationIdentifier2
            }*/

            let otp = DIGIPassClientSDKWrapper.generateOTPCode(forPin: pin)
            DispatchQueue.main.async {
                handler(otp)
            }
    }
    
    func showPinView(handler: @escaping ((_ pin: String?) -> Void)) {
        delegate?.showPinScreen(handler: { (pin) in
            MCKPinController.dismiss(completion: {
                MCKPinController.reset()
                if let p = pin {
                    self.confirm(pin: p, handler: handler)
                }
            })
        })
    }
    
    func confirm(pin: String, handler: @escaping ((_ pin: String?) -> Void)) {
        self.delegate?.confirmPin(pin: pin, handler: { (confirmPin) in
            MCKPinController.dismiss(completion: {
                MCKPinController.reset()
            })
            if let p2 = confirmPin, pin != p2 {
                DispatchQueue.main.async {
                    DigiPassUtilities.showAlertOnRootVC(title: "Alert", message: "Confirm password is not matching with password", cancel: "Ok", cancelHandler: { (action) in
                        self.showPinView(handler: handler)
                    })
                }
                return
            }
            handler(confirmPin)
        })
    }
    
    func convertDate(date: Date) -> String {
        let formatter = DateFormatter()
        formatter.dateFormat = "dd-MM-yyyy"
        let str = formatter.string(from: date)
        return str
    }
}

extension UIDevice {
    
    var isPhone: Bool { return self.userInterfaceIdiom == .phone }
    var isPad: Bool { return self.userInterfaceIdiom == .pad }
    
}

extension UIViewController {
    
    func displayAlert(titleText: String, messageText: String) {
        
        let okButton = UIAlertAction.init(title: "OK", style: UIAlertAction.Style.default, handler: nil)
        
        let alert = UIAlertController.init(title: titleText, message: messageText, preferredStyle: UIAlertController.Style.alert)
        alert.addAction(okButton)
        
        if UIDevice.current.isPad {
            AppDelegate.shared.window?.rootViewController?.present(alert, animated: true, completion: nil)
        } else {
            self.present(alert, animated: true, completion: nil)
        }
        
    }
}
