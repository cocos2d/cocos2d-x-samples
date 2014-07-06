
//  BlockFactory.swift
//  Created by Justin Graham on 6/20/14.

import Foundation

// blocks
// all shapes occupy the maximum space of 4x4
// binary encoding for shapes 32bits required for a single shape
//
// I   1000,1000,1000,1000 = 8,8,8,8 red
// J   0000,0000,1110,0010 = 0,0,E,2 yellow
// L   0000,1000,1000,1100 = 0,8,8,C magenta
// O   0000,0000,1100,1100 = 0,0,C,C blue
// S   0000,0000,0110,1100 = 0,0,6,C cyan
// T   0000,0000,1110,0100 = 0,0,E,4 green
// Z   0000,0000,1100,0110 = 0,0,C,6 orange

class BlockFactory
{
    let NUM_ROWS : Int = 4
    let NUM_COLS : Int = 4
    
    let NUM_SHAPES : Int = 7
    
    let MASKS : Int[] =
                        [0x08080808,
                         0x00000E02,
                         0x0008080C,
                         0x00000C0C,
                         0x0000060C, //
                         0x00000E04,
                         0x00000C06] //
    
    enum Piece : Int
    {
        case I = 0
        case J
        case L
        case O
        case S
        case T
        case Z
        case E
    }
    
    enum Color : Int
    {
        case Red = 0
        case Yellow
        case Magenta
        case Blue
        case Cyan
        case Lime
        case Orange
        case Grey
        case MaxColors
    }
    
    let Names = ["red.png", "yellow.png", "magenta.png", "blue.png", "cyan.png", "green.png", "orange.png", "grey.png"]
    
    var _blockSize : CGSize = CGSizeZero
    
    init()
    {
        var block = loadColoredBlock(Color.Red)
        _blockSize = block.getContentSize()
    }
    
    class var getInstance : BlockFactory
    {
        struct Singleton
        {
            static let instance = BlockFactory()
        }
        return Singleton.instance
    }
    
    func createColoredBlock(color : Color) -> Node
    {
        var index = color.toRaw()
        var mask = MASKS[index]
        return createBlockFromBitMask(mask, color: color)
    }
    
    func createRandomBlock() -> Block
    {
        var r = Double(rand())
        var m = Double(RAND_MAX)
        var c = Double(NUM_SHAPES)
        var i = r * c / m
        var index : Int = Int(i)
        var mask : Int = MASKS[index]
        return createBlockFromBitMask(mask, color : Color.fromRaw(index)!)
    }
    
    func createBlockFromBitMask(mask : Int, color : Color) -> Block
    {
        var parent = Block()
        parent.type = color.toRaw()
        parent.setAnchorPoint(CGPointMake(0.5, 0.5))
        
        var m = 0xFF000000
        
        let cols : CGFloat = CGFloat(NUM_COLS - 1)
        let rows : CGFloat = CGFloat(NUM_ROWS - 1)
        
        // where are constants FLT_MIN and FLT_MAX
        var minx : CGFloat = 10000
        var maxx : CGFloat = 0
        var miny : CGFloat = 10000
        var maxy : CGFloat = 0
        
        var ypos : CGFloat = 0
        
        for y in 0...3 {
            
            var xpos : CGFloat = 0

            // grab bytes from left to right
            var byte : Int = ((mask & m) >> (8 * (3 - y)) & 0xFF) ;
            m >>= 8
            
            // skip leading rows of blanks to align block to bottom of 4x4
            if 0 == byte
            {
                continue
            }
            
            for x in 0...3 {
                
                // read bits from left to right
                var r = byte & (1 << (3 - x))
                if (r > 0)
                {
                    var block = loadColoredBlock(color)
                    
                    var rpos = xpos + _blockSize.width
                    var tpos = ypos + _blockSize.height
                    
                    minx = minx < xpos ? minx : xpos
                    maxx = maxx > rpos ? maxx : rpos
                    miny = miny < ypos ? miny : ypos
                    maxy = maxy > tpos ? maxy : tpos
                    
                    block.setPosition(CGPointMake(xpos, ypos))
                    block.setAnchorPoint(CGPointZero)
                    
                    parent.addChild(block)
                }
                
                xpos += _blockSize.width
            }

            ypos += _blockSize.height
        }
        
        var contentWidth  = maxx - minx
        var contentHeight = maxy - miny
        
        Debug.getInstance.log("min max \(minx), \(maxx) -> \(miny), \(maxy)")
        Debug.getInstance.log("contentSize \(contentWidth), \(contentHeight)")
        
        var contentSize = CGSizeMake(contentWidth, contentHeight)
    
        var dimWidth  = Int(contentWidth) / Int(parent.cellSize().width)
        var dimHeight = Int(contentHeight) / Int(parent.cellSize().height)
        
        Debug.getInstance.log("Dims \(dimWidth), \(dimHeight)")
        
        parent.setDimensions(CGSizeMake(CGFloat(dimWidth), CGFloat(dimHeight)))
        
        parent.setAnchorPoint(CGPointZero)
        parent.setContentSize(contentSize)
        
        return parent;
    }
    
    func loadBlock(name : String) -> Sprite
    {
        return Sprite.create(name)
    }
    
    func loadColoredBlock(color : Color) ->Sprite
    {
        var sprite = Sprite.create(Names[Int(color.toRaw())])
        sprite.setAnchorPoint(CGPointMake(0, 0))
        return sprite;
    }
    
    func loadRandomBlock() -> Sprite
    {
        var r = Double(rand())
        var m = Double(RAND_MAX)
        var c = 8.0
        var color = r * c / m
        return loadBlock(Names[Int(color)])
    }
}


