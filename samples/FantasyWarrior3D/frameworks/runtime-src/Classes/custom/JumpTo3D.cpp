//
//  JumpTo3D.cpp
//  Jump3DTest
//
//  Created by gaohuang on 14-10-9.
//
//

#include "JumpTo3D.h"

JumpTo3D* JumpTo3D::create(float duration, const Vec3& position, float height, int jumps)
{
    JumpTo3D * jumpTo3D = new (std::nothrow) JumpTo3D();
    jumpTo3D->initWithDuration(duration, position, height, jumps);
    jumpTo3D->autorelease();
    
    return jumpTo3D;
}

JumpTo3D* JumpTo3D::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) JumpTo3D();
    a->initWithDuration(_duration, _delta, _height, _jumps);
	a->autorelease();
	return a;
}

JumpTo3D* JumpTo3D::reverse() const
{
	CCASSERT(false, "reverse() not supported in JumpTo3D");
	return nullptr;
}

void JumpTo3D::startWithTarget(Node *target)
{
    JumpBy3D::startWithTarget(target);
    _delta = Vec3(_delta.x - _startPosition.x, _delta.y - _startPosition.y,_delta.z-_startPosition.z);
}
