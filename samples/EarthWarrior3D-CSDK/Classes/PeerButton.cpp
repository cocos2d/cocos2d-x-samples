//
//  PeerButton.cpp
//  HelloCcf
//
//  Created by calf on 14-7-23.
//
//

#include "PeerButton.h"

///
/// PeerButton
///

PeerButton* PeerButton::create(const std::string &normalImage,
                       const std::string& selectedImage ,
                       const std::string& disableImage,
                       TextureResType texType)
{
    PeerButton *btn = new PeerButton();
    if (btn && btn->init(normalImage,selectedImage,disableImage,texType)) {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}
