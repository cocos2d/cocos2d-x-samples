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
    var _magnitude : Float = 0.0
    var _direction = CGPointMake(1,1)
    
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

        var label = Label.createWithTTF("Play", "edunline.ttf", 180)
        label.setAnchorPoint(CGPointMake(0.5, 0.5))
        label.setPosition(CGPointMake(0.5 * size.width, 700.0))
        var black = Color4B.createWithBlack() as Color4B // wtf?
        addChild(label)

        var t : Float = 2
        var action = ClosureAction.createWithDuration(t, { (time : Float) -> Void in
            self._magnitude = time
            var offset = self._direction
            offset.x *= CGFloat(self._magnitude)
            offset.y *= CGFloat(self._magnitude)
            label.enableShadow(black, CGSizeMake(offset.x, offset.y), 50)
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
