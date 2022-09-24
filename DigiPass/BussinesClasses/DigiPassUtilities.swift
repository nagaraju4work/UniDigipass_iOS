//
//  DigiPassUtilities.swift
//  DSAPPSample
//
//  Created by Unicorp Technologies LLC on 8/3/19.
//  Copyright © 2019 OneSpan. All rights reserved.
//

import Foundation

class DigiPassUtilities: NSObject {
    
    static let usersKey = "Users"
    static let currentUserKey = "CurrentUser"
   
    override init() {
        super.init()
    }
    
//    static func getUsers() -> [MDUserActivateModelWrapper] {
//        let userDefaults = UserDefaults.standard
//        var results = [MDUserActivateModelWrapper]()
//        if let users = userDefaults.object(forKey: usersKey)  as? [Data] {
//            for data in users {
//                if let user = NSKeyedUnarchiver.unarchiveObject(with: data) as? MDUserActivateModelWrapper {
//                    results.append(user)
//                }
//            }
//        }
//        return results
//    }
    
    /*static func addUser(user: MDUserActivateModelWrapper) {
        let data = NSKeyedArchiver.archivedData(withRootObject: user)
        let userDefaults = UserDefaults.standard
        var results = [Data]()
        if let users = userDefaults.object(forKey: usersKey)  as? [Data]  {
            results = users
            results.append(data)
        }else {
            results.append(data)
        }
        userDefaults.set(results, forKey: usersKey)
        userDefaults.synchronize()
    }
    
    static func setCurrentUser(user: MDUserActivateModelWrapper) {
        let userDefauls = UserDefaults.standard
        let data = NSKeyedArchiver.archivedData(withRootObject: user)
        userDefauls.set(data, forKey: currentUserKey)
        userDefauls.synchronize()
    }*/
    
//    static func currentUser() -> MDUserActivateModelWrapper? {
//        let userDefauls = UserDefaults.standard
//        if let data = userDefauls.object(forKey: currentUserKey) as? Data {
//            let user = NSKeyedUnarchiver.unarchiveObject(with: data) as? MDUserActivateModelWrapper
//            return user
//        }
//        return nil
//    }
    
//    static func deleteUser(user: MDUserActivateModelWrapper) {
//        var users = getUsers()
//        var index = 0
//        for u in users {
//            if user.userId == u.userId {
//                break
//            }
//            index += 1
//        }
//        users.remove(at: index)
//        UserDefaults.standard.set(users, forKey: usersKey)
//    }
//    
//    static func updateUserOption(user: MDUserActivateModelWrapper, isPinSelect: Bool) {
//        user.isPinSelected = isPinSelect
//        let users = getUsers()
//        for u in users {
//            if u.userId == user.userId {
//                
//            }
//        }
//    }
    
    // MARK:- UIAlertController methods
    
    static func showAlert(title: String?,
                          message: String?,
                          cancel titleStr: String,
                          viewController: UIViewController,
                          cancelHandler: ((_ action: UIAlertAction) -> Void)? = nil) {
        let controller = UIAlertController(title: title, message: message, preferredStyle: .alert)
        
        controller.addAction(UIAlertAction(title: titleStr, style: .cancel, handler: { (action) in
            if let h = cancelHandler {
                h(action)
            }
        }))
        viewController.present(controller, animated: true, completion: nil)
    }
    
    static func showAlertOnRootVC(title: String?,
                                  message: String?,
                                  cancel titleStr: String,
                                  cancelHandler: ((_ action: UIAlertAction) -> Void)? = nil) {
        let appDelegate = UIApplication.shared.delegate as! AppDelegate
        let router = appDelegate.appRouter
        if let rootViewController = router?.window.rootViewController {
            DigiPassUtilities.showAlert(title: title, message: message, cancel: titleStr, viewController: rootViewController, cancelHandler: cancelHandler)
        }
    }
    
}
