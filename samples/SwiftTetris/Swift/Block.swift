
//  Block.swift
//  Created by Justin Graham on 6/25/14.

import Foundation

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
    
    // this function is only ever called once the block has stopped
    // so we only need to deal with the current rotation
    func removeCell(cell : FixedPoint)
    {
        if _board
        {
            var index = _board!.cellToIndex(cell)
            var piece = _board!._map[index].piece
            if piece
            {
                removeChild(piece)
                _board!._map[index] = Board.MapEntry()
                //Debug.getInstance.log("removing cell \(cell.x), \(cell.y)")
            }
        }
    }
}
