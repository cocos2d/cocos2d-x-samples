//
//  GreyShader.cpp
//  cocos2d_libs
//
//  Created by Kirito on 10/22/14.
//
//

#include "GreyShader.h"

void GreyShader::setGreyShader(Sprite * s)
{
    
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename("res/shader3D/greyScale.fsh");
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = cocos2d::GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    auto glprogramstate = cocos2d::GLProgramState::getOrCreateWithGLProgram(glprogram);
    s->setGLProgramState(glprogramstate);
}