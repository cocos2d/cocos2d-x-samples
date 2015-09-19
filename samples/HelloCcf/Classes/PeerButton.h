//
//  PeerButton.h
//  HelloCcf
//
//  Created by calf on 14-7-23.
//
//

#ifndef __HelloCcf__PeerButton__
#define __HelloCcf__PeerButton__

#include "cocos2d.h"
#include "ConnectionInterface.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
using namespace cocos2d::ui;

class PeerButton : public Button
{
public:
    static PeerButton* create(const std::string& normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);
    tagPEER getPeer(){return _peer;}
    void setPeer(tagPEER peer){_peer = peer;}
protected:
    tagPEER _peer;
};
#endif /* defined(__HelloCcf__PeerMenuItem__) */
