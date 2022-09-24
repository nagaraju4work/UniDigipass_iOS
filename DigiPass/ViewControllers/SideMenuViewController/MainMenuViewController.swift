//
//  BaseViewController.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/27/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit

enum ViewControllerType: Int {
    case pin
    case fingerScan
    case face
    case scan
    case info
    case changePin
    case deactivate
}

enum ViewControllerIdentifiers: String {
    case welcomeVCIdentifier = "WelcomeViewController"
    case fingerScanVCIdentifier = "FingerScanViewController"
    case logoutVCIdentifier = "LogoutViewController"
}

class MainMenuViewController: UIViewController {

    let topView: NavBarCustomView = NavBarCustomView(frame: .zero)
    let containerView: UIView = UIView(frame: .zero)
    let presentAnimation = PresentAnimator()
    var welcomeVC: WelcomeViewController!
    
    lazy var leftMenuVC: LeftMenuController = {
        let vc = LeftMenuController()
        vc.delegate = self
        vc.modalPresentationStyle = .overCurrentContext
        vc.transitioningDelegate = self
        return vc
    }()
    
   var topViewController: UIViewController? = nil {
        willSet {
            let newVCType = newValue?.restorationIdentifier
            let oldVCType = topViewController?.restorationIdentifier
            if let vc = topViewController, newVCType != oldVCType { removeController(viewController: vc)}
        }
        didSet {
            let oldVCType = oldValue?.restorationIdentifier
            let newVCType = topViewController?.restorationIdentifier
            if let vc = topViewController,  newVCType != oldVCType { addViewController(viewController: vc)}
        }
    }
    
    // MARK:- Intitilizers
    @objc convenience init(topViewController: UIViewController) {
        self.init(nibName: nil, bundle: nil)
        self.topViewController = topViewController
        self.welcomeVC = topViewController as? WelcomeViewController
        addViewController(viewController: topViewController)
    }
    
    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: Bundle?) {
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    override func loadView() {
        super.loadView()
        view = UIView(frame: UIScreen.main.bounds)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        setup()
    }
    
// MARK:- custom methods
    
    private func setup() {
        // Add menu button on top left corner
        topView.translatesAutoresizingMaskIntoConstraints = false
        topView.delegate = self
        view.addSubview(topView)
        
        containerView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(containerView)
        
        // constraints for top view
        topView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 0).isActive = true
        view.trailingAnchor.constraint(equalTo: topView.trailingAnchor, constant: 0).isActive = true
        if #available(iOS 11.0, *) {
            topView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 0).isActive = true
        } else {
            topView.topAnchor.constraint(equalTo: view.topAnchor, constant: 0).isActive = true
        }
        topView.heightAnchor.constraint(equalToConstant: 100).isActive = true
        
        // constraints for contaniner view
        containerView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 0).isActive = true
        view.trailingAnchor.constraint(equalTo: containerView.trailingAnchor, constant: 0).isActive = true
        containerView.topAnchor.constraint(equalTo: topView.bottomAnchor, constant: 0).isActive = true
        view.bottomAnchor.constraint(equalTo: containerView.bottomAnchor, constant: 0).isActive = true
        
    }
    
    func addViewController(viewController: UIViewController) {
        for vc in children {
            removeController(viewController: vc)
        }
        
        self.addChild(viewController)
        viewController.view.translatesAutoresizingMaskIntoConstraints = false
        containerView.addSubview(viewController.view)
        viewController.didMove(toParent: self)
        
        viewController.view.leadingAnchor.constraint(equalTo: containerView.leadingAnchor, constant: 0).isActive = true
        viewController.view.topAnchor.constraint(equalTo: containerView.topAnchor, constant: 0).isActive = true
        containerView.trailingAnchor.constraint(equalTo: viewController.view.trailingAnchor, constant: 0).isActive = true
        containerView.bottomAnchor.constraint(equalTo: viewController.view.bottomAnchor, constant: 0).isActive = true

    }
    
    private func removeController(viewController: UIViewController) {
        
        viewController.view.removeFromSuperview()
        viewController.removeFromParent()
        viewController.didMove(toParent: nil)
    }
    
    private func getViewController(identifier: String, storyboard: String) -> UIViewController {
        let storyboard = UIStoryboard(name: storyboard, bundle: nil)
        let vc = storyboard.instantiateViewController(withIdentifier: identifier)
        return vc
    }
    
    // TODO REMOVE THE PARAMETERS AND GET THEM FROM SECURE CACHE
    func navigateToLogOnRequestPage(channelMessage: SecureChannelMessageWrapper,
                                    decryptedMsg: String,
                                    challengeKey: String) {
        if let vc = getViewController(identifier: ViewControllerIdentifiers.logoutVCIdentifier.rawValue, storyboard: "DigiPass") as? LogoutViewController {
            // TODO REMOVE THIS AND USE SECURE CACHE
            vc.channelMessage = channelMessage
            vc.challengeKey = challengeKey
            vc.decryptedMessage = decryptedMsg
            addViewController(viewController: vc)
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                self.leftMenuVC.dismiss(animated: true, completion: nil)
            }
        }
    }
}

extension MainMenuViewController: NavBarCustomviewDelegate {
    func leftMenuTapped() {
        present(leftMenuVC, animated: true, completion: nil)
    }
}

extension MainMenuViewController: LeftMenuControllerDelegate {
    func toggleLeftMenu(type: ToggleType) {
        if type == .collapse {
            leftMenuVC.dismiss(animated: true, completion: nil)
        }
    }
    
    func didSelectItem(of type: ViewControllerType) {
        
        var authType: ViewControllerType = ViewControllerType(rawValue: 0)!
        
        switch type {
        case .pin:
            authType = ViewControllerType(rawValue: 0)!
            DigiPassSharedData.sharedInstance().updatePinSelection(forCurrentUser: "pin")
            addViewController(viewController: welcomeVC)
//            topViewController = getViewController(identifier: ViewControllerIdentifiers.welcomeVCIdentifier.rawValue, storyboard: "DigiPass")
//            welcomeVC = (topViewController as! WelcomeViewController)
            welcomeVC.authType = authType
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                self.leftMenuVC.dismiss(animated: true, completion: nil)
            }
        case .fingerScan:
            authType = ViewControllerType(rawValue: 1)!
            DigiPassSharedData.sharedInstance().updatePinSelection(forCurrentUser: "biometric")
            addViewController(viewController: welcomeVC)
            welcomeVC.authType = authType
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                self.leftMenuVC.dismiss(animated: true, completion: nil)
            }
        case .face:
            authType = ViewControllerType(rawValue: 1)!
            DigiPassSharedData.sharedInstance().updatePinSelection(forCurrentUser: "biometric")
            addViewController(viewController: welcomeVC)
            welcomeVC.authType = authType
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                self.leftMenuVC.dismiss(animated: true, completion: nil)
            }
        case .changePin:
            topViewController = getViewController(identifier: ViewControllerIdentifiers.logoutVCIdentifier.rawValue, storyboard: "DigiPass")
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                self.leftMenuVC.dismiss(animated: true, completion: {
                    
                })
            }
        case .scan:
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                self.leftMenuVC.dismiss(animated: true, completion: {
                    self.welcomeVC.scanTapped(self)
                })
            }
        case .info:
            let vc = GetInfoViewController()
            DispatchQueue.main.async {
                self.leftMenuVC.dismiss(animated: true, completion: {
                    self.welcomeVC.hideOTPView()
                    DispatchQueue.main.asyncAfter(deadline: .now() + 0.2) {
                        self.navigationController?.pushViewController(vc, animated: true)
                    }
                })
            }
        case .deactivate:
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                self.leftMenuVC.dismiss(animated: true, completion: {
                    self.welcomeVC.deactivate()
                })
            }
        }
        
    }
}

extension MainMenuViewController: UIViewControllerTransitioningDelegate {
 
    func animationController(forPresented presented: UIViewController, presenting: UIViewController, source: UIViewController) -> UIViewControllerAnimatedTransitioning? {
        presentAnimation.presenting = true
        return presentAnimation
    }
    
    func animationController(forDismissed dismissed: UIViewController) -> UIViewControllerAnimatedTransitioning? {
        presentAnimation.presenting = false
        return presentAnimation
    }
}
