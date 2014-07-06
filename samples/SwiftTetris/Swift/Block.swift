
//  Block.swift
//  Created by Justin Graham on 6/25/14.

import Foundation

class Block : Node
{
    var dimensions : CGSize = CGSizeZero
    var type : Int?
    
    func getOrigin() -> CGPoint
    {
        var s = getRotatedDimensions()
        if nil == s
        {
            Debug.getInstance.log("getRotatedDimensions returned nil :(")
            return CGPointZero
        }
        var size = s!
        size.width *= cellSize().width
        size.height *= cellSize().height
        var ap = getAnchorPoint()
        return CGPointMake(ap.x * size.width, ap.y * size.height)
    }
    
    func getSize() -> CGSize
    {
        return getContentSize()
    }
    
    func cellSize() -> CGSize
    {
        return getChildren()[0].getContentSize()
    }
    
    func setDimensions(size : CGSize)
    {
        dimensions = size
    }
    
    func getDimensions() -> CGSize
    {
        Debug.getInstance.log("getting dimensions \(dimensions.width), \(dimensions.height)")
        return dimensions
    }
    
    func getType() -> Int
    {
        return type!
    }
    
    func getRotatedDimensions() -> CGSize?
    {
        var rot : Int = Int(getRotation())
        rot = rot % 360
        
        switch (rot)
        {
        case 0:
            return dimensions
        case 180:
            return dimensions
        case 90:
            return CGSizeMake(dimensions.height, dimensions.width)
        case 270:
            return CGSizeMake(dimensions.height, dimensions.width)
        default:
            Debug.getInstance.log("invalid rotation for block \(rot)")
        }
        return nil
    }
    
    func adjustAnchorsForRotation()
    {
        var rot : Int = Int(getRotation())
        rot = rot % 360
        
        for a : AnyObject in getChildren()
        {
            var n = a as Node
        
            switch (rot)
            {
            case 0:
                n.setAnchorPoint(CGPointMake(0, 0))
            case 90:
                n.setAnchorPoint(CGPointMake(1, 0))
            case 180:
                n.setAnchorPoint(CGPointMake(1, 1))
            case 270:
                n.setAnchorPoint(CGPointMake(0, 1))
            default:
                Debug.getInstance.log("invalid rotation for block \(rot)")
            }
        }
    }
    
    func quantizeBlockForRotation()
    {
        var o = getOrigin()
Debug.getInstance.log("origin \(o.x), \(o.y)")
        var s = getSize()
        var l = cellSize().width  + o.x
        var b = cellSize().height + o.y
        
        var pos = getPosition()
Debug.getInstance.log("old position \(pos.x), \(pos.y)")
        
        var slotx = (Int(pos.x) - Int(l)) / Int(cellSize().width)
        var sloty = (Int(pos.y) - Int(b)) / Int(cellSize().height)

Debug.getInstance.log("cell \(slotx), \(sloty)")
        
        var x = l + CGFloat(slotx) * cellSize().width
        var y = b + CGFloat(sloty) * cellSize().height
Debug.getInstance.log("new position \(x), \(y)")
        
        setPosition(CGPointMake(CGFloat(x), CGFloat(y)))
        adjustAnchorsForRotation()
    }
    
    func getCells() -> Array<Point>
    {
        var cells : Array<Point> = []
        var children = getChildren()
        for o : AnyObject in children
        {
            var node = o as Node
            var position = node.convertToWorldSpace(CGPointZero)
            var p = Board.getInstance.convertWorldPositionToCell(position)
            cells.append(p)
        }
        return cells
    }
    
    func addToMap()
    {
        var cells = getCells()
        for c in cells
        {
            Board.getInstance.addToMap(self, cell: c)
        }
    }
    
    func removeFromMap()
    {
        var cells = getCells()
        for c in cells
        {
            Board.getInstance.removeFromMap(self, cell: c)
        }
    }
}
