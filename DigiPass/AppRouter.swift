//
//  AppRouter.swift
//  OrchestrationSDKSample
//
//  Created by Unicorp Technologies LLC on 3/31/19.
//  Copyright © 2019 vasco. All rights reserved.
//

import Foundation
import UIKit

@objc class AppRouter: NSObject {
    
    var window: UIWindow!
    
   @objc  init(window: UIWindow) {
        super.init()
        self.window = window
        setup()
    }
    
    private func setup() {
        let storyboard = UIStoryboard(name: "DigiPass", bundle: nil)
        let welcomeVC = storyboard.instantiateViewController(withIdentifier: "WelcomeViewController")
        let mainVC = MainMenuViewController(topViewController: welcomeVC)
        let sideNavVC = SideMenuNavigationController(mainMenuVC: mainVC)
        window.rootViewController = sideNavVC
        window.makeKeyAndVisible()
        
       /* let storyboard = UIStoryboard(name: "Main", bundle: nil)
        let mainVC = storyboard.instantiateViewController(withIdentifier: "MainNavVC")
        window.rootViewController = mainVC
        window.makeKeyAndVisible()*/
    }
}
