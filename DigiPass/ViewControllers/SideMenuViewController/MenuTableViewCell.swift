//
//  MenuTableViewCell.swift
//  OrchestrationSDKSample
//
//  Created by Unicorp Technologies LLC on 4/17/19.
//  Copyright © 2019 vasco. All rights reserved.
//

import UIKit

class MenuTableViewCell: UITableViewCell {
    
    @IBOutlet weak var iconImage: UIImageView!
    @IBOutlet weak var titleLbl: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
        backgroundColor = UIColor(red: 242/255, green: 242/255, blue: 233/255, alpha: 1)
        selectionStyle = .none
    }
    
    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
        
        // Configure the view for the selected state
    }
    
}
