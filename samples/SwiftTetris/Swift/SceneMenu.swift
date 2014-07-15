
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

//  SceneMenu.swift
//  Created by Justin Graham on 6/27/14.

class SceneMenu : Scene
{
    var _extent : Float = 20
    var _magnitude : Float = 0
    var _direction = CGPointMake(0.8,-1)
    
    func startGame()
    {
        var scene = SceneGame()
        var fade = TransitionFade.create(3, scene)
        Director.getInstance().replaceScene(fade)
    }
    
    override func onEnter()
    {
        var director = Director.getInstance()
        var size = director.getWinSize()
        
        var bg = Sprite.create("background.png")
        bg.setAnchorPoint(CGPointZero)
        addChild(bg)

        AudioEngine.getInstance().playBackgroundMusic("tetris.mp3", true)
        AudioEngine.getInstance().setBackgroundMusicVolume(0.2)

        var label = Label.createWithTTF("Play", "Arcade.ttf", 180)
        label.setAnchorPoint(CGPointMake(0.5, 0.5))
        label.setPosition(CGPointMake(0.5 * size.width, 700.0))
        var black = Color4B.createWithBlack() as Color4B // wtf?
        var grey = Color4B.createWithRGBA(128, 128, 128, 128) as Color4B
        var blue = Color4B.createWithRGBA(88, 157, 214, 255) as Color4B
        label.setTextColor(blue)
        addChild(label)

        var t : Float = 2
        var action = ClosureAction.createWithDuration(t, { (time : Float) -> Void in
            self._magnitude = time * self._extent
            var offset = self._direction
            offset.x *= CGFloat(self._magnitude)
            offset.y *= CGFloat(self._magnitude)
            grey.a = UInt8(128.0 * time)
            label.enableShadow(grey, CGSizeMake(offset.x, offset.y), 50)
        })        
        label.runAction(action)
            
        var listener = EventListenerTouchOneByOne.create()
        listener.onTouchBegan = { (Touch, Event) -> Bool in self.startGame() ; return true }
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(listener, label)
        
        var keybdListener = EventListenerKeyboard()
        keybdListener.onKeyPressed = { (KeyCode, Event) in self.startGame() }
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(keybdListener, self)
    }
    
    override func onExit()
    {
        Director.getInstance().eventDispatcher.removeEventListenersForTarget(self, true)
    }
}
