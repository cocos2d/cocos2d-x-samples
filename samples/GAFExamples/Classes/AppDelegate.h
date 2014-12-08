#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "platform/CCApplication.h"

class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
    void updateGLstates(float dt);
};

#endif // _APP_DELEGATE_H_
