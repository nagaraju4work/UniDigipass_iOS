//
//  GetInfoViewController.swift
//  OrchestrationSDKSample
//
//  Created by Unicorp Technologies LLC on 4/23/19.
//  Copyright © 2019 vasco. All rights reserved.
//

import UIKit

class GetInfoViewController: UIViewController {
    
    var tableDataArray: [[String: String]] = [[String: String]]()
    var user: [String: Any]!
    
    lazy var tableView: UITableView = {
        let tableView = UITableView(frame: .zero, style: .grouped)
        tableView.dataSource = self
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
        
        // Do any additional setup after loading the view.
        setup()
    }
    
    private func setup() {
        configureDataSource()
        navigationItem.title = "DigiPass Information"
        view.addSubview(tableView)
        tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 0).isActive = true
        view.trailingAnchor.constraint(equalTo: tableView.trailingAnchor, constant: 0).isActive = true
        tableView.topAnchor.constraint(equalTo: view.topAnchor, constant: 0).isActive = true
        view.bottomAnchor.constraint(equalTo: tableView.bottomAnchor, constant: 0).isActive = true
        
    }
    
    func configureDataSource() {
        user = DigiPassSharedData.sharedInstance().currentUser() as? [String : Any]
        let timeShift = DIGIPassClientSDKWrapper.fetchServerTimeSS()
        let sequence = DIGIPassClientSDKWrapper.getDigiPassPropertyInt(vds_int32(PROPERTY_SEQUENCE_NUMBER), cryptoIndex: vds_int32(CRYPTO_APPLICATION_INDEX_APP_1))
        let serial = DIGIPassClientSDKWrapper.getDigiPassPropertyStr(vds_int32(PROPERTY_SERIAL_NUMBER), valueLength: vds_int32(LENGTH_SERIAL_NUMBER + 1), cryptoIndex: 0)
        
        if let userName = user["userName"] as? String {
            tableDataArray = [["header":"User Identifier", "value": userName],
                              ["header":"DIGIPASS Serial Number", "value": serial],
                              ["header":"DIGIPASS Sequence Number", "value": sequence],
                              ["header": "Client Server Time Shift(sec)", "value": "\(timeShift)"]]
        }
    }
}

extension GetInfoViewController: UITableViewDataSource {
    func numberOfSections(in tableView: UITableView) -> Int {
        return tableDataArray.count
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = UITableViewCell(style: .default, reuseIdentifier: "cell")
        let dict = tableDataArray[indexPath.section]
        cell.textLabel?.text = dict["value"]
        return cell
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        let dict = tableDataArray[section]
        return dict["header"]
    }
}
