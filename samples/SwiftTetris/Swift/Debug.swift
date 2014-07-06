
//  Debug.swift
//  Created by Justin Graham on 6/30/14.

class Debug
{
    var _console : Console
    
    class var getInstance : Debug
    {
        struct Singleton
        {
            static let instance = Debug()
        }
        return Singleton.instance
    }
    
    init()
    {
        _console = Director.getInstance().console
    }
    
    func log(message : String)
    {
        println(message)
        _console.log(message)
    }
}
