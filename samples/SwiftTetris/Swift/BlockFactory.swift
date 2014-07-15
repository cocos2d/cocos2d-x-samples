
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

//  BlockFactory.swift
//  Created by Justin Graham on 6/20/14.

class BlockFactory
{
    let NUM_ROWS : Int = 4
    let NUM_COLS : Int = 4
    let NUM_SHAPES : Int = 7
    
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
      [FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:-2)],
      [FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:0),   FixedPoint(x:1,y:0)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:0,y:-2)] ],
    /*T*/
    [ [FixedPoint(x:-2,y:0),  FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1)],
      [FixedPoint(x:0,y:1),   FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:-1,y:0)],
      [FixedPoint(x:0,y:0),   FixedPoint(x:-1,y:-1), FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2), FixedPoint(x:0,y:-1)] ],
    /*Z*/
    [ [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2)],
      [FixedPoint(x:-1,y:0),  FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:1,y:-1)],
      [FixedPoint(x:0,y:0),   FixedPoint(x:0,y:-1),  FixedPoint(x:-1,y:-1), FixedPoint(x:-1,y:-2)] ]
    ]
    
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
        var block = loadColoredBlock(0)
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
        return createBlockFromData(index)
    }
    
    func createRandomBlock() -> Block
    {
        var r = Double(rand())
        var m = Double(RAND_MAX)
        var c = Double(NUM_SHAPES)
        var i = r * c / m
        var index : Int = Int(i)
        return createBlockFromData(index)
    }
    
    func createBlockFromData(index : Int) -> Block
    {
        var blockDescription = BLOCKS[index]
        
        var block = Block()
        block._board = _board!
        block.type = index
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
                var c = loadColoredBlock(index)
                
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
    
    func loadColoredBlock(index : Int) ->Sprite
    {
        var sprite = Sprite.create(Names[index])
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


