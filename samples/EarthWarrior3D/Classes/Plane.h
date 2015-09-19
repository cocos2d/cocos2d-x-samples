//
//  Plane.h
//  Moon3d
//
//  Created by Rye on 14-3-13.
//
//

#ifndef __Moon3d__Plane__
#define __Moon3d__Plane__

#include <iostream>
#include "cocos2d.h"
#include "GameEntity.h"

class Plane :public GameEntity{
public:
    CREATE_FUNC(Plane);
    bool init();
private:
    float pRate = 3.1415926/2;
    float originX = -15.0f;
    float originY = 159.0f;
    float originZ = 9.0f;
    const float pXW = 1.1f;
    const float pYW = 5.0f;
    const float pZW = 1.0f;
    const float pXA = 1.0f;
    const float pYA = 10.0f;
    const float pZA = 7.0f;
    
    void update(float dt);
};

#endif /* defined(__Moon3d__Plane__) */
