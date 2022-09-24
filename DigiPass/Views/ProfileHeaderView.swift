//
//  ProfileHeaderView.swift
//  LeftMenu
//
//  Created by Unicorp Technologies LLC on 4/22/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit

protocol ProfileHeaderviewProtocol {
    func showUsers()
    func activate()
}

class ProfileHeaderView: UIView {

    var delegate: ProfileHeaderviewProtocol? = nil
//    let sharedStorage = SharedPreferencesStorage()
    
    @IBOutlet weak var view: UIView!
    @IBOutlet weak var userView: UIView!
    @IBOutlet weak var userLbl: UILabel!

    var userName: String = "" {
        willSet { self.userLbl.text = newValue }
    }
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setup()
    }
    
    required init?(coder aDecoder: NSCoder) {
        return nil
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self)
    }
    
    override func awakeFromNib() {
        setup()
    }
    
    private func loadViewFromNib() -> UIView {
        let bundle = Bundle(for: ProfileHeaderView.self)
        let nib = UINib(nibName: "ProfileHeaderView", bundle: bundle)
        let nibView = nib.instantiate(withOwner: self, options: nil).first as! UIView
        
        return nibView
    }
    
    private func setup() {
        view = loadViewFromNib()
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        view.translatesAutoresizingMaskIntoConstraints = true
        addSubview(view)
        
        let tap = UITapGestureRecognizer(target: self, action: #selector(usersTap))
        userView.addGestureRecognizer(tap)
        let user = DigiPassSharedData.sharedInstance().currentUser()
        if let userName = user["userName"] as? String {
            self.userName = userName
        }else {
            userName = "No Users Activated"
        }
    }
    
    @objc func usersTap() {
        let users = UserDefaults.standard.object(forKey: "users") as? [[String: Any]]
        if let results = users, results.count > 0 {
            delegate?.showUsers()
         }else {
            delegate?.activate()
        }
    }
    
    func reloadData() {
        
        let user = DigiPassSharedData.sharedInstance().currentUser()
        if let userName = user["userName"] as? String {
            self.userName = userName
        }else {
            userName = "No Users Activated"
        }
    }
}
