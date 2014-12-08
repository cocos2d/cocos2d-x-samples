#pragma once

#include "cocos2d.h"
#include "GAF.h"

#include <string>
#include <vector>
#include <unordered_map>


NS_GAF_BEGIN
class GAFObject;
class GAFAsset;
NS_GAF_END

USING_NS_GAF;

class GafFeatures : public cocos2d::Layer
{
private:

    typedef std::vector<std::string> StringVector_t;
    typedef std::unordered_map<int, std::string> MusicEffects_t;
    
    GAFAsset*                m_asset;
    cocos2d::__Array*        m_objects;
    StringVector_t           m_files;
    int                      m_anim_index;
    MusicEffects_t           m_musicEffects;
    void enableSequenceControllers(bool value);

    typedef std::vector<std::string> ObjectSequencesNames_t;
    ObjectSequencesNames_t  m_objectSequencesNames;
    int m_currentSequence;

    cocos2d::Label* m_loadingTimeLabel;
    cocos2d::EventListenerTouchAllAtOnce* m_touchlistener;
    
    cocos2d::MenuItemImage* m_playButton;
    cocos2d::MenuItemImage* m_pauseButton;
    cocos2d::MenuItemImage* m_nextSequence;
    cocos2d::MenuItemImage* m_prevSequence;
    cocos2d::Label*         m_sequenceName;
    cocos2d::Label*         m_vramStat;
    
    void setupMenuItems();
    cocos2d::MenuItemImage* addButton(const std::string& buttonName, const std::string& buttonPressedName, const cocos2d::Point& pos, const cocos2d::ccMenuCallback& clb);
public:
    GafFeatures();
    ~GafFeatures();

    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::Scene* scene();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GafFeatures);

    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

    void black(cocos2d::Ref*);
    void white(cocos2d::Ref*);
    void gray(cocos2d::Ref*);
    void prevFrame(cocos2d::Ref*);
    void nextFrame(cocos2d::Ref*);
    void toggleReverse(cocos2d::Ref*);
    void restart(cocos2d::Ref*);
    void playpause(cocos2d::Ref*);
    void cleanup(cocos2d::Ref*);
    void next_anim(cocos2d::Ref*);
    void prev_anim(cocos2d::Ref*);
    int  maxFrameNumber();
    void setFrameNumber(int aFrameNumber);
    int  frameNumber();
    void addObjectsToScene();
    void removeFromScene(int aCount);

    void nextSequence(cocos2d::Ref*);
    void prevSequence(cocos2d::Ref*);

    virtual void onFinishSequence(GAFObject* object, const std::string& sequenceName);

    virtual void onTexturePreLoad(std::string& path);
    
    virtual void onFramePlayed(GAFObject* object, int frame);
};
