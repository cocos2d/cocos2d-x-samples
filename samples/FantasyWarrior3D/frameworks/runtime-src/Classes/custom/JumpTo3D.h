//
//  JumpTo3D.h
//  Jump3DTest
//
//  Created by gaohuang on 14-10-9.
//
//

#ifndef __Jump3DTest__JumpTo3D__
#define __Jump3DTest__JumpTo3D__

#include "cocos2d.h"
#include "JumpBy3D.h"

USING_NS_CC;

NS_CC_BEGIN

class JumpTo3D : public JumpBy3D
{
public:
    /** creates the action */
    static JumpTo3D* create(float duration, const Vec3& position, float height, int jumps);
    
    //
    // Override
    //
    virtual void startWithTarget(Node *target) override;
    virtual JumpTo3D* clone() const override;
    virtual JumpTo3D* reverse(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpTo3D() {}
    virtual ~JumpTo3D() {}
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTo3D);
};

NS_CC_END

#endif /* defined(__Jump3DTest__JumpTo3D__) */
