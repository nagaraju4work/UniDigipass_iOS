//
//  Appearance.swift
//  MCKPinController
//
//  Created by Himal Madhushan on 11/28/18.
//  Copyright © 2018 Himal Madhushan. All rights reserved.
//

import UIKit
import Foundation

public enum MCKLayerType {
    case square, rounded
}

public struct MCKAppearance {
    
    public var dots = MCKDotAppearance()
    
    public var general = MCKGeneralAppearance()
    
    public var numberPad = MCKNumberPadAppearance()
    
    public init() { }
    
}


public struct MCKGeneralAppearance {
    
    public var backgroundColor: UIColor = UIColor(white: 0, alpha: 0.5)
    
    /// Default is set to `UIBlurEffect.Style.dark`.
    public var blurEffect: UIBlurEffect = UIBlurEffect(style: .prominent)
    
    public var imageTint: UIColor = .white
    
    public init() { }
    
}


public struct MCKNumberPadAppearance {
    
    public var fillingColor: UIColor = .clear
    
    public var borderColor: UIColor = .black
    
    /// Changes the color of number (1...0 and backspace)
    public var textColor: UIColor = .black
    
    public var borderWidth: CGFloat = 1
    
    /// Sets the text to titleLabel of the backspace button, Ex: String("↩︎")
    public var backspaceTitle: String? // = ""
    
    public var backspaceImage: UIImage?
    
    /// Default is set to `rounded`.
    public var layerType: MCKLayerType = .rounded
    
    public init() { }
    
}


public struct MCKDotAppearance {
    
    public var fillingColor: UIColor = .black
    public var borderColor: UIColor = UIColor(white: 0, alpha: 1)
    
    /// Default is set to `rounded`.
    public var layerType: MCKLayerType = .rounded
    
    public init() { }
}
