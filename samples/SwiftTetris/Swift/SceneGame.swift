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
    var _board : Board?
    
    override func onEnter()
    {
        AudioEngine.getInstance().playBackgroundMusic("tetris.mp3", true)

        _board = Board()
        addChild(_board!)
        _board!.start()
    }
    
    override func onExit()
    {
        AudioEngine.getInstance().stopBackgroundMusic()
        
        removeAllChildren()
        _board = nil
    }
}
