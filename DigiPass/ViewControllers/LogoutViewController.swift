//
//  LogoutViewController.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/28/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit
import LocalAuthentication
import FirebaseAnalytics

class LogoutViewController: BaseViewController {

    @IBOutlet weak var yesButton: UIButton!
    @IBOutlet weak var noButton: UIButton!
    @IBOutlet weak var logoutView: UIView!
    @IBOutlet weak var msgLbl: UILabel!
    
    var channelMessage: SecureChannelMessageWrapper!
    var challengeKey: String!
    var decryptedMessage: String!
    let config = MCKConfiguration()
    var loadingView: FSnapChatLoadingView!
    var newBiometricData: Data?
    private var timer: Timer?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        setup()
    }

    // MARK:- custom methods
    override func setup() {
        super.setup()
        logoutView.layer.borderColor = UIColor.lighBlueColor().cgColor
        logoutView.layer.borderWidth = 2.5
        logoutView.layer.cornerRadius = logoutView.frame.width / 2
        logoutView.layer.masksToBounds = true
        loadingView = FSnapChatLoadingView()

        yesButton.backgroundColor = UIColor.buttonBgColor2()
        noButton.backgroundColor = UIColor.buttonBgColor1()
        
        config.numberOfDigits = 6
        config.shouldShakeOnReset = true
    }
    
    // MARK:- Custom methods
    
    func showPinScreen(handler: @escaping ((String?) -> Void)) {
        DispatchQueue.main.async {
            self.config.completion = { pin in
                handler(pin)
            }
            MCKPinController.present(with: self.config, in: self)
        }
    }
    var handler: ((String?) -> Void)?
    
    func validateBiometric(handler: @escaping ((String?) -> Void)) {
        self.handler = handler
        let parameters = AuthenticationParameters(reason: "Biometric dialog description text",
                                                  methods: .all,
                                                  fallbackMechanismText: nil)
        
        do {
            try BiometricSensorSDK.startBiometricAuthentication(parameters: parameters, delegate: self)
            
            // After 30s the user authentication is stopped
            timer?.invalidate()
            timer = Timer.scheduledTimer(timeInterval: 30.0, target: self, selector: #selector(stopUserAuthentication), userInfo: nil, repeats: false)
        } catch let error as BiometricError {
            timer?.invalidate()
            DigiPassUtilities.showAlert(title: "BiometricError - code: \(error.errorCode), cause: \(String(describing: error.failureReason))", message: nil, cancel: "Ok", viewController: self)
        } catch {
            timer?.invalidate()
            assertionFailure("The error thrown should be of type BiometricError!")
        }
        
        /*let params = BiometricSensorSDKParams()
        params.onBiometricAuthenticationSucceededWithParams = { (params) in
            handler("")
        }
        params.onBiometricAuthenticationFailed = { (params) in
            handler(nil)
            DispatchQueue.main.async {
                DigiPassUtilities.showAlert(title: "Failed Biometric Authentication", message: nil, cancel: "Ok", viewController: self)
            }
        }
        params.onBiometricAuthenticationError = { (params) in
            handler(nil)
            DispatchQueue.main.async {
                DigiPassUtilities.showAlert(title: "onBiometricAuthenticationError", message: nil, cancel: "Ok", viewController: self)
            }
        }
        params.onBiometricAuthenticationCancelled = { () in
            handler(nil)
            DispatchQueue.main.async {
                DigiPassUtilities.showAlert(title: "onBiometricAuthenticationCancelled", message: nil, cancel: "Ok", viewController: self)
            }
        }
        params.onBiometricAuthenticationFallbackCalled = { () in
            handler(nil)
            DispatchQueue.main.async {
                DigiPassUtilities.showAlert(title: "onBiometricAuthenticationFallbackCalled", message: nil, cancel: "Ok", viewController: self)
            }
        }
        params.biometricAuthenticationMethod = BiometricAuthentificationMethodAny
        params.operationDescription = "description"
        
        BiometricSensorSDK.startUserAuthentication(using: params)*/
    }
    
    @objc func stopUserAuthentication() {
        BiometricSensorSDK.stopBiometricAuthentication()
    }
    
    func acceptLogOnRequest(pin: String,  message: SecureChannelMessage) {
        
        let generateSignatureModel = DIGIPassClientSDKWrapper.generateSignature(fromPassword: pin, isActivateProcess: false)
        // let responseMsg = String(data: generateSignatureModel.responseData, encoding: .utf8)?.replacingOccurrences(of: "\0", with: "")
        
        let userID = decryptedMessage.components(separatedBy: ";")[4]
        
        var requestDict: [String: String] = [:]
        if let signature = String(data: generateSignatureModel.responseData, encoding: .utf8)?.replacingOccurrences(of: "\0", with: "") {
            requestDict["signature"] = signature
        }
        if let domain = decryptedMessage.components(separatedBy: ";").last {
            requestDict["domain"] = domain
        }
        requestDict["challengeKey"] = challengeKey
        requestDict["userID"] = userID

        DispatchQueue.main.async {
            self.loadingView.show(view: self.parent?.view)
        }
        
        NetworkManager.shared.authenticateUserLoginRequest(requestBody: requestDict as [String : Any]) { (response, error) in
            guard let json = response else {
                DispatchQueue.main.async {
                    self.loadingView.hide()
                }
                return
            }
            
            if let resultCode = json["resultCodes"] as? [String: Any] {
                if let returnCode = resultCode["returnCode"] as? Int, returnCode == 0 {
                    DispatchQueue.main.async {
                        self.loadingView.hide()
                        self.navigateToDashboard()
                        if let window = UIApplication.shared.keyWindow,
                            let rootVC = window.rootViewController as? UINavigationController,
                            let topVC = rootVC.topViewController {
                            DigiPassUtilities.showAlert(title: "Success", message: "Your request has been approved ", cancel: "Ok", viewController: topVC)
                        }
                    }
                }else {
                    DispatchQueue.main.async {
                        self.loadingView.hide()
                    }
                }
            }
        }
    }

    func cancelAuthenticationRequest() {
        
        // TODO TEST THE CANCELLATION
            let rawData = DIGIPassClientSDKWrapper.string(toHex: challengeKey)

            let messageModel = DIGIPassClientSDKWrapper.generateSecureChannelINotificationToken(rawData)
            let sequenceNumber = DIGIPassClientSDKWrapper.getDigiPassPropertyInt(vds_int32(PROPERTY_SEQUENCE_NUMBER), cryptoIndex: vds_int32(CRYPTO_APPLICATION_INDEX_APP_1))
            let serialNumber = messageModel.serialNumber
            let finalStr = "\(serialNumber)-\(sequenceNumber)"

        // TODO : CHECK IF THE CHALLENGE KEY SHOULD NOT BE CHALLENGE KEY
            let requestBody = ["challengeKey": messageModel.rawData,
                               "serialNumber": finalStr]
            
            DispatchQueue.main.async {
                self.loadingView.show(view: self.parent?.view)
            }

            NetworkManager.shared.cancelUserLoginRequest(requestBody: requestBody as [String : Any]) { (response, error) in
                
                guard let json = response else {
                    DispatchQueue.main.async {
                        self.loadingView.hide()
                    }
                    return
                }
                
                if let resultCode = json["resultCodes"] as? [String: Any] {
                    if let returnCode = resultCode["returnCode"] as? Int, returnCode == 0 {
                        DispatchQueue.main.async {
                            self.loadingView.hide()
                            self.navigateToDashboard()
                        }
                    }else {
                        DispatchQueue.main.async {
                            self.loadingView.hide()
                        }
                    }
                }
            }
    }
    
    func validate(on isAccept: Bool) {

        let actionTapped: (String,Bool) -> Void = { (pin, isAccep) in
             if isAccept {
                 self.acceptLogOnRequest(pin: pin, message: self.channelMessage.message)
             }else {
                 self.cancelAuthenticationRequest()
             }
        }
        
        let user = DigiPassSharedData.sharedInstance().currentUser()
        if let isPinSelected = user["isPinSelected"] as? String,
            isPinSelected == "pin" {
            showPinScreen { (pin) in
                MCKPinController.dismiss(completion: {
                    MCKPinController.reset()
                    guard let p = pin else {
                        return
                    }
                    actionTapped(p, isAccept)
                })
            }
        }else {
            authenticate(reason: "Check Biometric Status") { (status, reason) in
                if status {
                    DispatchQueue.main.async {
                        let controller = UIAlertController(title: "Alert", message: reason ?? "", preferredStyle: .alert)
                        controller.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
                        controller.addAction(UIAlertAction(title: "Ok", style: .default, handler: { (action) in
                            DigiPassSharedData.sharedInstance().updatePinSelection(forCurrentUser: "pin")
                            self.showPinScreen { (pin) in
                                if let p = pin {
                                    actionTapped(p, isAccept)
                                }
                            }
                        }))
                        self.present(controller, animated: true, completion: nil)
                    }
                }else {
                    actionTapped("", isAccept)
                }
            }
        }
        
    }
    
    func navigateToDashboard() {
        if let parentVC = self.parent as? MainMenuViewController {
            parentVC.addViewController(viewController: parentVC.welcomeVC)
        }
    }
    
    @IBAction func yesTapped(_ sender: Any) {
        validate(on: true)
    }
    
    @IBAction func noTapped(_ sender: Any) {
        validate(on: false)
    }
    
    
    
    func authenticate(context: LAContext = .init(), reason: String, handler: @escaping (_ status: Bool, _ reason: String?) -> Void) {
        let policy = LAPolicy.deviceOwnerAuthenticationWithBiometrics
        var error: NSError?
        guard context.canEvaluatePolicy(policy, error: &error) else {
            handler(true, error?.localizedDescription)
            return
        }
        context.evaluatePolicy(policy, localizedReason: reason) { (success, error) in
            guard success else {
                handler(true, error?.localizedDescription)
                return
            }
            do {
                let currentBiometric = try DigiPassSharedData.sharedInstance().secureStorage.getBytesForKey(UserCodingKeys.systemBiometric.rawValue)
                let newFingerPrintData = context.evaluatedPolicyDomainState
                guard currentBiometric == newFingerPrintData else {
                    // finger print is changed
                    self.newBiometricData = newFingerPrintData
                    handler(true, "A new fingerprint was added to this device, so your PIN is required.")
                    return
                }
                self.newBiometricData = newFingerPrintData
                self.storeNewBiometricData()
                handler(false, nil)
            }catch let error {
                let newFingerPrintData = context.evaluatedPolicyDomainState
                self.newBiometricData = newFingerPrintData
                self.storeNewBiometricData()
                handler(false, nil)
                Analytics.logEvent("authenticate", parameters: [
                    "error": error.localizedDescription as NSObject,
                    ])
            }
        }
    }
    
    private func storeNewBiometricData() {
        if let data = self.newBiometricData {
            do {
                try DigiPassSharedData.sharedInstance().secureStorage.putBytes(forBytes: data, forKey: UserCodingKeys.systemBiometric.rawValue)
                DigiPassSharedData.sharedInstance().saveSecureStorage()
                self.newBiometricData = nil
            }catch let error {
                Analytics.logEvent("storeNewBiometricData", parameters: [
                    "error": error.localizedDescription as NSObject,
                    ])
            }
           
        }
    }
}

extension LogoutViewController: AuthenticationDelegate {
    private func updateLabel(withText text: String) {
        DispatchQueue.main.async {
//            self.biometricVerifiedLabel.text = text
        }
    }
    
    func biometricAuthenticationDidSucceed(parameters: SuccessParameters) {
        timer?.invalidate()
        self.handler?("")
    }
    
    func biometricAuthenticationDidFail(for method: BiometricAuthenticationMethod) {
        timer?.invalidate()
        DispatchQueue.main.async {
            DigiPassUtilities.showAlert(title: "Failed Biometric Authentication", message: nil, cancel: "Ok", viewController: self)
        }
    }
    
    func biometricAuthenticationDidCallFallbackMethod() {
        timer?.invalidate()
        updateLabel(withText: "Use fallback")
    }
    
    func biometricAuthenticationDidCancel() {
        timer?.invalidate()
        DigiPassUtilities.showAlert(title: "onBiometricAuthenticationCancelled", message: nil, cancel: "Ok", viewController: self)
    }
    
    func biometricAuthenticationDidReceive(error: BiometricError) {
        timer?.invalidate()
        let errorText = [
            "errorCode: \(error.errorCode)",
            error.errorDescription,
            error.failureReason,
            error.recoverySuggestion
        ]
        .compactMap { ($0?.isEmpty ?? true) ? nil : $0 }
        .joined(separator: "\n")
        updateLabel(withText: errorText)
    }
}
