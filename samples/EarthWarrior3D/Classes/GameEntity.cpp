//
//  GameEntity.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "GameEntity.h"

Node *GameEntity::getModel(){
    return _Model;
}

Vertex3F GameEntity::getOrientation(){
    return _orientation;
}

void GameEntity::forward(float dist){
    float f = getRotation();
    setPosition(getPosition()
                +Point(
                       sinf(CC_DEGREES_TO_RADIANS(f))*dist,
                       cosf(CC_DEGREES_TO_RADIANS(f))*dist)
                );
}
void GameEntity::forward(float dist, float angle)
{
    setRotation(getRotation()-angle);
    forward(dist);
}