#include "GafFeatures.h"

#include <audio/include/SimpleAudioEngine.h>

#include <iostream>

#ifdef WIN32
#include <windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}
#else
static double startCounter = 0.0;
void StartCounter()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    startCounter = double(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

double GetCounter()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return double(tv.tv_sec * 1000 + tv.tv_usec / 1000) - startCounter;
}
#endif


cocos2d::Point centerScreenPosition(GAFAsset* ast, const cocos2d::Size& screenSize)
{
    const GAFHeader& headInfo = ast->getHeader();
    
    return cocos2d::Point(-headInfo.frameSize.getMinX() + (screenSize.width - headInfo.frameSize.size.width) / 2,
                           headInfo.frameSize.getMinY() + (screenSize.height + headInfo.frameSize.size.height) / 2);
}

GafFeatures::GafFeatures()
    :
    m_asset(NULL),
    m_objects(NULL),
    m_currentSequence(0)
    , m_loadingTimeLabel(NULL)
{
    m_touchlistener = cocos2d::EventListenerTouchAllAtOnce::create();

    m_touchlistener->onTouchesBegan = CC_CALLBACK_2(cocos2d::Layer::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_touchlistener, this);
}
GafFeatures::~GafFeatures()
{
    CC_SAFE_RELEASE(m_asset);
    CC_SAFE_RELEASE(m_objects);
    CC_SAFE_RELEASE(m_playButton);
    CC_SAFE_RELEASE(m_pauseButton);
    CC_SAFE_RELEASE(m_nextSequence);
    CC_SAFE_RELEASE(m_prevSequence);
    CC_SAFE_RELEASE(m_sequenceName);
    CC_SAFE_RELEASE(m_vramStat);

    _eventDispatcher->removeEventListener(m_touchlistener);
}

cocos2d::Scene* GafFeatures::scene()
{
    cocos2d::Scene *scene = cocos2d::Scene::create();
    GafFeatures *layer = GafFeatures::create();
    scene->addChild(layer);
    return scene;
}


void GafFeatures::black(cocos2d::Ref*)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GafFeatures::white(cocos2d::Ref*)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GafFeatures::gray(cocos2d::Ref*)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void GafFeatures::prevFrame(cocos2d::Ref*)
{
    int f = frameNumber();
    if (-1 == f)
    {
        return;
    }
    if (f)
    {
        setFrameNumber(f - 1);
    }
}

void GafFeatures::nextFrame(cocos2d::Ref*)
{
    int f = frameNumber();
    if (-1 == f)
    {
        return;
    }
    if (f != maxFrameNumber())
    {
        setFrameNumber(f + 1);
    }
}

void GafFeatures::setupMenuItems()
{
    cocos2d::Size wsize = cocos2d::Director::getInstance()->getWinSize();
    cocos2d::Vector<cocos2d::MenuItem*> items;
    
    using namespace std::placeholders;
    
    const float Y = 0.1f;
    
    items.pushBack(addButton("buttons/previous_animation_button@2x.png", "buttons/previous_animation_button_pressed@2x.png", cocos2d::Point(0.0f, Y),
                             [this](cocos2d::Ref* obj)
                             {
                                 GafFeatures::prev_anim(obj);
                                 m_playButton->setVisible(false);
                                 m_pauseButton->setVisible(true);
                             }));
    
                   
    items.pushBack(addButton("buttons/previous_frame_button@2x.png", "buttons/previous_frame_button_pressed@2x.png", cocos2d::Point(0.1f, Y), std::bind(&GafFeatures::prevFrame, this, _1)));
    
    m_playButton = addButton("buttons/play_button@2x.png", "buttons/play_button_pressed@2x.png", cocos2d::Point(0.22f, Y),
                             [this](cocos2d::Ref* obj)
                             {
                                 m_playButton->setVisible(true);
                                 m_pauseButton->setVisible(false);
                                 this->playpause(obj);
                             });
    
    m_pauseButton = addButton("buttons/pause_button@2x.png", "buttons/pause_button_pressed@2x.png", cocos2d::Point(0.22f, Y),
                              [this](cocos2d::Ref* obj)
                              {
                                  m_pauseButton->setVisible(false);
                                  m_playButton->setVisible(true);
                                  this->playpause(obj);
                              });
    
    items.pushBack(addButton("buttons/next_frame_button@2x.png", "buttons/next_frame_button_pressed@2x.png", cocos2d::Point(0.34f, Y), std::bind(&GafFeatures::nextFrame, this, _1)));
    
    items.pushBack(addButton("buttons/next_animation_button@2x.png", "buttons/next_animation_button_pressed@2x.png", cocos2d::Point(0.44f, Y),
                             [this](cocos2d::Ref* obj)
                             {
                                 m_pauseButton->setVisible(true);
                                 m_playButton->setVisible(false);

                                 GafFeatures::next_anim(obj);
                             }));
    
    items.pushBack(addButton("buttons/restart_button@2x.png", "buttons/restart_button_pressed@2x.png", cocos2d::Point(0.57f, Y), std::bind(&GafFeatures::restart, this, _1)));
    
    items.pushBack(addButton("buttons/white_bg_button@2x.png", "buttons/white_bg_button_pressed@2x.png", cocos2d::Point(0.67f, Y),
                             [this](cocos2d::Ref* ob)
                             {
                                 static int mode = 0;
                                 mode ++;
                                 
                                 if (mode == 3) mode = 0;
                                 switch (mode)
                                 {
                                     case 0:
                                         this->gray(ob);
                                         break;
                                     case 1:
                                         this->white(ob);
                                         break;
                                     case 2:
                                         this->black(ob);
                                         break;
                                     default:
                                         break;
                                 }
                             }
                             ));
    
    m_nextSequence = addButton("buttons/right_arrow@2x.png", "buttons/right_arrow_pressed@2x.png", cocos2d::Point(0.40f, 0.93f), std::bind(&GafFeatures::nextSequence, this, _1));
    
    m_prevSequence = addButton("buttons/left_arrow@2x.png", "buttons/left_arrow_pressed@2x.png", cocos2d::Point(0.05f, 0.93f), std::bind(&GafFeatures::prevSequence, this, _1));
    
    
    
    m_playButton->retain();
    m_pauseButton->retain();
    m_nextSequence->retain();
    m_prevSequence->retain();
    
    m_playButton->setVisible(false);
    items.pushBack(m_pauseButton);
    items.pushBack(m_playButton);
    items.pushBack(m_nextSequence);
    items.pushBack(m_prevSequence);
    
    m_sequenceName = cocos2d::Label::createWithSystemFont("---", "System", 24);
    m_sequenceName->retain();
    
    cocos2d::Menu* pMenu = cocos2d::Menu::createWithArray(items);

    pMenu->setPosition(cocos2d::Point(wsize.width / 2.f - m_pauseButton->getPositionX(), 0));

    cocos2d::MenuItemLabel* labelMenuItem = cocos2d::MenuItemLabel::create(m_sequenceName);
    labelMenuItem->setAnchorPoint(cocos2d::Vec2(0.f, 0.5f));
    cocos2d::Point labelPos = cocos2d::Point( m_prevSequence->getPositionX() + m_prevSequence->getContentSize().width / 2.f, m_prevSequence->getPositionY());
    labelMenuItem->setPosition(labelPos);
    
    pMenu->addChild(labelMenuItem);
    
    addChild(pMenu, 10000);
    
    cocos2d::Sprite* gafLogo = cocos2d::Sprite::create("buttons/gaf_logo@2x.png");
    gafLogo->setAnchorPoint(cocos2d::Point(1.f, 1.f));
    gafLogo->setScale(0.5f * cocos2d::Director::getInstance()->getContentScaleFactor());
    gafLogo->setPosition(cocos2d::Vec2(wsize.width * 0.93f, wsize.height * 0.93f));
    
    addChild(gafLogo, 10000);
    
    m_vramStat = cocos2d::Label::createWithSystemFont("VRAM: XXX", "System", 14);
    m_vramStat->setAnchorPoint(cocos2d::Point(0.f, 0.f));
    m_vramStat->setPosition(cocos2d::Vec2(10, wsize.height * 0.1f));
    m_vramStat->retain();
    
    addChild(m_vramStat);
}

cocos2d::MenuItemImage* GafFeatures::addButton(const std::string &buttonName, const std::string &buttonPressedName, const cocos2d::Point &pos, const cocos2d::ccMenuCallback& clb)
{
    cocos2d::Size size = cocos2d::Director::getInstance()->getWinSize();
    
    cocos2d::MenuItemImage* item = cocos2d::MenuItemImage::create(buttonName, buttonPressedName, "", clb);
    
    item->setPosition(cocos2d::Point(size.width * pos.x, size.height * pos.y));
    item->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
    
    return item;
}

bool GafFeatures::init()
{
    setupMenuItems();
    gray(NULL);
    
    m_files.push_back("cut_the_hope/cut_the_hope.gaf");
    m_files.push_back("biggreen/biggreen.gaf");
    m_files.push_back("bird_bezneba/bird_bezneba.gaf");
    m_files.push_back("christmas2013_julia2/christmas2013_julia2.gaf");
    m_files.push_back("fireman_2014_sound/fireman_2014_sound.gaf");
    m_files.push_back("fairy2/fairy2.gaf");
    m_files.push_back("firemen/firemen.gaf");
    m_files.push_back("impiretank_05_oneplace/impiretank_05_oneplace.gaf");
    m_files.push_back("myshopsgame4/myshopsgame4.gaf");
    m_files.push_back("peacock_feb3_natasha/peacock_feb3_natasha.gaf");
    m_files.push_back("tiger/tiger.gaf");
    
    m_anim_index = 0;
    
    addObjectsToScene();
    
    return true;
}

void GafFeatures::enableSequenceControllers( bool value )
{
    m_prevSequence->setVisible(value);
    m_nextSequence->setVisible(value);
    m_sequenceName->setVisible(value);
    
    if (value)
    {
        m_sequenceName->setString(m_objectSequencesNames[m_currentSequence]);
    }
}

void GafFeatures::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event)
{
    /*if (!m_objects || !m_objects->count())
    {
        return;
    }

    GAFAnimatedObject * node = (GAFAnimatedObject*)m_objects->getObjectAtIndex(0);
    cocos2d::Touch * pTouch = touches[0];
    cocos2d::Point pt = pTouch->getLocation();
    node->setPosition(pt.x, pt.y);*/
}

void GafFeatures::nextSequence( cocos2d::Ref* )
{
    GAFAnimatedObject *object = (GAFAnimatedObject *)m_objects->getObjectAtIndex(0);

    m_currentSequence++;

    if (m_currentSequence >= m_objectSequencesNames.size())
    {
        m_currentSequence = 0;
    }

    const char* secName = m_objectSequencesNames[m_currentSequence].c_str();
    object->playSequence(secName, true);
    
    m_sequenceName->setString(secName);
}

void GafFeatures::prevSequence( cocos2d::Ref* )
{
    GAFAnimatedObject *object = (GAFAnimatedObject *)m_objects->getObjectAtIndex(0);

    m_currentSequence--;

    if (m_currentSequence < 0)
    {
        m_currentSequence = m_objectSequencesNames.size() - 1;
    }

    const char* secName = m_objectSequencesNames[m_currentSequence].c_str();
    object->playSequence(secName, true);
    
    m_sequenceName->setString(secName);
}

void GafFeatures::next_anim(cocos2d::Ref*)
{
    if (!m_files.size())
    {
        return;
    }

    cleanup(NULL);
    ++m_anim_index;

    if (m_anim_index >= (int)m_files.size())
    {
        m_anim_index = 0;
    }
    addObjectsToScene();
}

void GafFeatures::prev_anim(cocos2d::Ref*)
{
    if (!m_files.size())
    {
        return;
    }

    cleanup(NULL);
    --m_anim_index;
    if (m_anim_index < 0)
    {
        m_anim_index = m_files.size() - 1;
    }

    addObjectsToScene();
}

void GafFeatures::restart(cocos2d::Ref*)
{
    if (!m_objects || !m_objects->count())
    {
        return;
    }

    GAFAnimatedObject *object = (GAFAnimatedObject *)m_objects->getObjectAtIndex(0);
    object->stop();
    object->start();
}

void GafFeatures::playpause(cocos2d::Ref*)
{
    if (!m_objects || !m_objects->count())
    {
        return;
    }

    GAFAnimatedObject *object = (GAFAnimatedObject *)m_objects->getObjectAtIndex(0);

    if (object->isAnimationRunning())
    {
        object->pauseAnimation();
    }
    else
    {
        object->resumeAnimation();
    }
}

int GafFeatures::maxFrameNumber()
{
    if (!m_objects || !m_objects->count())
    {
        return -1;
    }

    GAFAnimatedObject *object = (GAFAnimatedObject *)m_objects->getObjectAtIndex(0);
    return object->totalFrameCount();	
}

void GafFeatures::setFrameNumber(int aFrameNumber)
{
    if (!m_objects || !m_objects->count())
    {
        return;
    }

    GAFAnimatedObject *object = (GAFAnimatedObject *)m_objects->getObjectAtIndex(0);
    object->setFrame(aFrameNumber);	
}

int GafFeatures::frameNumber()
{
    if (!m_objects || !m_objects->count())
    {
        return -1;
    }

    GAFAnimatedObject *object = (GAFAnimatedObject *)m_objects->getObjectAtIndex(0);
    return object->currentFrameIndex();
}

void GafFeatures::toggleReverse(cocos2d::Ref*)
{
    if (m_objects->count() == 0)
    {
        return;
    }
    GAFAnimatedObject *obj = (GAFAnimatedObject *)m_objects->getLastObject();
    obj->setReversed(!obj->isReversed());
}

void GafFeatures::cleanup(cocos2d::Ref*)
{
    CC_SAFE_RELEASE_NULL(m_asset);

    if (!m_objects)
    {
        return;
    }

    removeFromScene(m_objects->count());
    CC_SAFE_RELEASE_NULL(m_objects);
}

void GafFeatures::removeFromScene(int aCount)
{
    if (!m_objects || !aCount)
    {
        return;
    }

    if (aCount > int(m_objects->count()))
    {
        aCount = m_objects->count();
    }

    for (int i = 0; i < aCount; ++i)
    {
        GAFAnimatedObject *obj = (GAFAnimatedObject *) m_objects->getLastObject();
        removeChild(obj);
        m_objects->removeLastObject();
    }
}

void GafFeatures::addObjectsToScene()
{
    if (!m_asset)
    {
        StartCounter();
        m_asset = GAFAsset::create(m_files[m_anim_index], this);
        double loadingTime = GetCounter();

        cocos2d::log("Loading time [%f]\n", loadingTime);

        std::ostringstream ss;
        ss << m_files[m_anim_index] << " ";
        ss << loadingTime;

        //m_loadingTimeLabel->setString(ss.str().c_str());
        
        ss.str("");
        
        ss << "VRAM: ";
        ss << m_asset->getTextureAtlas()->getMemoryConsumptionStat();
        ss << " bytes";
        
        m_vramStat->setString(ss.str());
        
        CC_SAFE_RETAIN(m_asset);
    }

    if (!m_objects)
    {
        m_objects = cocos2d::__Array::create();
        m_objects->retain();
    }

    const cocos2d::Size size = cocos2d::Director::getInstance()->getWinSizeInPixels();

    if (m_asset)
    {
        GAFAnimatedObject *object = m_asset->createObject();
        
        object->setLocalZOrder(0);
        addChild(object);
        
        float scaleFactor = cocos2d::Director::getInstance()->getContentScaleFactor();
        object->setPosition(centerScreenPosition(m_asset, size / scaleFactor));
        
        m_objects->addObject(object);
        
        m_objectSequencesNames.clear();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        
        for(auto& effect : m_musicEffects)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(effect.second.c_str());
        }
#endif
        m_musicEffects.clear();
        
        const AnimationSequences_t& secDictionary = m_asset->getAnimationSequences();
        if (!secDictionary.empty())
        {
            for (AnimationSequences_t::const_iterator i = secDictionary.begin(), e = secDictionary.end(); i != e; ++i)
            {
                const std::string& seqName = i->first;
                std::string::size_type pos = seqName.find("__audio:");
                if (pos != std::string::npos)
                {
                    std::string effectName = seqName.substr(pos + 8) + ".wav";
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(effectName.c_str());
#endif
                    m_musicEffects[i->second.startFrameNo] = std::move(effectName);
                }
                else
                {
                    m_objectSequencesNames.push_back(i->first);
                }
            }
        }
        
        enableSequenceControllers(!m_objectSequencesNames.empty());
        
        // will work only if animation has a sequence
        object->playSequence("walk", true);
        object->setLooped(true);
        object->start();
        
        object->setSequenceDelegate(this);
        object->setFramePlayedDelegate(this);
        
    }
}

void GafFeatures::onFinishSequence( GAFAnimatedObject * object, const std::string& sequenceName )
{
    //! This function will be triggered once a sequence completed
}

void GafFeatures::onFramePlayed(GAFAnimatedObject *object, int frame)
{
    MusicEffects_t::const_iterator it = m_musicEffects.find(frame);
    
    if (it != m_musicEffects.end())
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(it->second.c_str());
#endif
    }
}

//! path parameter could be changed
void GafFeatures::onTexturePreLoad(std::string& path)
{
    CCLOG("Loading texture %s", path.c_str());
}
