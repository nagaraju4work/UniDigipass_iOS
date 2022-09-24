//
//  UIColor+Extension.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/27/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import Foundation
import UIKit

extension UIColor {
    static func backgroundColor() -> UIColor {
        return UIColor(red: 243/255, green: 241/255, blue: 234/255, alpha: 1)
    }
    
    static func buttonBgColor1() -> UIColor {
        return UIColor(red: 158/255, green: 142/255, blue: 101/255, alpha: 1)
    }
    
    static func buttonBgColor2() -> UIColor {
        return UIColor(red: 103/255, green: 40/255, blue: 53/255, alpha: 1)
    }
    
    static func scanViewColor() -> UIColor {
        return UIColor(red: 168/255, green: 39/255, blue: 52/255, alpha: 1)
    }
    
    static func lighBlueColor() -> UIColor {
        return UIColor(red: 36/255, green: 70/255, blue: 110/255, alpha: 1)
    }
}
