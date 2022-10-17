//
//  WelcomeViewController
//  DigiPass
//
//  Created by sravan on 20/02/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit
import LocalAuthentication
import FirebaseAnalytics
import AVFoundation

class WelcomeViewController: BaseViewController {

    @IBOutlet weak var scanView: UIView!
    @IBOutlet weak var otpButtonView: CircularProgressBar!
    @IBOutlet weak var otpButton: UIButton!
    @IBOutlet weak var scanDesc: UILabel!
    @IBOutlet weak var centerYCons: NSLayoutConstraint!
    @IBOutlet weak var descLbl: UILabel!
    @IBOutlet weak var thakLbl: UILabel!
    @IBOutlet weak var welcomeLbl: UILabel!
    @IBOutlet weak var hyperLinkBtn: UIButton!
    
    var newBiometricData: Data?
    var progressBar: CircularProgressBar!
    let activation = DigiPassActivation()
    let config = MCKConfiguration()
    var loadingView: FSnapChatLoadingView!

    var authType: ViewControllerType = ViewControllerType(rawValue: 0)! {
        didSet {
            hideOTPView()
        }
    }
    
    
    // MARK:- view life cycle methods
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        setup()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    override func viewWillLayoutSubviews() {
        super.viewWillLayoutSubviews()
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self, name: Notification.Name("UpdateUserName"), object: nil)
    }
    
    // MARK:- custom methods
    override func setup() {
        super.setup()
        fetchServerTime()
        scanView.backgroundColor = UIColor.scanViewColor()
        scanView.layer.cornerRadius = scanView.frame.width / 2
        scanView.layer.masksToBounds = true
        activation.delegate = self

        config.numberOfDigits = 6
        config.shouldShakeOnReset = true
        
        loadingView = FSnapChatLoadingView()
        checkIsUser()
        
        NotificationCenter.default.addObserver(self, selector: #selector(updateUser), name: Notification.Name("UpdateUserName"), object: nil)
        
    }
    
    @objc func updateUser() {
        let user = DigiPassSharedData.sharedInstance().currentUser()
        welcomeLbl.text = "Welcome, \(user["userName"] as? String ?? "")"
        
    }
    
    func fetchServerTime() {
        NetworkManager.shared.getServerTime { (response, error) in
            if let model = response {
                if let result = model.resultCodes?.returnCode, result == 0 {
                    if let time = model.result?.serverTime {
                        do {
                            let timeServer = DIGIPassClientSDKWrapper .computeClientServerTimeShift(fromServerTime: time)
                            try DigiPassSharedData.sharedInstance().secureStorage.putString(forValue: "\(timeServer)", forKey: UserCodingKeys.serverTime.rawValue)

                        }catch {
                            
                        }
                    }
                }
            }
        }
    }
    
    fileprivate func checkIsUser() {
        var isUser = false
        let userDict = DigiPassSharedData.sharedInstance().currentUser()
        if  let userName = userDict["userName"] as? String {
            isUser = true
            welcomeLbl.text = "Welcome, \(userName)"
            getRootViewController()?.topView.menuButton.isHidden = false
            
            if let isPinSelected = userDict["isPinSelected"] as? String, isPinSelected == "biometric"  {
                authType = .fingerScan
            }
        }else {
            getRootViewController()?.topView.menuButton.isHidden = true
            isUser = false
            welcomeLbl.text = "Welcome"
        }
        
        scanView.isHidden = isUser ? true : false
        thakLbl.isHidden = isUser ? true : false
        descLbl.isHidden = isUser ? true : false
//        scanDesc.text = isUser ? "Click above button generate OTP" : "Get started and click on button bellow to scan a cronto code and start your activation"
        scanDesc.text = isUser ? "Click above button generate OTP" : "Please login into the activation website and click on above button to scan a cronto image and start your activation"

        otpButtonView.isHidden = isUser ? false : true
        hyperLinkBtn.isHidden = isUser ? true : false
    }
    
    func presentQRCodeReader() {
        DispatchQueue.main.async {
            do {
                let qrVC = try QRCodeScannerSDK.getQRCodeScannerSDKViewController(delegate: self,
                                                                                  vibrate: true,
                                                                                  codeType: .all,
                                                                                  image: UIImage(named: "QRScan_close"),
                                                                                  scannerOverlay: true,
                                                                                  scannerOverlayColor: .clear)
                //            let qrVC = QRCodeScannerSDKViewController(delegate: self, vibrate: true, codeType:  1 +  2, use: UIImage(named: "QRScan_close.png"), scannerOverlay: true, scannerOverlayColor: .clear)
                self.present(qrVC, animated: true, completion: nil)
            } catch let e {
                print(e)
            }
        }
    }
    func showScanCamers() {
        if AVCaptureDevice.authorizationStatus(for: .video) ==  .authorized {
            self.presentQRCodeReader()
        } else {
            AVCaptureDevice.requestAccess(for: .video, completionHandler: { (granted: Bool) in
                if granted {
                    self.presentQRCodeReader()
                } else {
                    let controller = UIAlertController(title: "Alert", message: "Camera access required for scanning QR code", preferredStyle: .alert)
                    controller.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
                    controller.addAction(UIAlertAction(title: "Settings", style: .default, handler: { (action) in
                        let url = URL(string: UIApplication.openSettingsURLString)
                        if (UIApplication.shared.canOpenURL(url!)) {
                            if #available(iOS 10.0, *) {
                                UIApplication.shared.open(url!, options: [:], completionHandler: nil)
                            } else {
                                // Fallback on earlier versions
                            }
                        }
                    }))
                    self.present(controller, animated: true, completion: nil)
                }
            })
        }
    }
    
    @IBAction func scanTapped(_ sender: Any) {

        LocationAuthentication.sharedMySingleton().checkLocationServices { (allow) in
            if allow {
                LocationAuthentication.sharedMySingleton().checkCurrentLocation { (allow) in
                    if !allow {
                        DigiPassUtilities.showAlertOnRootVC(title: "Alert", message: "You are not in an authorized zone.", cancel: "Ok")
                    }else {
                        self.showScanCamers()
                    }
                }
            }else {
                let alert = UIAlertController(title: "Location Services are not enabled", message: nil, preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
                alert.addAction(UIAlertAction(title: "Settings", style: .default, handler: { action in
                    let url = URL(string: UIApplication.openSettingsURLString)
                    if let url = url {
                        if UIApplication.shared.canOpenURL(url) {
                            UIApplication.shared.open(url, options: [:], completionHandler: nil)
                        }
                    }
                }))
                self.present(alert, animated: true)
            }
        }
    }
    
    func deactivate() {
        hideOTPView()
        let user = DigiPassSharedData.sharedInstance().currentUser()
        DigiPassSharedData.sharedInstance().deleteUser(user)
        let users = UserDefaults.standard.object(forKey: "users") as? [[String: Any]]
        if let results = users, let u = results.first {
            UserDefaults.standard.set(u, forKey: "currentUser")
        }
        checkIsUser()
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
    
    @IBAction func generateOtp(_ sender: Any) {
        
        let otpGenerator: (String) -> Void = { (pin) in
            DispatchQueue.main.async {
                self.loadingView.show(view: self.parent?.view)
            }
            let response = DIGIPassClientSDKWrapper.validatePassword(pin)
            if let status =  response["status"] as? Bool, status {
                self.activation.generatePin(entered: pin) { (pin) in
                    self.loadingView.hide()
                    let finalStr = pin.replacingOccurrences(of: "\0", with: "", options: NSString.CompareOptions.literal, range:nil)
                    self.showOTPView(otp: finalStr)
                    self.storeNewBiometricData()
                }
                if pin.count > 0 {
                    MCKPinController.dismiss(completion: {
                                       MCKPinController.reset()
                                   })
                }
            }else {
                DispatchQueue.main.async {
                    if pin.count > 0 {
                        MCKPinController.dismiss(completion: {
                            MCKPinController.reset()
                             self.loadingView.hide()
                        })
                    }
                    DigiPassUtilities.showAlert(title: response["error"] as? String, message: nil, cancel: "Ok", viewController: self)
                }
            }
       }
        
        hideOTPView()
        if authType == .pin {
            showPinScreen { (pin) in
                if let p = pin {
                    otpGenerator(p)
                }
            }
        }else if authType == .face || authType == .fingerScan {
            authenticate(reason: "Check Biometric Status") { (status, reason) in
                if status {
                    DispatchQueue.main.async {
                        let controller = UIAlertController(title: "Alert", message: reason ?? "", preferredStyle: .alert)
                        controller.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
                        controller.addAction(UIAlertAction(title: "Ok", style: .default, handler: { (action) in
                            DigiPassSharedData.sharedInstance().updatePinSelection(forCurrentUser: "pin")
                            self.authType = .pin
                            self.showPinScreen { (pin) in
                                if let p = pin {
                                    otpGenerator(p)
                                }
                            }
                        }))
                        self.present(controller, animated: true, completion: nil)
                    }
                }else {
                    otpGenerator("")
                }
            }
        }
    }
    
    func hideOTPView() {
        
        if progressBar != nil {
            if progressBar.timer.isValid { progressBar.timer.invalidate() }
            progressBar.removeFromSuperview()
            progressBar = nil
        }
        //getRootViewController()?.topView.menuButton.isHidden = false
        otpButtonView.isHidden = false
    }
    
    func getRootViewController() -> MainMenuViewController? {
        return self.parent as? MainMenuViewController
    }
    
    private func showOTPView(otp: String) {
        otpButtonView.isHidden = true
        //getRootViewController()?.topView.menuButton.isHidden = true
        
        progressBar = CircularProgressBar(with: otp)
        progressBar.delegate = self
        progressBar.translatesAutoresizingMaskIntoConstraints = false
        self.view.addSubview(progressBar)
        
        let width = view.bounds.width / 2
        progressBar.centerXAnchor.constraint(equalTo: view.centerXAnchor, constant: 0).isActive = true
        progressBar.centerYAnchor.constraint(equalTo: view.centerYAnchor, constant: -60).isActive = true
        progressBar.widthAnchor.constraint(equalToConstant: width).isActive = true
        progressBar.heightAnchor.constraint(equalToConstant: width).isActive = true
        
        progressBar.labelSize = 20
        progressBar.safePercent = 100
        progressBar.setProgress(to: 1, withAnimation: true)
        
    }
    
    func startActivation() {
        self.loadingView.show(view: self.parent?.view)

        DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
            self.activation.startActivateUser(activate: .withRegistrationIDOne)
        }
    }

}

extension WelcomeViewController: CircularProgressBarDelegate {
    func didCompleteTimeOut() {
        hideOTPView()
    }
}

extension WelcomeViewController: DigiPassActivationDelegate {
    func confirmPin(pin: String, handler: @escaping ((String?) -> Void)) {
        DispatchQueue.main.async {
            self.config.completion = { pin in
                handler(pin)
            }
            self.config.titleText = "Please enter confirm pin"
            MCKPinController.present(with: self.config, in: self )
        }
    }
    
    func didFailedActivationProcess() {
        DispatchQueue.main.async {
            self.loadingView.hide()
        }
    }
    
    private func handleWeakPassword(handler: @escaping ((String?) -> Void)) {
        let controller = UIAlertController(title: "Weak password", message: "The Pin is not strong enough. Please retry.", preferredStyle: .alert)
        controller.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: { (action) in
            self.didFailedActivationProcess()
        }))
        controller.addAction(UIAlertAction(title: "Retry", style: .default, handler: { (action) in
            self.showPinScreen(handler: handler)
        }))
        present(controller, animated: true, completion: nil)
    }
    
    func showPinScreen(handler: @escaping ((String?) -> Void)) {
        DispatchQueue.main.async {
            self.config.completion = { pin in
                
                let isWeakPassword = DIGIPassClientSDKWrapper.checkWeakPassword(pin)
                if !isWeakPassword {
                    handler(pin)
                }else {
                    MCKPinController.dismiss {
                        MCKPinController.reset()
                        self.handleWeakPassword(handler: handler)
                    }
                }
            }
            self.config.titleText = "Please Enter Pin"
            MCKPinController.present(with: self.config, in: self)
        }
    }
    
    func didCompleteActivateProcess() {
        authType = .pin
        self.loadingView.hide()
        checkIsUser()
        if let notificationId = DigiPassSingleTon.shared.userIno.vascoDeviceIdentifier {
            NetworkManager.shared.updateNotificationID(notificationToken: notificationId) { (response, error) in
                if let model = response {
                    if let result = model.resultCodes?.returnCode, result == 0 {

                    }
                }
            }
        }
    }
}

extension WelcomeViewController: ScannerDelegate {
    func qrCodeScannerSDKController(_ controller: UIViewController, didScan result: String, codeType: CodeType) {
        
        controller.dismiss(animated: true) {
            
            if let data = Data(fromHexEncodedString: result) {
                if let tempStr = String.init(data:data, encoding: String.Encoding.utf8) {
                    let tempArr = tempStr.components(separatedBy: ",")
                    if let user = tempArr.first {
                        let registrationId1 = tempArr[1]
                        let password1 = tempArr[2]
                        let registrationId2 = tempArr[3]
                        let password2 = tempArr[4]
                        
                        do {
                            /*let number = Int.random(in: 0 ..< 10)
                            let fingerPrintName = "\(number)"
                            try DigiPassSharedData.sharedInstance().secureCache = SecureStorageSDKWrapper.init(fileName: "DigiPassCache", useFingerPrint: fingerPrintName, andIterationNumber: 8001)*/
                            
                            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: user, forKey: UserCodingKeys.user.rawValue)
                            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: registrationId1, forKey: UserCodingKeys.registrationID1.rawValue)
                            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: password1, forKey: UserCodingKeys.activationPwd1.rawValue)
                            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: registrationId2, forKey: UserCodingKeys.registrationID2.rawValue)
                            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: password2, forKey: UserCodingKeys.activationPwd2.rawValue)

                        }catch let error {
                            Analytics.logEvent("qrCodeScannerSDKController", parameters: [
                                "error": error.localizedDescription as NSObject,
                                ])
                        }
                        self.startActivation()
                    }
                }
            }
        }
    }
    
    func qrCodeScannerSDKControllerDidCancel(_ controller: UIViewController) {
        controller.dismiss(animated: true, completion: nil)
    }
    
    func qrCodeScannerSDKController(_ controller: UIViewController, didReceive error: ScannerError) {
        
    }
}

extension Data {
    
    init?(fromHexEncodedString string: String) {
        
        // Convert 0 ... 9, a ... f, A ...F to their decimal value,
        // return nil for all other input characters
        func decodeNibble(u: UInt16) -> UInt8? {
            switch(u) {
            case 0x30 ... 0x39:
                return UInt8(u - 0x30)
            case 0x41 ... 0x46:
                return UInt8(u - 0x41 + 10)
            case 0x61 ... 0x66:
                return UInt8(u - 0x61 + 10)
            default:
                return nil
            }
        }
        
        self.init(capacity: string.utf16.count/2)
        var even = true
        var byte: UInt8 = 0
        for c in string.utf16 {
            guard let val = decodeNibble(u: c) else { return nil }
            if even {
                byte = val << 4
            } else {
                byte += val
                self.append(byte)
            }
            even = !even
        }
        guard even else { return nil }
    }
}
