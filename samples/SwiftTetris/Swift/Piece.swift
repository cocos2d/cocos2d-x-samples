
/****************************************************************************
Copyright (c) 2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

//  Piece.swift
//  Created by Justin Graham on 7/6/14.

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
        //Debug.getInstance.log("setPosition: \(pos.x), \(pos.y)")
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
