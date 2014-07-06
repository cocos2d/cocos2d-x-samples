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
        Director.getInstance().pushScene(fade)

        return true
    }
    
    override func onEnter()
    {
        var director = Director.getInstance()
        var size = director.getWinSize()
        
        var sprite = Sprite.create("startbutton.png")
        sprite.setPosition(CGPointMake(size.width / 2, size.height / 2))
        self.addChild(sprite)
    
        var listener = EventListenerTouchOneByOne()
        listener.onTouchBegan = startGame
        director.eventDispatcher.addEventListenerWithSceneGraphPriority(listener, sprite)
    }    
}
