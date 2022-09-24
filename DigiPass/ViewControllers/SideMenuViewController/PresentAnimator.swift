//
//  PresentAnimator.swift
//  DigiPass
//
//  Created by Unicorp Technologies LLC on 3/28/19.
//  Copyright © 2019 ecknologic. All rights reserved.
//

import Foundation
import UIKit

class PresentAnimator: NSObject, UIViewControllerAnimatedTransitioning {
    
    let duration = 0.4
    var presenting = true
    var originFrame = CGRect(x: -(UIScreen.main.bounds.width), y: 0, width: (UIScreen.main.bounds.width), height: (UIScreen.main.bounds.height))
    var finalFrame = CGRect(x: 0, y: 0, width: (UIScreen.main.bounds.width), height: (UIScreen.main.bounds.height))

    func transitionDuration(using transitionContext: UIViewControllerContextTransitioning?) -> TimeInterval {
        return duration
    }
    
    func animateTransition(using transitionContext: UIViewControllerContextTransitioning) {
        let containerView = transitionContext.containerView
        let toView = presenting ? transitionContext.view(forKey: .to)! : transitionContext.view(forKey: .from)!
        let herbView = presenting ? toView : transitionContext.view(forKey: .from)!
        
        let initialFrame = presenting ? originFrame : self.finalFrame
        let finalFrame = presenting ? self.finalFrame : originFrame
        
        herbView.frame = initialFrame
        
        containerView.addSubview(toView)
        containerView.bringSubviewToFront(herbView)
        
        UIView.animate(withDuration: duration, animations: {
            herbView.frame = finalFrame
        }) { (success) in
            transitionContext.completeTransition(true)
        }
    }
}
