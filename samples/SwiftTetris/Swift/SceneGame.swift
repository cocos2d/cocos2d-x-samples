
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

//  SceneGame.swift
//  Created by Justin Graham on 6/20/14.

import Foundation

class SceneGame : Scene
{
    var _board : Board = Board()
    var _level : Int = 1
    var _score : UInt = 0
    
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
    
    
    func nextLevel(score : UInt)
    {
        _score = score
        
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
            self._board.addScore(self._score)
        })
        var fadein = ClosureAction.createWithDuration(2, { (time : Float) -> Void in
            self._board.setOpacity(time * 255.0)
        })
        var sequence = fadeout + remove + add + fadein
        runAction(sequence)
    }
}
