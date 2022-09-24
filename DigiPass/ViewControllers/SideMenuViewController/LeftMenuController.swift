//
//  LeftMenuController.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/27/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit

enum ToggleType: Int {
    case expand
    case collapse
}

protocol LeftMenuControllerDelegate {
    func toggleLeftMenu(type: ToggleType)
    func didSelectItem(of type: ViewControllerType)
}

class LeftMenuController: UIViewController {

    let menuIdentifier = "menuCell"

    var delegate: LeftMenuControllerDelegate? = nil
    var profileHeaderView: ProfileHeaderView!
    var section1Data: [[String: String]] = [[String: String]]()
    var section2Data: [[String: String]] = [[String: String]]()
    
    lazy var tableView: UITableView = {
        let tableView = UITableView(frame: .zero, style: .plain)
        tableView.dataSource = self
        tableView.delegate = self
        tableView.translatesAutoresizingMaskIntoConstraints = false
//        tableView.separatorColor = UIColor.white
        tableView.tableFooterView = UIView(frame: .zero)
        tableView.backgroundColor = UIColor(red: 242/255, green: 242/255, blue: 233/255, alpha: 1)
        return tableView
    }()
    
    lazy var backgroundImageView: UIImageView = {
        let imageView = UIImageView(frame: .zero)
        imageView.translatesAutoresizingMaskIntoConstraints = false
        imageView.backgroundColor = UIColor.black.withAlphaComponent(0.6)
        imageView.isUserInteractionEnabled = true
        
        let tap = UITapGestureRecognizer(target: self, action: #selector(collapseLeftMenu(_:)))
        tap.numberOfTapsRequired = 1
        imageView.addGestureRecognizer(tap)
        return imageView
    }()
    
    var tableDataArray: [String] = [String]()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        view.backgroundColor = UIColor.clear
        setup()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        profileHeaderView.reloadData()
        tableView.reloadData()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        addBgView()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        backgroundImageView.removeFromSuperview()
    }
    
    // MARK:- custom methods
    private func setup() {
        section1Data = [["title": isCurrentDeviceEnableFaceAuth() ? "Face Authentication" :  "Biometric Authentication", "image": isCurrentDeviceEnableFaceAuth() ? "faceid" : "biometric"] ,
                                    ["title": "Pin", "image": "pin"]]
        section2Data = [["title": "Activate", "image": "checkmark"],
                        ["title": "Deactivate", "image": "deactivate"],
                        ["title": "About DigiPass", "image": "about"]]
        
        view.backgroundColor = UIColor(red: 242/255, green: 242/255, blue: 233/255, alpha: 1)
        view.addSubview(tableView)

        tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 0).isActive = true
        view.trailingAnchor.constraint(equalTo: tableView.trailingAnchor, constant: 60).isActive = true
        if #available(iOS 11.0, *) {
            tableView.safeAreaLayoutGuide.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 0).isActive = true
        } else {
            tableView.topAnchor.constraint(equalTo: view.topAnchor, constant: 0).isActive = true
        }
        view.bottomAnchor.constraint(equalTo: tableView.bottomAnchor, constant: 0).isActive = true
        
        tableView.register(MenuTableViewCell.self, forCellReuseIdentifier: "menuCell")
        tableView.register(UINib(nibName: "MenuTableViewCell", bundle: nil), forCellReuseIdentifier: menuIdentifier)
        
        profileHeaderView = ProfileHeaderView(frame: CGRect(x: 0, y: 0, width: tableView.bounds.width, height: 230))
        profileHeaderView.delegate = self
        tableView.tableHeaderView = profileHeaderView
    }
    
    private func addBgView() {
        view.insertSubview(backgroundImageView, at: 0)
        // constraints for background image view
        backgroundImageView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 0).isActive = true
        view.trailingAnchor.constraint(equalTo: backgroundImageView.trailingAnchor, constant: 0).isActive = true
        backgroundImageView.topAnchor.constraint(equalTo: view.topAnchor, constant: 0).isActive = true
        view.bottomAnchor.constraint(equalTo: backgroundImageView.bottomAnchor, constant: 0).isActive = true
    }
    
    @objc private func collapseLeftMenu(_ sender: UITapGestureRecognizer) {
        delegate?.toggleLeftMenu(type: .collapse)
    }
    
    internal func isCurrentDeviceEnableFaceAuth() -> Bool {
        let model = UIDevice.modelName
        switch model {
        case "iPhone X":
            return true
        case "iPhone XS":
            return true
        case "iPhone XS Max":
            return true
        case "iPhone XR":
            return true
        default:
            return false
        }
    }
}

extension LeftMenuController: ProfileHeaderviewProtocol {
    func showUsers() {
        let controller = UsersListViewController()
        controller.delegate = self
        controller.modalPresentationStyle = .popover
        controller.preferredContentSize = CGSize(width: 300, height: 200)
        let presentationController = AlwaysPresentAsPopover.configurePresentation(forController: controller)
        presentationController.sourceView = profileHeaderView
        presentationController.sourceRect = profileHeaderView.bounds
        presentationController.permittedArrowDirections = [.down, .up]
        self.present(controller, animated: true)
    }
    
    func activate() {
        delegate?.didSelectItem(of: .scan)
    }
}

extension LeftMenuController: UsersListViewControllerProtocol {
    func didSelectUser() {
        profileHeaderView.reloadData()
        NotificationCenter.default.post(name: Notification.Name("UpdateUserName"), object: nil)
    }
}

extension LeftMenuController: UITableViewDelegate, UITableViewDataSource {
    func numberOfSections(in tableView: UITableView) -> Int {
        return 2
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section == 0 {
            return section1Data.count
        }else if section == 1 {
            return section2Data.count
        }
        return 0
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: menuIdentifier) as! MenuTableViewCell
        var dict: [String: String]!
        if indexPath.section == 0 {
            dict =  section1Data[indexPath.row]
        }else if indexPath.section == 1 {
            dict =  section2Data[indexPath.row]
        }
        cell.titleLbl.text = dict["title"]
        if let name = dict["image"], let image = UIImage(named: name) {
            cell.iconImage.image = image
        }
        
        if indexPath.section == 0 {
            let isBiometric = UserDefaults.standard.object(forKey: "isBiometric") as? Bool
            if let isbio = isBiometric, isbio, indexPath.row == 0  {
                let image = cell.iconImage.image?.withRenderingMode(.alwaysTemplate)
                cell.iconImage.tintColor = .red
                cell.iconImage.image = image
            }else if let isbio = isBiometric, !isbio, indexPath.row == 1 {
                let image = cell.iconImage.image?.withRenderingMode(.alwaysTemplate)
                cell.iconImage.tintColor = .red
                cell.iconImage.image = image
            }else {
                let image = cell.iconImage.image?.withRenderingMode(.alwaysOriginal)
                cell.iconImage.tintColor = .clear
                cell.iconImage.image = image
            }
        }
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        if indexPath.section == 0 {
            switch indexPath.row {
            case 0:
                delegate?.didSelectItem(of: isCurrentDeviceEnableFaceAuth() ? .face : .fingerScan)
            case 1:
                delegate?.didSelectItem(of: .pin)
            default:
                delegate?.didSelectItem(of: .pin)
            }
        }else if indexPath.section == 1 {
            switch indexPath.row {
            case 0:
                delegate?.didSelectItem(of: .scan)
            case 1:
                delegate?.didSelectItem(of: .deactivate)
            case 2:
                delegate?.didSelectItem(of: .info)
            default:
                break
            }
        }
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return section == 1 ? "Settings" : nil
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 50
    }
}

class AlwaysPresentAsPopover : NSObject, UIPopoverPresentationControllerDelegate {
    
    // `sharedInstance` because the delegate property is weak - the delegate instance needs to be retained.
    private static let sharedInstance = AlwaysPresentAsPopover()
    
    private override init() {
        super.init()
    }
    
    func adaptivePresentationStyle(for controller: UIPresentationController) -> UIModalPresentationStyle {
        return .none
    }
    
    static func configurePresentation(forController controller : UIViewController) -> UIPopoverPresentationController {
        controller.modalPresentationStyle = .popover
        let presentationController = controller.presentationController as! UIPopoverPresentationController
        presentationController.delegate = AlwaysPresentAsPopover.sharedInstance
        return presentationController
    }
    
}


public extension UIDevice {
    
    static let modelName: String = {
        var systemInfo = utsname()
        uname(&systemInfo)
        let machineMirror = Mirror(reflecting: systemInfo.machine)
        let identifier = machineMirror.children.reduce("") { identifier, element in
            guard let value = element.value as? Int8, value != 0 else { return identifier }
            return identifier + String(UnicodeScalar(UInt8(value)))
        }
        
        func mapToDevice(identifier: String) -> String { // swiftlint:disable:this cyclomatic_complexity
            #if os(iOS)
            switch identifier {
            case "iPod5,1":                                 return "iPod Touch 5"
            case "iPod7,1":                                 return "iPod Touch 6"
            case "iPhone3,1", "iPhone3,2", "iPhone3,3":     return "iPhone 4"
            case "iPhone4,1":                               return "iPhone 4s"
            case "iPhone5,1", "iPhone5,2":                  return "iPhone 5"
            case "iPhone5,3", "iPhone5,4":                  return "iPhone 5c"
            case "iPhone6,1", "iPhone6,2":                  return "iPhone 5s"
            case "iPhone7,2":                               return "iPhone 6"
            case "iPhone7,1":                               return "iPhone 6 Plus"
            case "iPhone8,1":                               return "iPhone 6s"
            case "iPhone8,2":                               return "iPhone 6s Plus"
            case "iPhone9,1", "iPhone9,3":                  return "iPhone 7"
            case "iPhone9,2", "iPhone9,4":                  return "iPhone 7 Plus"
            case "iPhone8,4":                               return "iPhone SE"
            case "iPhone10,1", "iPhone10,4":                return "iPhone 8"
            case "iPhone10,2", "iPhone10,5":                return "iPhone 8 Plus"
            case "iPhone10,3", "iPhone10,6":                return "iPhone X"
            case "iPhone11,2":                              return "iPhone XS"
            case "iPhone11,4", "iPhone11,6":                return "iPhone XS Max"
            case "iPhone11,8":                              return "iPhone XR"
            case "iPad2,1", "iPad2,2", "iPad2,3", "iPad2,4":return "iPad 2"
            case "iPad3,1", "iPad3,2", "iPad3,3":           return "iPad 3"
            case "iPad3,4", "iPad3,5", "iPad3,6":           return "iPad 4"
            case "iPad4,1", "iPad4,2", "iPad4,3":           return "iPad Air"
            case "iPad5,3", "iPad5,4":                      return "iPad Air 2"
            case "iPad6,11", "iPad6,12":                    return "iPad 5"
            case "iPad7,5", "iPad7,6":                      return "iPad 6"
            case "iPad11,4", "iPad11,5":                    return "iPad Air (3rd generation)"
            case "iPad2,5", "iPad2,6", "iPad2,7":           return "iPad Mini"
            case "iPad4,4", "iPad4,5", "iPad4,6":           return "iPad Mini 2"
            case "iPad4,7", "iPad4,8", "iPad4,9":           return "iPad Mini 3"
            case "iPad5,1", "iPad5,2":                      return "iPad Mini 4"
            case "iPad11,1", "iPad11,2":                    return "iPad Mini 5"
            case "iPad6,3", "iPad6,4":                      return "iPad Pro (9.7-inch)"
            case "iPad6,7", "iPad6,8":                      return "iPad Pro (12.9-inch)"
            case "iPad7,1", "iPad7,2":                      return "iPad Pro (12.9-inch) (2nd generation)"
            case "iPad7,3", "iPad7,4":                      return "iPad Pro (10.5-inch)"
            case "iPad8,1", "iPad8,2", "iPad8,3", "iPad8,4":return "iPad Pro (11-inch)"
            case "iPad8,5", "iPad8,6", "iPad8,7", "iPad8,8":return "iPad Pro (12.9-inch) (3rd generation)"
            case "AppleTV5,3":                              return "Apple TV"
            case "AppleTV6,2":                              return "Apple TV 4K"
            case "AudioAccessory1,1":                       return "HomePod"
            case "i386", "x86_64":                          return "Simulator \(mapToDevice(identifier: ProcessInfo().environment["SIMULATOR_MODEL_IDENTIFIER"] ?? "iOS"))"
            default:                                        return identifier
            }
            #elseif os(tvOS)
            switch identifier {
            case "AppleTV5,3": return "Apple TV 4"
            case "AppleTV6,2": return "Apple TV 4K"
            case "i386", "x86_64": return "Simulator \(mapToDevice(identifier: ProcessInfo().environment["SIMULATOR_MODEL_IDENTIFIER"] ?? "tvOS"))"
            default: return identifier
            }
            #endif
        }
        
        return mapToDevice(identifier: identifier)
    }()
    
}
