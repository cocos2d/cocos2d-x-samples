//
//  start.swift
//  swiftress
//
//  Created by Justin Graham on 6/20/14.
//
//

import Foundation

class SceneGame : Scene
{
    var _board : Board = Board()
    var _level : Int = 1
    
    override func onEnter()
    {
        var sprite = Sprite.create("background.png")
        sprite.setAnchorPoint(CGPointZero)
        self.addChild(sprite)

        _board = Board()
        _board._level = _level
        addChild(_board)
        _board.start()
    }
    
    override func onExit()
    {
        removeAllChildren()
    }
    
    func nextLevel()
    {
        var fadeout = ClosureAction.createWithDuration(2, { (time : Float) -> Void in
            self._board.setOpacity((1 - time) * 255.0)
        })
        var remove = ClosureAction.createWithDuration(0, { (time : Float) -> Void in
            self._board.removeFromParentAndCleanup(true)
        })
        var add = ClosureAction.createWithDuration(0, { (time : Float) -> Void in
            self._board = Board()
            self._board._level = ++self._level
            self.addChild(self._board)
            self._board.start()
        })
        var fadein = ClosureAction.createWithDuration(2, { (time : Float) -> Void in
            self._board.setOpacity(time * 255.0)
        })
        var sequence = fadeout + remove + add + fadein
        runAction(sequence)
    }
}
