//
//  SceneSplash.swift
//  swiftress
//
//  Created by Justin Graham on 6/27/14.
//
//

import Foundation

// displays the same image as the loading image,
// and immediately fades to the menu scene
class SceneSplash : Scene
{
    override func onEnter()
    {
        var director = Director.getInstance()
        
        var console = director.console
        console.listenOnTCP(44444)
        
        var sprite = Sprite.create("splash_640x1136.png")
        sprite.setAnchorPoint(CGPointZero)
        self.addChild(sprite)
        
        var scene = SceneMenu()
        director.replaceScene(scene)
    }
}