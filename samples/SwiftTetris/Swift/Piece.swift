//
//  Piece.swift
//  SwiftTetris
//
//  Created by Justin Graham on 7/6/14.
//
//

import Foundation

class Piece : Node
{
    var _board : Board? = nil
    var _position : FixedPoint = FixedPoint(x:0, y:0)
    var _dimensions : FixedPoint = FixedPoint(x:0, y:0)
    var _BL : FixedPoint = FixedPoint(x:0, y:0)
    var _TR : FixedPoint = FixedPoint(x:0, y:0)
    
    func setDimensions(size : FixedPoint, bl : FixedPoint, tr : FixedPoint)
    {
        _dimensions = size
        _BL = bl
        _TR = tr
    }
    
    func getDimensions() -> FixedPoint
    {
        return _dimensions
    }
    
    func BL() -> FixedPoint
    {
        return _BL
    }
    
    func TR() -> FixedPoint
    {
        return _TR
    }
    
    func getSize() -> CGSize
    {
        return getContentSize()
    }
    
    func setPos(position : FixedPoint)
    {
        _position = position
        var BS = BlockFactory.getInstance._blockSize
        var BL = _board!._cellBL
        BL.x *= Fixed(BS.width)
        BL.y *= Fixed(BS.height)
        var x = BS.width  * CGFloat(_position.x)
        var y = BS.height * CGFloat(_position.y)
        var pos : CGPoint = CGPointMake(CGFloat(BL.x) + x, CGFloat(BL.y) + y)
        Debug.getInstance.log("setPosition: \(pos.x), \(pos.y)")
        setPosition(pos)
    }
    
    func getPos() -> FixedPoint
    {
        return _position
    }
    
    func slotWidth() -> Fixed
    {
        return _TR.x - _BL.x
    }
    
    func slotHeight() -> Fixed
    {
        return _TR.y - _BL.y
    }
}
