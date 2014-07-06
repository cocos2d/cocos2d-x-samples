//
//  Board.swift
//  swiftress
//
//  Created by Justin Graham on 6/27/14.
//
//

import Foundation

//
// Constants
//
let COLUMNS : Int = 10
let ROWS : Int = 17

class Board : Node
{
    struct MapEntry
    {
        var block : Block? = nil
    }
    
    var _map : MapEntry[] = []

    var _accelerometer : EventListenerAcceleration?
    var _pieces    : Block[] = []
    var _currentBlock : Block?

    var _lastDropSpeed : Float = 0.5
    var _dropSpeed : Float = 0.5
    var _time      : Float = 0
    
    var _gameDelay : Float = 1
    var _gameTime : Float = 0
    var _countDown : Int = 3
    
    var _origin : CGPoint = CGPointZero
    var _size : CGSize = CGSizeZero
    var _blockSize : CGSize = CGSizeZero
    
    var _cellBL : Point = Point(v: 0, h: 0)
    var _cellTR : Point = Point(v: 0, h: 0)
    
    var _board : Node = Node()
    
    var _paused : Bool = false
    
    enum State
    {
        case COUNTDOWN // Beginning state
        case IDLE // enter drop state
        case DROP // spawn a single random piece
        case PLAY // user interaction occurs until the piece has landed
        case DEAD // end case when a piece cannot be dropped
    }
    var _state : State = .COUNTDOWN
    
    //
    // Methods
    //
    
    class var getInstance : Board
    {
        struct Singleton
        {
            static let instance = Board()
        }
        return Singleton.instance
    }
    
    init()
    {
        super.init()
        
        var block = BlockFactory.getInstance.loadColoredBlock(BlockFactory.Color.Grey)
        var blockSize = block.getContentSize()
        _blockSize = blockSize
        
        var listener = EventListenerTouchOneByOne()
        listener.onTouchBegan = touchBoard
        
        var director = Director.getInstance()
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(listener, _board)

        director.console.addCommand("dumpMap", "dumps the map to console", commandDumpMap)
    }
    
    func commandDumpMap(i : CInt, s : String!)
    {
        Debug.getInstance.log("")

        var t = "IJLOSTZE"
        var types = Array(t)
        var line : String
        for r in 0...ROWS-1
        {
            line = ""
            
            for c in 0...COLUMNS-1
            {
                var index = cellToIndex(Point(v : CShort((ROWS-1) - r), h : CShort(c)))
                var block = _map[index].block
                if !block
                {
                    line += "_"
                }
                else
                {
                    var type = block!.getType()
                    var s = String(types[type])
                    line += s
                }
            }
            
            Debug.getInstance.log(line)
        }
        
        Debug.getInstance.log("")
    }

    func togglePause()
    {
        _paused = !_paused
    }
    
    func bottomLeftInPoints() -> CGPoint
    {
        var l = CGFloat(_cellBL.h) * _blockSize.width
        var b = CGFloat(_cellBL.v) * _blockSize.height
        return CGPointMake(l, b)
    }
    
    func topRightInPoints() -> CGPoint
    {
        var t = CGFloat(_cellTR.h) * _blockSize.width
        var r = CGFloat(_cellTR.v) * _blockSize.height
        return CGPointMake(t, r)
    }
    
    func touchBoard(touch : Touch!, event : Event!) -> Bool
    {
        if _state != .PLAY
        {
            return false;
        }
        
        if pickBlockFromLocation(touch.getLocation())
        {
            return false;
        }
        
        // the board has been touched
        var point = touch.getLocation()
        var halfway = _size.width / 2
        
        if point.x <= halfway
        {
            moveCurrentBlockLeft()
        }
        else
        {
            moveCurrentBlockRight()
        }
        
        return true
    }
    
    func gameOver()
    {
        self.unscheduleUpdate()
        _pieces = []
        _currentBlock = nil
        _map = []
        _board.removeFromParentAndCleanup(true)
        Director.getInstance().popScene()
    }
    
    func fillBackground()
    {
        var director = Director.getInstance()
        var size = director.getWinSize()
        
        var across : Int = Int(size.width  / _blockSize.width)
        var down : Int   = Int(size.height / _blockSize.height)
        
        var l = (across - COLUMNS) / 2
        var r = l + COLUMNS - 1
        var b = 1
        var t = b + ROWS - 1
        
        _cellBL = Point(v: CShort(b), h: CShort(l))
        _cellTR = Point(v: CShort(t), h: CShort(r))
        
        Debug.getInstance.log("across \(across) down \(down) l \(l) r \(r) t \(t) b \(b)")
        
        for d in 0...down - 1
        {
            for a in 0...across - 1
            {
                if d >= b && d <= t && a >= l && a <= r
                {
                    continue
                }
                
                var block = BlockFactory.getInstance.loadColoredBlock(BlockFactory.Color.Grey)
                block.setPosition(CFloat(a * Int(_blockSize.width)), CFloat(d * Int(_blockSize.height)))
                _board.addChild(block)
            }
        }
        
        var backWidth  = _blockSize.width  * CGFloat(across)
        var backHeight = _blockSize.height * CGFloat(down)
        var left = (size.width - backWidth) / 2.0
        var bott = (size.height - backHeight) / 2.0
        _board.setPosition(CGPointMake(left, bott))
        
        _origin = CGPointMake(left, bott)
        _size = CGSizeMake(CGFloat(r - l) * _blockSize.width, CGFloat(t - b) * _blockSize.height)
        
        Debug.getInstance.log("origin \(_origin) size \(_size)")
        
        self.addChild(_board)
    }

    func convertWorldPositionToCell(pos : CGPoint) -> Point
    {
        var cx : Int = Int((pos.x - _origin.x) / _blockSize.width) - Int(_cellBL.h)
        var cy : Int = Int((pos.y - _origin.y) / _blockSize.height) - Int(_cellBL.v)
        //Debug.getInstance.log("converting \(pos.x - _origin.x), \(pos.y - _origin.y) to \(cx), \(cy)")
        return Point(v: CShort(cy), h: CShort(cx))
    }
    
    func convertCellToWorldPosition(cell : Point) -> CGPoint
    {
        var px : CGFloat = (CGFloat(cell.h) * _blockSize.width) + _origin.x
        var py : CGFloat = (CGFloat(cell.v) * _blockSize.height) + _origin.y
        return CGPointMake(px, py)
    }
    
    func start()
    {
        for i in 0...COLUMNS * ROWS - 1
        {
            _map.append(MapEntry())
        }
        Debug.getInstance.log("map size \(_map.count)")
        
        var director = Director.getInstance()
        var size = director.getWinSize()
        
        self.fillBackground()
        self.scheduleUpdate(update)
        
        var label = Label.createWithSystemFont("SwiftresS", "MarkerFelt-Wide", 80)
        label.setPosition(CGPointMake(size.width / 2, 1050))
        self.addChild(label)
        
        var bounce = ClosureAction.createWithDuration(2, { (time : Float) -> Void in
            label.setScale(time)
            })
        label.runAction(bounce)
        
        self._accelerometer = EventListenerAcceleration.create { (acceleration : Acceleration!, event : Event!) in
            Debug.getInstance.log("acceleration \(acceleration.x) \(acceleration.y) \(acceleration.z)")
        }
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(self._accelerometer, self)
    }
    
    func startCountDown()
    {
        if _countDown < 0
        {
            return
        }
        
        var director = Director.getInstance()
        var size = director.getWinSize()
        
        var text = _countDown > 0 ? "\(_countDown)" : ""
        var label = Label.createWithSystemFont(text, "MarkerFelt-Wide", 120)
        label.setPosition(CGPointMake(size.width / 2, size.height / 2))
        self.addChild(label)
        
        var actions : Array<Action> = []
        
        actions.append(ClosureAction.createWithDuration(_gameDelay, { (time : Float) -> Void in
            label.setScale(1 / time)
            }))
        
        actions.append(ClosureAction.createWithDuration(_gameDelay, { (time : Float) -> Void in
            label.removeFromParentAndCleanup(true)
            }))
        
        var sequence = ActionSequence.create(actions)
        
        label.runAction(sequence)
        
        --_countDown
    }
    
    func cellToIndex(cell : Point) -> Int
    {
        if Int(cell.h) >= COLUMNS || Int(cell.v) >= ROWS
        {
            //Debug.getInstance.log("invalid cell \(cell.h), \(cell.v) clamping")
        }
        var x = Int(cell.h) >= COLUMNS ? COLUMNS - 1 : Int(cell.h)
        var y = Int(cell.v) >= ROWS    ? ROWS - 1    : Int(cell.v)
        return Int(y * COLUMNS + x)
    }
    
    func canPlaceBlock(block : Block) -> Bool
    {
        var cells : Array<Point> = block.getCells()
        for p in cells
        {
            //Debug.getInstance.log("checking cell \(p.h), \(p.v) against \(_cellBL.h), \(_cellTR.h)")
            if p.h < 0 || p.h >= CShort(COLUMNS)
            {
                return false;
            }
            
            var index = cellToIndex(p)
            if index >= _map.count
            {
                Debug.getInstance.log("canPlaceBlock: invalid index \(index)")
                return false
            }
            if nil != _map[index].block
            {
                Debug.getInstance.log("cell \(p.h), \(p.v) is occupied")
                return false
            }
        }
        return true;
    }
    
    func spawnBlock() -> Bool
    {
        var block = BlockFactory.getInstance.createRandomBlock()
        placeBlockInPlayArea(&block)
        
        if false == canPlaceBlock(block)
        {
            Debug.getInstance.log("DEAD")
            _state = .DEAD
            return false
        }
        
        block.addToMap()

        var touchListener = EventListenerTouchOneByOne()
        var keybdListener = EventListenerKeyboard()
        
        touchListener.onTouchBegan = rotatePiece
        keybdListener.onKeyPressed = keyboardPressed
        keybdListener.onKeyReleased = keyboardReleased
        
        var director = Director.getInstance()
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(touchListener, block)
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(keybdListener, block)
        
        return true
    }
    
    func cleanupCurrentBlock()
    {
        if _currentBlock
        {
            Director.getInstance().eventDispatcher.removeEventListenersForTarget(_currentBlock, false)
        }
    }
    
    func placeBlockInPlayArea(inout block : Block)
    {
        var s = block.getSize()
        var o = block.getOrigin()
        var d = block.getDimensions()
        
        var bl = bottomLeftInPoints()
        var tr = topRightInPoints()
        
        Debug.getInstance.log("LB in points \(bl.x), \(bl.y)")
        Debug.getInstance.log("RT in points \(tr.x), \(tr.y)")
        Debug.getInstance.log("size         \(s.width), \(s.height)")
        Debug.getInstance.log("dimensions   \(d.width), \(d.height)")
        Debug.getInstance.log("board size   \(_size.width), \(_size.height)")
        
        var t = tr.y - s.height
        
        var slot = Int(Utilities.random(Double(0), Double(COLUMNS - Int(d.width))))
        
        Debug.getInstance.log("slot         \(slot)")
        
        var x = bl.x + CGFloat(slot) * block.cellSize().width + o.x
        var y = t + o.y
        
        Debug.getInstance.log("x,y          \(x), \(y)")
        
        block.setPosition(CGPointMake(CGFloat(x), CGFloat(y)))
        
        _board.addChild(block)
        _pieces.append(block)
        _currentBlock = block
        
        //Debug.getInstance.log("placed new block at \(x), \(y)")
    }
    
    func moveCurrentBlock()
    {
        var block = _currentBlock!
        var wp = block.convertToWorldSpace(CGPointZero)
        var cell = convertWorldPositionToCell(wp)
        //Debug.getInstance.log("piece at \(cell.h), \(cell.v)")
        
        if cell.v == 0
        {
            Debug.getInstance.log("piece has reached \(cell.h), \(cell.v) setting state to DROP")
            _state = .IDLE
            return
        }
        
        block.removeFromMap()
        var pos = block.getPosition()
        var newPos = pos
        newPos.y -= _blockSize.height
        block.setPosition(newPos)

        if !canPlaceBlock(block)
        {
            block.setPosition(pos)
            _state = .IDLE
        }
        block.addToMap()
    }
    
    func moveCurrentBlockLeft()
    {
        var block = _currentBlock!
        block.removeFromMap()
        var pos = block.getPosition()
        var newPos = pos
        newPos.x -= _blockSize.width
        Debug.getInstance.log("moveCurrentBlockLeft: moving block from \(pos.x), \(pos.y) to \(newPos.x), \(newPos.y)")
        block.setPosition(newPos)
        if !canPlaceBlock(block)
        {
            block.setPosition(pos)
        }
        block.addToMap()
    }
    
    func moveCurrentBlockRight()
    {
        var block = _currentBlock!
        block.removeFromMap()
        var pos = block.getPosition()
        var newPos = pos
        newPos.x += _blockSize.width
        Debug.getInstance.log("moveCurrentBlockRight: moving block from \(pos.x), \(pos.y) to \(newPos.x), \(newPos.y)")
        block.setPosition(newPos)
        if !canPlaceBlock(block)
        {
            block.setPosition(pos)
        }
        block.addToMap()
    }
    
    func pickBlockFromLocation(location : CGPoint) -> Block?
    {
        for block in _pieces
        {
            for object : AnyObject in block.getChildren()
            {
                var cell = object as Sprite
                var size = cell.getContentSize()
                var np = cell.convertToNodeSpace(location)
                if np.x >= 0 && np.y >= 0 && np.x < size.width && np.y < size.height
                {
                    return block;
                }
            }
        }
        return nil
    }
    
    func adjustBlockForBounds(block : Block)
    {
        var cells : Array<Point> = block.getCells()
        var l : CShort = 10000
        var r : CShort = 0
        
        for p in cells
        {
            l = p.h < l ? p.h : l
            r = p.h > r ? p.h : r
        }
        
        Debug.getInstance.log("extents l \(l) r \(r)")
        
        var adjust : CGFloat = 0
        if (l < 0)
        {
            adjust = -CGFloat(l) * _blockSize.width
        }
        else if (r >= CShort(COLUMNS-1))
        {
            adjust = (CGFloat(COLUMNS-1) - CGFloat(r)) * _blockSize.width
        }
        
        Debug.getInstance.log("adjusting block by \(adjust)")
        
        var pos = block.getPosition()
        pos.x += adjust
        block.setPosition(pos)
    }
    
    func rotatePiece(touch : Touch!, event : Event!) -> Bool
    {        
        let block = _currentBlock
        if !block
        {
            return false
        }

        var b = block!
        var rotation = b.getRotation()
        var position = b.getPosition()
        
        b.removeFromMap()
        
        rotation += 90
        rotation = rotation % 360
        b.setRotation(rotation)
        b.quantizeBlockForRotation()
        
        adjustBlockForBounds(b)
        
        if !canPlaceBlock(b)
        {
            b.setPosition(position)
            b.setRotation(rotation)
        }
        
        var cells = b.getCells()
        for p in cells
        {
            Debug.getInstance.log("rotated cell \(p.h), \(p.v)")
        }
        
        b.addToMap()
        
        return true
    }
    
    func keyboardReleased(keycode : KeyCode, event : Event!)
    {
        switch keycode
        {
        case .CodeDOWN_ARROW:
            _dropSpeed = _lastDropSpeed
        
        default:
            Debug.getInstance.log("invalid key")
        }
    }
    
    func keyboardPressed(keycode : KeyCode, event : Event!)
    {
        switch keycode
        {
        case .CodeP:
            togglePause()
            
        case .CodeLEFT_ARROW:
            moveCurrentBlockLeft()
            
        case .CodeRIGHT_ARROW:
            moveCurrentBlockRight()
            
        case .CodeDOWN_ARROW:
            _lastDropSpeed = _dropSpeed
            _dropSpeed = 0.1
            
        case .CodeSPACE:
            rotatePiece(nil, event: event)
            
        default:
            Debug.getInstance.log("invalid key")
        }
    }
    
    func addToMap(block : Block, cell : Point) -> Bool
    {
        var index = cellToIndex(cell)
        if index >= _map.count
        {
            Debug.getInstance.log("addToMap: invalid index \(index) count \(_map.count)")
            return false
        }
        if _map[index].block != nil
        {
            Debug.getInstance.log("addToMap: error cell \(cell.h), \(cell.v) is already occupied")
            return false;
        }
        _map[index].block = block
        return true
    }
    
    func removeFromMap(block : Block, cell : Point) -> Bool
    {
        var index = cellToIndex(cell)
        if index >= _map.count
        {
            Debug.getInstance.log("removeFromMap: invalid index \(index) count \(_map.count)")
            return false
        }
        if _map[index].block != block
        {
            Debug.getInstance.log("removeFromMap: cell \(cell.h), \(cell.v) doesn't belong to block")
            return false
        }
        _map[index].block = nil
        return true
    }

    func removeRow(row : Int)
    {
        Debug.getInstance.log("Removing row \(row)")
        
        for c in 0...COLUMNS
        {
            var index = cellToIndex(Point(v : CShort(row), h : CShort(c)))
            var block = _map[index].block
            if block
            {

            }
        }
    }
    
    func checkAndRemoveRows()
    {
        var row = 0
        for r in 0...ROWS
        {
            Debug.getInstance.log("checking row \(row)")
            
            var count = 0
            
            for c in 0...COLUMNS - 1
            {
                var index = cellToIndex(Point(v : CShort(row), h : CShort(c)))
                if _map[index].block != nil
                {
                    ++count
                }
            }
            
            Debug.getInstance.log("column count for row \(row) is \(count)")
            
            if count == COLUMNS
            {
                removeRow(row)
            }
            else
            {
                ++row
            }
        }
    }
    
    func update(delta : Float)
    {
        switch _state
        {
        case .COUNTDOWN:
            if _countDown >= 0
            {
                _gameTime += delta
                while _gameTime >= _gameDelay
                {
                    _gameTime -= _gameDelay
                    startCountDown()
                }
                
                if _countDown >= 0
                {
                    return
                }
            }
            else
            {
                _state = .IDLE
            }
        
        case .IDLE:
            checkAndRemoveRows()
            _state = .DROP
            
        case .DROP:
            // remove previous block listeners
            cleanupCurrentBlock()
            if spawnBlock()
            {
                Debug.getInstance.log("setting state to PLAY")
                _state = .PLAY
            }
            
        case .PLAY:
            if _paused
            {
                return
            }
            
            _time += delta
            while _time >= _dropSpeed
            {
                _time -= _dropSpeed
                moveCurrentBlock()
            }
            
        case .DEAD:
            gameOver()
            
        default:
            Debug.getInstance.log("invalid state")
        }
    }
}
