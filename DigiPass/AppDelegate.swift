//
//  AppDelegate.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 10/9/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit
import MSSNotificationClient
import FirebaseCore
import FirebaseMessaging
//import Firebase

//Host APIKey  domain

//com.adpolice.mfa
@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate{
    var window: UIWindow?
    
    let NotificationDataUpdated = "NotificationDataUpdated"
    let NotificationReceived = "NotificationReceived"
//    var reachability: Reachability!
    var appRouter: AppRouter!
    var notificationFromBackground = false
    var errorText: String?
    var notificationIdentifierText: String?
    var oneSpanNotification: OneSpanNotification?
    static let shared: AppDelegate = UIApplication.shared.delegate as! AppDelegate
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // We want subscribe to every availlable aspect of the notification
        appRouter = AppRouter(window: window!)
        let notificationTypes: NotificationType = [.badge, .sound, .alert]
        FirebaseApp.configure()
        do {
            try NotificationClientSDK.registerNotificationServices(withType: notificationTypes)
        } catch let error {
            handleNotificationSDKError(error: error)
        }
        Messaging.messaging().isAutoInitEnabled = true
        Messaging.messaging().delegate = self
        return true
    }
    
    func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
        do {
            // Create the OneSpan Notification Identifier from the token provided by the system
            Messaging.messaging().apnsToken = deviceToken
            notificationIdentifierText = try NotificationClientSDK.oneSpanNotificationIdentifier(for: deviceToken)
            print("OneSpan notification ID: \(notificationIdentifierText ?? "nil")")
            DigiPassSingleTon.shared.userIno.vascoDeviceIdentifier = notificationIdentifierText
            UserDefaults.standard.set(notificationIdentifierText, forKey: "NotificationStringObj")
            print("Vasco notification ID: \(notificationIdentifierText)")
            NetworkManager.shared.updateNotificationID(notificationToken: notificationIdentifierText!) { (response, error) in
                if let model = response {
                    if let result = model.resultCodes?.returnCode, result == 0 {

                    }
                }
            }
            notify()
            let token = deviceToken.map { String(format: "%02.2hhx", $0) }.joined()
               print(token)        
        } catch let error {
            notificationIdentifierText = nil
            handleNotificationSDKError(error: error)
        }
    }
    
    func application(_ application: UIApplication, didFailToRegisterForRemoteNotificationsWithError error: Error) {
        print("Error during registration. Error: \(error.localizedDescription)")
        errorText = error.localizedDescription
        notify()
    }
    
    func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable: Any], fetchCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
        print("didReceiveRemoteNotification userInfo: [AnyHashable : Any], fetchCompletionHandler: \(userInfo.description)")
        
        if application.applicationState == .inactive || application.applicationState == .background {
            // opened from a push notification when the app was on background
            notificationFromBackground = true
        }
        
        // Check that the notification is a correct OneSpan notification
        if NotificationClientSDK.isOneSpanNotification(userInfo) {
            manageNotificationWithApplication(application, userInfo: userInfo)
        }
        
        completionHandler(.newData)
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }

    private func notify() {
        NotificationCenter.default.post(name:Notification.Name(self.NotificationDataUpdated), object: nil)
    }
    
    private func notifyNotificationReceived() {
        NotificationCenter.default.post(name: Notification.Name(self.NotificationReceived), object: nil)
    }
    
    /**
     * Parse an incomming OneSpan Notification and update the text data accordingly so that the attached
     * ViewController can display them/
     */
    
    /*
     private func manageNotificationWithApplication(_ application: UIApplication, userInfo: [AnyHashable : Any])
 {
         do {
             // Parse the provided NSDictionary and retrieve the content of the notification as a String
             notificationContentText = try NotificationSDKClientWrapper.parseVASCONotification(userInfo)

             try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: notificationContentText, forKey: UserCodingKeys.activatedMessage.rawValue)

             // SENSITIVE TEMPORARY INFORMATION -> SECURE CACHE
             let messsage = DIGIPassClientSDKWrapper.parseSecureChannelMessage(notificationContentText)

             let decryptedMsg = DIGIPassClientSDKWrapper.decryptSecureChannelMessageBody()

 //            if  let tempArray = decryptedMsg.components(separatedBy: ";")  {
             let tempArray = decryptedMsg.components(separatedBy: ";")

             let challengeKey = tempArray.last!
                 NetworkManager.shared.preparedSecureChannel(message: messsage, challengeKey: challengeKey) { (response, error) in
                     if let model = response {
                         if let result = model.resultCodes?.returnCode, result == 0 {
                             if let activateMsg = model.result?.activationMessage {
                                 do {
                                     try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: activateMsg, forKey: UserCodingKeys.activatedMessage.rawValue)
                                     let messsage1 = DIGIPassClientSDKWrapper.parseSecureChannelMessage(activateMsg)
                                     let decryptedMsg1 = DIGIPassClientSDKWrapper.decryptSecureChannelMessageBody()
                                     self.navigateToLogOnRequestPage(channelMessage: messsage1, decryptedMsg: decryptedMsg1, challengeKey: challengeKey)
                                 }catch { }
                             }
                         }
                     }
                 }
 //            }


             // Parse the provided NSDictionary and retrieve the title of the notification as a String
             notificationTitleText = try NotificationSDKClientWrapper.getTitle(userInfo)

             // Parse the provided NSDictionary and retrieve the subject of the notification as a String
             notificationSubjectText = try NotificationSDKClientWrapper.getSubject(userInfo)

             // Parse the provided NSDictionary and retrieve the badge value of the notification
             // Set the badge value to 0 in order to remove all notifications.
             // It is required since, in iOS 7, the remote notifications are not automatically removed when opened.
             UIApplication.shared.applicationIconBadgeNumber = 0

             ////NSLog("Vasco notification: Title : %@, Subject : %@, content: %@, badge: %d", notificationTitleText, notificationSubjectText, notificationContentText, badgeValue)
         }
         catch let error as NSError{
             errorText = getErrorMessageFromCode(Int32(error.code))
         }
         notifyNotificationReceived()
     }
 }
     */
    func navigateToLogOnRequestPage(channelMessage: SecureChannelMessageWrapper,
                                    decryptedMsg: String,
                                    challengeKey: String) {
        DispatchQueue.main.async {
            if let rootViewController = self.appRouter.window.rootViewController as? SideMenuNavigationController {
                let mainVC = rootViewController.mainMenuVC
                mainVC?.navigateToLogOnRequestPage(channelMessage: channelMessage, decryptedMsg: decryptedMsg, challengeKey: challengeKey)
            }
        }
    }
    private func manageNotificationWithApplication(_ application: UIApplication, userInfo: [AnyHashable: Any]) {
        UIApplication.shared.applicationIconBadgeNumber = 0


        do{
            oneSpanNotification = NotificationClientSDK.oneSpanNotification(from: userInfo)
            print(userInfo["vascoPayload"])
            
            let notificationContentText = userInfo["vascoPayload"] as! String
            
            print(notificationContentText)
            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: notificationContentText, forKey: UserCodingKeys.activatedMessage.rawValue)
    
            
            // SENSITIVE TEMPORARY INFORMATION -> SECURE CACHE
            let messsage = DIGIPassClientSDKWrapper.parseSecureChannelMessage(notificationContentText)
            let decryptedMsg = DIGIPassClientSDKWrapper.decryptSecureChannelMessageBody()
            
            let tempArray = decryptedMsg.components(separatedBy: ";")

            let challengeKey = tempArray.last!
                NetworkManager.shared.preparedSecureChannel(message: messsage, challengeKey: challengeKey) { (response, error) in
                    if let model = response {
                        if let result = model.resultCodes?.returnCode, result == 0 {
                            if let activateMsg = model.result?.activationMessage {
                                do {
                                    try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: activateMsg, forKey: UserCodingKeys.activatedMessage.rawValue)
                                    let messsage1 = DIGIPassClientSDKWrapper.parseSecureChannelMessage(activateMsg)
                                    let decryptedMsg1 = DIGIPassClientSDKWrapper.decryptSecureChannelMessageBody()
                                    self.navigateToLogOnRequestPage(channelMessage: messsage1, decryptedMsg: decryptedMsg1, challengeKey: challengeKey)
                                }catch { }
                            }
                        }
                    }
                }
            
            if oneSpanNotification != nil {
                notifyNotificationReceived()
            }
        }
        catch{
            print("error Notifcation SDK")
        }
    }

    private func handleNotificationSDKError(error: Error) {
        if let notificationError = error as? NotificationError {
            errorText = [
                "errorCode: \(notificationError.errorCode)",
                notificationError.errorDescription,
                notificationError.failureReason,
                notificationError.recoverySuggestion
            ]
            .compactMap { $0 }
            .filter { !$0.isEmpty }
            .joined(separator: "\n")
        } else {
            errorText = error.localizedDescription
        }
        
        notify()
    }
}

//{
//
//    var window: UIWindow?
//    var reachability: Reachability!
//
//
//    var notificationContentText = ""
//    var notificationTitleText = ""
//    var notificationSubjectText = ""
//
//    var appRouter: AppRouter!
//
//    var notificationFromBackground = false
//    var errorText: String?
//    var notificationIdentifierText: String?
//    var oneSpanNotification: OneSpanNotification?
//
//
//
//    static let shared: AppDelegate = UIApplication.shared.delegate as! AppDelegate
//
//    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
//        // Override point for customization after application launch.
//
//        window = UIWindow(frame: UIScreen.main.bounds)
//        appRouter = AppRouter(window: window!)
//        registerNotifications()
//
////        FirebaseApp.configure()
//        return true
//    }
//
//    func applicationWillResignActive(_ application: UIApplication) {
//        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
//        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
//    }
//
//    func applicationDidEnterBackground(_ application: UIApplication) {
//        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
//        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
//    }
//
//    func applicationWillEnterForeground(_ application: UIApplication) {
//        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
//    }
//
//    func applicationDidBecomeActive(_ application: UIApplication) {
//        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
//    }
//
//    func applicationWillTerminate(_ application: UIApplication) {
//        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
//    }
//
//
//    func checkConnectivity() {
//        reachability = Reachability(hostName: "www.google.com")
//
//    }
//}
//
//// MARK:- NotificationDelegate methods
//
//extension AppDelegate {
//
//    func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
////        let updateNotification: () -> Void = {
////
////        }
//        do {
//            // Create the VASCO Notification Identifier from the token provided by the system
//
//            // TODO POSSIBLE OPTIMISATION : STORE CURRENT VASCO ID IN SS AND COMPARE
//            // UPDATE ONLY IF IT CHANGED
//           // let notificationID = try DigiPassSharedData.sharedInstance().secureStorage.getStringForKey(UserCodingKeys.notificationIdentifierText.rawValue)
//            //try DigiPassSharedData.sharedInstance().secureStorage.putString(forValue: notificationIdentifierText, forKey: UserCodingKeys.notificationIdentifierText.rawValue)
//            notificationIdentifierText = try NotificationSDKClientWrapper.getVASCONotificationIdentifer(deviceToken)
//            DigiPassSingleTon.shared.userIno.vascoDeviceIdentifier = notificationIdentifierText
//            ////NSLog("Vasco notification ID: %@", notificationIdentifierText)
//
//            NetworkManager.shared.updateNotificationID(notificationToken: notificationIdentifierText!) { (response, error) in
//                if let model = response {
//                    if let result = model.resultCodes?.returnCode, result == 0 {
//
//                    }
//                }
//            }
//            notify()
//        }
//        catch let error as NSError{
//            errorText = getErrorMessageFromCode(Int32(error.code))
//            notify()
//        }
//
//    }
//
//    func application(_ application: UIApplication, didFailToRegisterForRemoteNotificationsWithError error: Error) {
//        //NSLog("Error during registration. Error: %@", error.localizedDescription)
//        errorText = error.localizedDescription
//        notify()
//    }
//
//    func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any], fetchCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
//
//        if ( application.applicationState == .inactive || application.applicationState == .background  )
//        {
//            //opened from a push notification when the app was on background
//            notificationFromBackground = true;
//        }
//
//        // Check that the notification is a correct VASCO notification
//        do {
//            try NotificationSDKClientWrapper.isVASCONotification(userInfo)
//
//            // Manage the notification
//            manageNotificationWithApplication(application, userInfo: userInfo)
//        }
//        catch {
//            //do nothing
//        }
//
//        completionHandler(.newData)
//    }
//
//}
//
//extension AppDelegate {
//
//    func checkLocation() {
//        LocationAuthentication.sharedMySingleton().checkLocationServices { (allow) in
//            if !allow {
//                let alert = UIAlertController(title: "Location Services are not enabled", message: nil, preferredStyle: .alert)
//                alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
//                alert.addAction(UIAlertAction(title: "Settings", style: .default, handler: { action in
//                    let url = URL(string: UIApplication.openSettingsURLString)
//                    if let url = url {
//                        if UIApplication.shared.canOpenURL(url) {
//                            UIApplication.shared.open(url, options: [:], completionHandler: nil)
//                        }
//                    }
//                }))
//                self.appRouter.window.rootViewController?.present(alert, animated: true)
//            }else {
//                LocationAuthentication.sharedMySingleton().checkCurrentLocation { (allow) in
//                    if !allow {
//                        let alert = UIAlertController(title: "You are not in an authorized zone.", message: nil, preferredStyle: .alert)
//                        alert.addAction(UIAlertAction(title: "Retry", style: .default, handler: { action in
//                            self.checkLocation()
//                        }))
//                        self.appRouter.window.rootViewController?.present(alert, animated: true)
//                    }
//                }
//            }
//        }
//    }
////    sfsfdf
//    func registerNotifications() {
//        let types = NotificationSDKClientNotificationType.badge.rawValue | NotificationSDKClientNotificationType.sound.rawValue | NotificationSDKClientNotificationType.alert.rawValue
//
//        print(types)
//        do {
//            try NotificationSDKClientWrapper.registerNotificationService(withNotificationSettings: NotificationSDKClientNotificationType(rawValue: types))
////            try NotificationSDKClientWrapper.registerNotificationService(withNotificationSettings: NotificationSDKClientNotificationType(rawValue: types))
//        }
//        catch let error as NSError{
//            errorText = getErrorMessageFromCode(Int32(error.code))
//            notify()
//        }
//    }
//
//    private func getErrorMessageFromCode(_ errorCode: Int32) -> String
//    {
//        var errorMessage = ""
//
//        switch (errorCode)
//        {
//        case NotificationSDKClientErrorCodes_INTERNAL_ERROR:
//            errorMessage = "Internal Error"
//            break
//        case NotificationSDKClientErrorCodes_DEVTOKEN_NULL:
//            errorMessage = "The provided devToken is NULL."
//            break
//        case NotificationSDKClientErrorCodes_NETWORK_NOT_AVAILABLE:
//            errorMessage = "The network is not available."
//            break
//        case NotificationSDKClientErrorCodes_VASCO_NOTIFICATION_IDENTIFIER_INCORRECT_FORMAT:
//            errorMessage = "The VASCO notification identifier has an incorrect format."
//            break
//        case NotificationSDKClientErrorCodes_VASCO_NOTIFICATION_IDENTIFIER_INVALID:
//            errorMessage = "The VASCO notification identifier is invalid."
//            break
//        case NotificationSDKClientErrorCodes_VASCO_NOTIFICATION_IDENTIFIER_NULL:
//            errorMessage = "The VASCO notification identifier is NULL."
//            break
//        case NotificationSDKClientErrorCodes_NOTIFICATION_INVALID:
//            errorMessage = "The notification is invalid."
//            break
//        case NotificationSDKClientErrorCodes_NOTIFICATION_NULL:
//            errorMessage = "The notification is NULL."
//            break
//        default:
//            break
//        }
//
//        return errorMessage;
//    }
//
//    private func notify() {
//        NotificationCenter.default.post(name: Notification.Name(NotificationDataUpdated), object: nil)
//    }
//
//    private func notifyNotificationReceived() {
//        NotificationCenter.default.post(name: Notification.Name(NotificationReceived), object: nil)
//    }
//
//    func navigateToLogOnRequestPage(channelMessage: SecureChannelMessageWrapper,
//                                    decryptedMsg: String,
//                                    challengeKey: String) {
//        DispatchQueue.main.async {
//            if let rootViewController = self.appRouter.window.rootViewController as? SideMenuNavigationController {
//                let mainVC = rootViewController.mainMenuVC
//                mainVC?.navigateToLogOnRequestPage(channelMessage: channelMessage, decryptedMsg: decryptedMsg, challengeKey: challengeKey)
//            }
//        }
//    }
//
//    private func manageNotificationWithApplication(_ application: UIApplication, userInfo: [AnyHashable : Any])
//{
//        do {
//            // Parse the provided NSDictionary and retrieve the content of the notification as a String
//            notificationContentText = try NotificationSDKClientWrapper.parseVASCONotification(userInfo)
//
//            try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: notificationContentText, forKey: UserCodingKeys.activatedMessage.rawValue)
//
//            // SENSITIVE TEMPORARY INFORMATION -> SECURE CACHE
//            let messsage = DIGIPassClientSDKWrapper.parseSecureChannelMessage(notificationContentText)
//
//            let decryptedMsg = DIGIPassClientSDKWrapper.decryptSecureChannelMessageBody()
//
////            if  let tempArray = decryptedMsg.components(separatedBy: ";")  {
//            let tempArray = decryptedMsg.components(separatedBy: ";")
//
//            let challengeKey = tempArray.last!
//                NetworkManager.shared.preparedSecureChannel(message: messsage, challengeKey: challengeKey) { (response, error) in
//                    if let model = response {
//                        if let result = model.resultCodes?.returnCode, result == 0 {
//                            if let activateMsg = model.result?.activationMessage {
//                                do {
//                                    try DigiPassSharedData.sharedInstance().secureCache.putString(forValue: activateMsg, forKey: UserCodingKeys.activatedMessage.rawValue)
//                                    let messsage1 = DIGIPassClientSDKWrapper.parseSecureChannelMessage(activateMsg)
//                                    let decryptedMsg1 = DIGIPassClientSDKWrapper.decryptSecureChannelMessageBody()
//                                    self.navigateToLogOnRequestPage(channelMessage: messsage1, decryptedMsg: decryptedMsg1, challengeKey: challengeKey)
//                                }catch { }
//                            }
//                        }
//                    }
//                }
////            }
//
//
//            // Parse the provided NSDictionary and retrieve the title of the notification as a String
//            notificationTitleText = try NotificationSDKClientWrapper.getTitle(userInfo)
//
//            // Parse the provided NSDictionary and retrieve the subject of the notification as a String
//            notificationSubjectText = try NotificationSDKClientWrapper.getSubject(userInfo)
//
//            // Parse the provided NSDictionary and retrieve the badge value of the notification
//            // Set the badge value to 0 in order to remove all notifications.
//            // It is required since, in iOS 7, the remote notifications are not automatically removed when opened.
//            UIApplication.shared.applicationIconBadgeNumber = 0
//
//            ////NSLog("Vasco notification: Title : %@, Subject : %@, content: %@, badge: %d", notificationTitleText, notificationSubjectText, notificationContentText, badgeValue)
//        }
//        catch let error as NSError{
//            errorText = getErrorMessageFromCode(Int32(error.code))
//        }
//        notifyNotificationReceived()
//    }
//}
//
//class QueueResModel {
//    var createdDate: Date? = nil
//    var createdOn: String? = nil
//
//    init(createdOn: String) {
//        self.createdOn = createdOn
//        self.createdDate = convertDate(dateStr: createdOn)
//    }
//
//    func convertDate(dateStr: String) -> Date? {
//        let formater = DateFormatter()
//        formater.dateFormat = "yyyy-MM-dd HH:mm"
//        formater.timeZone = TimeZone.current
//        formater.locale = Locale.current
//        let date = formater.date(from: dateStr)
//        return date
//    }
//}
//
//
extension AppDelegate : MessagingDelegate {
    func messaging(_ messaging: Messaging, didReceiveRegistrationToken fcmToken: String?) {
      print("Firebase registration token: \(String(describing: fcmToken))")

      let dataDict: [String: String] = ["token": fcmToken ?? ""]
      print(dataDict)
      // TODO: If necessary send token to application server.
      // Note: This callback is fired at each app startup and whenever a new token is generated.
    }

}
