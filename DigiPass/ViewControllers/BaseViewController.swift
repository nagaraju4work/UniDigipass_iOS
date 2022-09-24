//
//  BaseViewController.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/30/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit

class BaseViewController: UIViewController {

    lazy var bgView: UIImageView = {
        let view = UIImageView(frame: .zero)
        view.image = UIImage(named: "BG_images")
        view.translatesAutoresizingMaskIntoConstraints = false
        view.contentMode = .scaleAspectFit
        view.clipsToBounds = true
        return view
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    

    // MARK:- custom methods
    
    func setup() {
        view.backgroundColor = UIColor.backgroundColor()

        view.insertSubview(bgView, at: 0)
        
        bgView.centerXAnchor.constraint(equalTo: view.centerXAnchor, constant: 0).isActive = true
        bgView.centerYAnchor.constraint(equalTo: view.centerYAnchor, constant: -60).isActive = true
        bgView.widthAnchor.constraint(lessThanOrEqualTo: view.widthAnchor, multiplier: 1).isActive = true
        bgView.heightAnchor.constraint(lessThanOrEqualTo: view.heightAnchor, multiplier: 0.5).isActive = true
        
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
