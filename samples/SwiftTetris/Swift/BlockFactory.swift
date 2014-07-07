
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

    /*
    
   -2  -1   0   1    2
    2---+---+---+---+
    |
    1---+---+---+---+
    |
    0---+---+---+---+
    |
   -1---+---+---+---+
    |
   -2---+---+---+---+

    let ? : Array<FixedPoint> = [FixedPoint(x:,y:), FixedPoint(x:,y:), FixedPoint(x:,y:), FixedPoint(x:,y:)]

    */
    
    let BLOCKS = [
    /*I*/
    [ [FixedPoint(x:0,y:1),   FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:-2)],
      [FixedPoint(x:-2,y:-1), FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:-1,y:1),  FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2)],
      [FixedPoint(x:-2,y:0),  FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:1,y:0)] ],
    /*J*/
    [ [FixedPoint(x:0,y:1),   FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:-1,y:-1)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2)],
      [FixedPoint(x:-2,y:0),  FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1)] ],
    /*L*/
    [ [FixedPoint(x:-1,y:1),  FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1)],
      [FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:1,y:0)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:-2)],
      [FixedPoint(x:-2,y:-1), FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:0)] ],
    /*O*/
    [ [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1)] ],
    /*S*/
    [ [FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:0),   FixedPoint(x:1,y:0)],
      [FixedPoint(x:-1,y:1),  FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:-2)],
      [FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:0),   FixedPoint(x:1,y:0)],
      [FixedPoint(x:-1,y:1),  FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:-2)] ],
    /*T*/
    [ [FixedPoint(x:-2,y:0),  FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1)],
      [FixedPoint(x:0,y:1),   FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:-1,y:0)],
      [FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2), FixedPoint(x:0,y:-1)] ],
    /*Z*/
    [ [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:0,y:1),   FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:0,y:1),   FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2)] ] ]
    
    //typealias PieceDescription = Array<FixedPoint>
    //typealias BlockDescription = Array<PieceDescription>

    enum PieceName : Int
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
    
    var _board : Board? = nil
    
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
    
    func setBoard(board : Board)
    {
        _board = board
    }
    
    func createColoredBlock(color : Color) -> Node
    {
        var index = color.toRaw()
        return createBlockFromData(BLOCKS[index], color: color)
    }
    
    func createRandomBlock() -> Block
    {
        var r = Double(rand())
        var m = Double(RAND_MAX)
        var c = Double(NUM_SHAPES)
        var i = r * c / m
        var index : Int = Int(i)
        return createBlockFromData(BLOCKS[index], color: Color.fromRaw(index)!)
    }
    
    func createBlockFromData(blockDescription : Array<Array<FixedPoint>>, color : Color) -> Block
    {
//        Debug.getInstance.log("createBlockFromData count \(blockDescription.count) : color \(color.toRaw())")
//        
//        for o in blockDescription
//        {
//            Debug.getInstance.log("   count \(o.count)")
//            for c in o
//            {
//                Debug.getInstance.log("  cell \(c.x), \(c.y)")
//            }
//        }
//
//        Debug.getInstance.log("DONE")
        
        var block = Block()
        block._board = _board!
        block.type = color.toRaw()
        block.setAnchorPoint(CGPointZero)
        
        for pieceDesc in blockDescription
        {
            var minx : Fixed = 10000
            var maxx : Fixed = 0
            var miny : Fixed = 10000
            var maxy : Fixed = 0
            
            var piece = Piece()
            piece._board = _board!
            piece.setAnchorPoint(CGPointZero)
            
            for cell in pieceDesc
            {
                var c = loadColoredBlock(color)
                
                var rpos = cell.x + 1
                var tpos = cell.y + 1
                
                minx = minx < cell.x ? minx : cell.x
                miny = miny < cell.y ? miny : cell.y
                maxx = maxx > rpos ? maxx : rpos
                maxy = maxy > tpos ? maxy : tpos
                
                c.setAnchorPoint(CGPointZero)
                piece.addChild(c)
                var x = CGFloat(cell.x) * _blockSize.width
                var y = CGFloat(cell.y) * _blockSize.height
                c.setPosition(CGPointMake(x, y))
                //Debug.getInstance.log("place cell \(x), \(y)")
            }
            
            //Debug.getInstance.log("dims \(maxx - minx), \(maxy - miny)")
            
            piece.setDimensions(FixedPoint(x:maxx - minx, y:maxy - miny),
                                bl: FixedPoint(x: minx, y: miny),
                                tr: FixedPoint(x: maxx, y: maxy))
            
            var contentWidth  = maxx - minx
            var contentHeight = maxy - miny
            
            //Debug.getInstance.log("min max \(minx), \(maxx) -> \(miny), \(maxy)")
            //Debug.getInstance.log("contentSize \(contentWidth), \(contentHeight)")
            
            var contentSize = CGSizeMake(CGFloat(contentWidth) * _blockSize.width, CGFloat(contentHeight) * _blockSize.height)
            piece.setContentSize(contentSize)

            block.rotations.append(piece)
        }

        // default to first piece
        block.addChild(block.rotations[0])
        
        //Debug.getInstance.log("done with block creation")
        
        return block
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


