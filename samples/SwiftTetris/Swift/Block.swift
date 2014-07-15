
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

//  Block.swift
//  Created by Justin Graham on 6/25/14.

class Block : Node
{
    var _board : Board? = nil
    var rotations : [Piece] = []
    var rotation : Int = 0
    var position : FixedPoint = FixedPoint(x: 0,y: 0)
    var type : Int?
    
    func getPiece() -> Piece
    {
        return rotations[rotation]
    }
    
    func getPieceDescription() -> Array<FixedPoint>
    {
        let blockFactory = BlockFactory.getInstance
        let blocks = blockFactory.BLOCKS
        var blockDesc = blocks[type!]
        return blockDesc[rotation]
    }
    
    func getType() -> Int
    {
        return type!
    }
    
    func getCells() -> Array<FixedPoint>
    {
        var pieceDesc = getPieceDescription()
        var pos = getPos()
        var cells : Array<FixedPoint> = []
        for c in pieceDesc
        {
            var cc = FixedPoint(x:pos.x + c.x, y:pos.y + c.y)
            //Debug.getInstance.log("appending \(cc.x), \(cc.y)")
            cells.append(cc)
        }
        return cells
    }
    
    func addToMap()
    {
        var cells = getCells()
        for c in cells
        {
            _board!.addToMap(self, cell: c)
        }
    }
    
    func removeFromMap()
    {
        var cells = getCells()
        for c in cells
        {
            _board!.removeFromMap(self, cell: c)
        }
    }
    
    func setRot(rot : Int)
    {
        if rot != rotation
        {
            removeAllChildren()
            rotation = rot
            //Debug.getInstance.log("Rotation set to \(rotation)")
            addChild(rotations[rotation])
        }
    }
    
    func getRot() -> Int
    {
        return rotation
    }
    
    func setPos(pos : FixedPoint)
    {
        if position.x != pos.x || position.y != pos.y
        {
            position = pos
            for p in rotations
            {
                p.setPos(pos)
            }
        }
    }
    
    func getPos() -> FixedPoint
    {
        return position
    }
}
