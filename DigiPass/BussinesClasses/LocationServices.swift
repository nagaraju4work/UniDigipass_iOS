//
//  LocationServices.swift
//  OrchestrationSDKSample
//
//  Created by Unicorp Technologies LLC on 4/22/19.
//  Copyright © 2019 vasco. All rights reserved.
//

import UIKit
import CoreLocation

@objc class LocationServices: NSObject, CLLocationManagerDelegate {
    @objc static let shared: LocationServices = LocationServices()
    
    let locationManager = CLLocationManager()
    
    private override init() {
        super.init()
    }
    
    @objc func checkLocationEnable() -> CLAuthorizationStatus {
        if CLLocationManager.locationServicesEnabled() {
            switch CLLocationManager.authorizationStatus() {
            case .notDetermined, .restricted, .denied:
               /* locationManager.delegate = self
                locationManager.desiredAccuracy = kCLLocationAccuracyBest
                locationManager.requestAlwaysAuthorization()
                locationManager.requestWhenInUseAuthorization()
                 locationManager.startUpdatingLocation()*/
                showAlert(with: "Location services", message: "Please enable location services.")
                return .denied
            case .authorizedAlways, .authorizedWhenInUse:
                return .authorizedWhenInUse
            }
        } else {
            showAlert(with: "Location Services Disabled", message: "Please enable location services for this app.")
            return .restricted
        }
    }

    private func showAlert(with title: String, message: String) {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let OKAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(OKAction)
        
        let delegate = UIApplication.shared.delegate as! AppDelegate
        let window = delegate.window
        if let rootController = window?.rootViewController {
            rootController.present(alertController, animated: true, completion: nil)
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
//        print(locations)
    }
}
