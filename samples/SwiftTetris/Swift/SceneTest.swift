//
//  SceneTest.swift
//  SwiftTetris
//
//  Created by Justin Graham on 7/7/14.
//
//

import Foundation

class SceneTest : Scene
{
    override func onEnter()
    {
        var director = Director.getInstance()
        var size = director.getWinSize()
        
        var block = BlockFactory.getInstance.createRandomBlock()
        block.setPosition(CGPointMake(size.width/2, size.height/2))
        addChild(block)
        
        director.popScene()
    }
}