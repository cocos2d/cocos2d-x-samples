//
//  SceneMenu.swift
//  swiftress
//
//  Created by Justin Graham on 6/27/14.
//
//

import Foundation

class SceneMenu : Scene
{
    var _extent : Float = 20
    var _magnitude : Float = 0
    var _direction = CGPointMake(0.8,-1)
    
    func startGame(touch : Touch!, event : Event!) -> Bool
    {
        var scene = SceneGame()
        var fade = TransitionFade.create(3, scene)
        Director.getInstance().replaceScene(fade)

        return true
    }
    
    override func onEnter()
    {
        var director = Director.getInstance()
        var size = director.getWinSize()
        
        var bg = Sprite.create("background.png")
        bg.setAnchorPoint(CGPointZero)
        addChild(bg)

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
        listener.onTouchBegan = startGame
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(listener, label)
        
        var accelerator = EventListenerAcceleration.create({ (acceleration : Acceleration?, event : Event?) -> Void in
            if acceleration
            {
                self._direction.x = CGFloat(acceleration!.x)
                self._direction.y = CGFloat(acceleration!.y)
                Debug.getInstance.log("direction \(self._direction.x), \(self._direction.y)")
            }
        })
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(accelerator, self)
    }
}
