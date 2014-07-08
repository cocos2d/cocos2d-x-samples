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
        label.enableShadow(black, CGSizeMake(20, -20), 50)
        addChild(label)

        var t : Float = 6
        var action = ClosureAction.createWithDuration(t, { (time : Float) -> Void in
            let offset:Float = 10.0
            label.enableShadow(black, CGSizeMake(CGFloat(time * offset), CGFloat(time * -offset)), 50)
        })        
        label.runAction(action)
            
        var listener = EventListenerTouchOneByOne()
        listener.onTouchBegan = startGame
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(listener, label)
    }
}
