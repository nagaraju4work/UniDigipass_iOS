//
//  ProfileTableViewCell.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/30/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import UIKit

class ProfileTableViewCell: UITableViewCell {

    lazy var profileImageView: UIImageView = {
        let view = UIImageView(frame: .zero)
        view.translatesAutoresizingMaskIntoConstraints = false
        view.clipsToBounds = true
        view.image = UIImage(named: "profile")
        return view
    }()
    
    lazy var nameLbl: UILabel = {
        let view = UILabel(frame: .zero)
        view.translatesAutoresizingMaskIntoConstraints  = false
        view.textColor = UIColor.white
        view.text = "Naga Raju Taddiiseti"
        view.font = UIFont.boldSystemFont(ofSize: 17)
        view.numberOfLines = 0
        return view
    }()
    
    lazy var idLbl: UILabel = {
        let view = UILabel(frame: .zero)
        view.translatesAutoresizingMaskIntoConstraints  = false
        view.textColor = UIColor.white
        view.text = "ID 12345"
        view.font = UIFont.systemFont(ofSize: 15)
        return view
    }()
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        setup()
    }
    
    required init?(coder aDecoder: NSCoder) {
       super.init(coder: aDecoder)
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
        setup()
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

    // MARK:- custom methods
    private func setup() {
        selectionStyle = .none
        backgroundColor = UIColor.lighBlueColor()
        contentView.addSubview(profileImageView)
        contentView.addSubview(nameLbl)
        contentView.addSubview(idLbl)
        
        // constraints for profile image view
        profileImageView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 30).isActive = true
        profileImageView.widthAnchor.constraint(equalToConstant: 80).isActive = true
        profileImageView.heightAnchor.constraint(equalToConstant: 80).isActive = true
        profileImageView.centerYAnchor.constraint(equalTo: contentView.centerYAnchor, constant: 0).isActive = true
        
        customizeProfileView()
        
        // constraints for name lable
        nameLbl.leadingAnchor.constraint(equalTo: profileImageView.trailingAnchor, constant: 8).isActive = true
        contentView.trailingAnchor.constraint(equalTo: nameLbl.trailingAnchor, constant: 15).isActive = true
        nameLbl.topAnchor.constraint(equalTo: profileImageView.topAnchor, constant: 20).isActive = true
        
        // constraints for id lable
        idLbl.leftAnchor.constraint(equalTo: nameLbl.leftAnchor, constant: 0).isActive = true
        idLbl.rightAnchor.constraint(equalTo: nameLbl.rightAnchor, constant: 0).isActive = true
        idLbl.topAnchor.constraint(equalTo: nameLbl.bottomAnchor, constant: 8).isActive = true
    }
    
    private func customizeProfileView() {
        profileImageView.layer.cornerRadius = profileImageView.frame.width / 2
        profileImageView.clipsToBounds = true
    }
}
