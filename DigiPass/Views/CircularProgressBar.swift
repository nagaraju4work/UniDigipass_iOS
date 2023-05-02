import UIKit

protocol CircularProgressBarDelegate {
    func didCompleteTimeOut()
}

class CircularProgressBar: UIView {
    
    var delegate: CircularProgressBarDelegate? = nil
    var otp: String = "0"
    var timer: Timer!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        setupView()
        label.text = otp
    }
    
    init(with otp: String) {
        super.init(frame: .zero)
        setupView()
        self.otp = otp
        label.text = otp
        
        NotificationCenter.default.addObserver(self, selector: #selector(invalidateOTP), name: UIApplication.didEnterBackgroundNotification, object: nil)
    }
    
    required init?(coder aDecoder: NSCoder) {
        return nil
    }
    
    //MARK: Public
    
    public var lineWidth:CGFloat = 10 {
        didSet{
            foregroundLayer.lineWidth = lineWidth
            backgroundLayer.lineWidth = lineWidth - (0.20 * lineWidth)
        }
    }
    
    public var labelSize: CGFloat = 20 {
        didSet {
            label.font = UIFont.boldSystemFont(ofSize: labelSize)
            label.sizeToFit()
            configLabel()
        }
    }
    
    public var safePercent: Int = 100 {
        didSet{
            setForegroundLayerColorForSafePercent()
        }
    }
    
    public func setProgress(to progressConstant: Double, withAnimation: Bool) {
        
        var progress: Double {
            get {
                if progressConstant > 1 { return 1 }
                else if progressConstant < 0 { return 0 }
                else { return progressConstant }
            }
        }
        
        foregroundLayer.strokeEnd = CGFloat(progress)
        
        if withAnimation {
            let animation = CABasicAnimation(keyPath: "strokeEnd")
            animation.fromValue = 0
            animation.toValue = progress
            animation.duration = 32
            foregroundLayer.add(animation, forKey: "foregroundAnimation")
            
        }
        
        var currentTime:Double = 0
        if #available(iOS 10.0, *) {
            timer = Timer.scheduledTimer(withTimeInterval: 0.05, repeats: true) { (timer) in
                if currentTime >= 32 {
                    timer.invalidate()
                    self.delegate?.didCompleteTimeOut()
                } else {
                    currentTime += 0.05
                    self.label.text = self.otp//"\(Int(progress * percent))"
                    self.setForegroundLayerColorForSafePercent()
                    self.configLabel()
                }
            }
        } else {
            // Fallback on earlier versions
        }
        timer.fire()
    }
    
    @objc internal func invalidateOTP() {
        if timer.isValid {
            timer.invalidate()
            self.delegate?.didCompleteTimeOut()
        }
    }
    
    //MARK: Private
    private var label = UILabel()
    private let foregroundLayer = CAShapeLayer()
    private let backgroundLayer = CAShapeLayer()
    private var radius: CGFloat {
        get{
            if self.frame.width < self.frame.height { return (self.frame.width - lineWidth)/2 }
            else { return (self.frame.height - lineWidth)/2 }
        }
    }
    
    private var pathCenter: CGPoint{ get{ return self.convert(self.center, from:self.superview) } }
    private func makeBar(){
        self.layer.sublayers = nil
        drawBackgroundLayer()
        drawForegroundLayer()
    }
    
    private func drawBackgroundLayer(){
        let path = UIBezierPath(arcCenter: pathCenter, radius: self.radius, startAngle: 0, endAngle: 2*CGFloat.pi, clockwise: true)
        self.backgroundLayer.path = path.cgPath
        self.backgroundLayer.strokeColor = UIColor.lightGray.cgColor
        self.backgroundLayer.lineWidth = lineWidth - (lineWidth * 20/100)
        self.backgroundLayer.fillColor = UIColor.clear.cgColor
        self.layer.addSublayer(backgroundLayer)
        
    }
    
    private func drawForegroundLayer(){
        
        let startAngle = (-CGFloat.pi/2)
        let endAngle = 2 * CGFloat.pi + startAngle
        
        let path = UIBezierPath(arcCenter: pathCenter, radius: self.radius, startAngle: startAngle, endAngle: endAngle, clockwise: true)
        
        foregroundLayer.lineCap = CAShapeLayerLineCap.round
        foregroundLayer.path = path.cgPath
        foregroundLayer.lineWidth = lineWidth
        foregroundLayer.fillColor = UIColor.clear.cgColor
        foregroundLayer.strokeColor = UIColor.red.cgColor
        foregroundLayer.strokeEnd = 0
        
        self.layer.addSublayer(foregroundLayer)
        
    }
    
    private func makeLabel(withText text: String) -> UILabel {
        let label = UILabel(frame: CGRect(x: 0, y: 0, width: 0, height: 0))
        label.text = text
        label.font = UIFont.boldSystemFont(ofSize: labelSize)
        label.sizeToFit()
        label.center = pathCenter
        return label
    }
    
    private func configLabel(){
        label.sizeToFit()
        label.center = pathCenter
    }
    
    private func setForegroundLayerColorForSafePercent(){
        if Int(label.text!)! >= self.safePercent {
            self.foregroundLayer.strokeColor = UIColor(red: 008/255, green: 046/255, blue: 109/255, alpha: 1).cgColor
        } else {
            self.foregroundLayer.strokeColor = UIColor.red.cgColor
        }
    }
    
    private func setupView() {
        makeBar()
        self.addSubview(label)
    }
    
    //Layout Sublayers
    
    private var layoutDone = false
    override func layoutSublayers(of layer: CALayer) {
        if !layoutDone {
            let tempText = label.text
            setupView()
            label.text = tempText
            layoutDone = true
        }
    }
    
}
