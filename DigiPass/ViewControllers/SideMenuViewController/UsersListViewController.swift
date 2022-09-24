//
//  UsersListViewController.swift
//  OrchestrationSDKSample
//
//  Created by Unicorp Technologies LLC on 4/23/19.
//  Copyright © 2019 vasco. All rights reserved.
//

import UIKit

protocol UsersListViewControllerProtocol {
    func didSelectUser()
}

class UsersListViewController: UIViewController {

    /*var orchestrator: OrchestrationProtocol!
    var sharedStorage: SharedPreferencesStorage = SharedPreferencesStorage()*/
    
    var delegate: UsersListViewControllerProtocol? = nil
    var users: [[String: Any]] = [[String: Any]]()

    lazy var tableView: UITableView = {
        let tableView = UITableView(frame: .zero, style: .grouped)
        tableView.dataSource = self
        tableView.delegate = self
        tableView.translatesAutoresizingMaskIntoConstraints = false
        //        tableView.separatorColor = UIColor.white
        tableView.tableFooterView = UIView(frame: .zero)
        tableView.backgroundColor = UIColor(red: 242/255, green: 242/255, blue: 233/255, alpha: 1)
        return tableView
    }()
    
    override func loadView() {
        super.loadView()
        self.view = UIView(frame: UIScreen.main.bounds)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setup()
    }
    
    // MARK:- custom methods
    
    private func setup() {
        view.addSubview(tableView)
        // constraints for tableview
        tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 0).isActive = true
        view.trailingAnchor.constraint(equalTo: tableView.trailingAnchor, constant: 0).isActive = true
        tableView.topAnchor.constraint(equalTo: view.topAnchor, constant: 0).isActive = true
        view.bottomAnchor.constraint(equalTo: tableView.bottomAnchor, constant: 0).isActive = true
        
        configure()
    }
    
    func configure() {
       /* let cddcParams = CDDCParams()
        cddcParams.addOptionalRetrievableField(OptionalRetrievableFieldsBluetooth)
        cddcParams.addOptionalRetrievableField(OptionalRetrievableFieldsGeolocation)

        let orchestrationDelegate = SampleOrchestrationDelegate()
        orchestrationDelegate.setViewController(self)
        
        let builder = OrchestratorBuilder()
        builder.setDigipassSalt(SALT_DIGIPASS)
        builder.setStorageSalt(SALT_STORAGE)
        builder.setDefaultDomain(ACCOUNT_IDENTIFIER.lowercased())
        builder.setCDDCParams(cddcParams)
        builder.setErrorDelegate(orchestrationDelegate)
        builder.setWarningDelegate(orchestrationDelegate)
        orchestrator = builder.build();*/
        
        users = UserDefaults.standard.object(forKey: "users") as! [[String : Any]]
    }
    
    /*func getUsers() -> [OrchestrationUser] {
        return orchestrator.userManager().users()
    }*/
}

extension UsersListViewController: UITableViewDelegate, UITableViewDataSource {
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return users.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = UITableViewCell(style: .default, reuseIdentifier: "userCell")
        let user = users[indexPath.row]
         //sharedStorage.activatedUser()
        cell.textLabel?.text = user["userName"] as? String
        let name = user["userName"] as? String
        let currentUserDetails = DigiPassSharedData.sharedInstance().currentUser()
        let currentUserName = currentUserDetails["userName"] as? String
        if let userName = currentUserName, let userName1 = name, userName.caseInsensitiveCompare(userName1) == .orderedSame {
            cell.accessoryType = .checkmark
        }
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let user = users[indexPath.row]
        UserDefaults.standard.set(user, forKey: "currentUser")
        UserDefaults.standard.synchronize()
        
        //sharedStorage.storeActivatedUser(user.identifier)
        dismiss(animated: true) {
            self.delegate?.didSelectUser()
        }
    }
}
