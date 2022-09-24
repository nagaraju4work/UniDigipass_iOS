//
//  SideMenuNavigationController.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/27/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit

class SideMenuNavigationController: UINavigationController, UINavigationControllerDelegate {

    var mainMenuVC: MainMenuViewController!
    
    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: Bundle?) {
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
    }
    
    @objc override init(rootViewController: UIViewController) {
        super.init(rootViewController: rootViewController)
    }
    
    @objc convenience init(mainMenuVC: MainMenuViewController) {
        self.init(rootViewController: mainMenuVC)
        self.mainMenuVC = mainMenuVC
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        navigationBar.barTintColor = UIColor.lighBlueColor()
        navigationBar.tintColor = UIColor.white
        navigationBar.isTranslucent = false
        navigationBar.setBackgroundImage(UIImage(), for: .default)
        navigationBar.shadowImage = UIImage()
        navigationBar.titleTextAttributes = [NSAttributedString.Key.foregroundColor: UIColor.white]
        delegate = self
    }
    
    func navigationController(_ navigationController: UINavigationController, willShow viewController: UIViewController, animated: Bool) {
        viewController.view.backgroundColor = UIColor.backgroundColor()
        
        if viewController .isKind(of: MainMenuViewController.self) {
            viewController.navigationController?.navigationBar.isHidden = true
        }else {
            viewController.navigationController?.navigationBar.isHidden = false
        }
    }
    

}
