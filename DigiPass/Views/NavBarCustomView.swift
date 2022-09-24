//
//  NavBarCustomView.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/30/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit

protocol NavBarCustomviewDelegate {
    func leftMenuTapped()
}

class NavBarCustomView: UIView {
    
    var delegate: NavBarCustomviewDelegate? = nil
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setup()
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    lazy var menuButton: UIButton = {
        let button = UIButton(frame: .zero)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.setImage(UIImage(named: "menu"), for: .normal)
        button.clipsToBounds = true
        button.addTarget(self, action: #selector(menuTapped(_:)), for: .touchUpInside)
        return button
    }()
    
    lazy var logoImageView: UIImageView = {
        let logo = UIImageView(frame: .zero)
        logo.image = UIImage(named: "Logo_top_black")
        logo.translatesAutoresizingMaskIntoConstraints = false
        logo.clipsToBounds = true
        logo.contentMode = .scaleAspectFit
        return logo
    }()
    
    private func setup() {
        backgroundColor = UIColor.backgroundColor()
        addSubview(menuButton)
        // constraints for menu button
        menuButton.leadingAnchor.constraint(equalTo: leadingAnchor, constant: 10).isActive = true
        menuButton.topAnchor.constraint(equalTo: topAnchor, constant: 40).isActive = true
        menuButton.widthAnchor.constraint(equalToConstant: 40).isActive = true
        menuButton.heightAnchor.constraint(equalToConstant: 40).isActive = true
        
        addSubview(logoImageView)
        trailingAnchor.constraint(equalTo: logoImageView.trailingAnchor, constant: 20).isActive = true
        logoImageView.heightAnchor.constraint(lessThanOrEqualTo: heightAnchor, multiplier: 1).isActive = true
        logoImageView.leadingAnchor.constraint(equalTo: centerXAnchor, constant: 0).isActive = true
        logoImageView.topAnchor.constraint(equalTo: topAnchor, constant: 0).isActive = true
    }
    
    @objc func menuTapped(_ sender: Any) {
        delegate?.leftMenuTapped()
    }
}
