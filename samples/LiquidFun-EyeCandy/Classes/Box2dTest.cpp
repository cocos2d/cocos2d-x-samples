#include "Box2dTest.h"
#include "GLES-Render.h"

using namespace cocos2d;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

Box2DTestLayer* Box2DTestLayer::create()
{
    auto layer = new Box2DTestLayer();
    layer->autorelease();
    return layer;
}

Box2DTestLayer::Box2DTestLayer()
: _world(nullptr)
{
    auto director = Director::getInstance();
    auto dispatcher = director->getEventDispatcher();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(Box2DTestLayer::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // init physics
    this->initPhysics();

    //Set up sprite
    auto parent = Node::create();
    addChild(parent, 0, kTagParentNode);

    auto s = director->getWinSize();
    addNewSpriteAtPosition(Point(s.width/2, s.height/2));

    auto label = Label::createWithTTF("Tap screen", "fonts/Marker Felt.ttf", 32.0f);
    addChild(label, 0);
    label->setColor(Color3B(0,0,255));
    label->setPosition(Point(s.width/2, s.height-50));
    
    scheduleUpdate();
}

Box2DTestLayer::~Box2DTestLayer()
{
    delete _debugDraw;
    delete _world;
}

void Box2DTestLayer::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    _world = new b2World(gravity);

    // Do we want to let bodies sleep?
    _world->SetAllowSleeping(true);

    _world->SetContinuousPhysics(true);

    _debugDraw = new GLESDebugDraw( PTM_RATIO );
    _world->SetDebugDraw(_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
//    flags += b2Draw::e_jointBit;
//    flags += b2Draw::e_aabbBit;
//    flags += b2Draw::e_pairBit;
//    flags += b2Draw::e_centerOfMassBit;
    flags += b2Draw::e_particleBit;
    _debugDraw->SetFlags(flags);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = _world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2EdgeShape groundBox;

    auto s = Director::getInstance()->getWinSize();
    // bottom
    groundBox.Set(b2Vec2(0/PTM_RATIO,0/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(0/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0/PTM_RATIO,0/PTM_RATIO), b2Vec2(0/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,0/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);



    b2ParticleSystemDef particleSystemDef;
    particleSystemDef.dampingStrength = 0.2f;
    particleSystemDef.radius = 0.3f;
    _particleSystem = _world->CreateParticleSystem(&particleSystemDef);
    _particleSystem->SetGravityScale(0.4f);
    _particleSystem->SetDensity(1.2f);

    b2ParticleGroupDef pd;
    pd.flags = b2_waterParticle;
    
    b2PolygonShape shape2;
    shape2.SetAsBox(9.0f, 9.0f, b2Vec2(0.0f, 0.0f), 0.0);
    
    pd.shape = &shape2;
    _particleSystem->CreateParticleGroup(pd);
}

void Box2DTestLayer::addNewSpriteAtPosition(Point p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);

    auto parent = this->getChildByTag(kTagParentNode);
    auto sprite = Sprite::create("Images/r1.png");
    parent->addChild(sprite);
    sprite->setPosition( Point( p.x, p.y) );

    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

    b2Body *body = _world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = sprite->getContentSize().width/2/PTM_RATIO;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}


void Box2DTestLayer::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;

    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    _world->Step(dt, velocityIterations, positionIterations);

    b2Vec2 *array = _particleSystem->GetPositionBuffer();
    int32 l = _particleSystem->GetParticleCount();
    for(int i=0; i<l; i++) {
        b2Vec2 p = array[i];
    }
}

void Box2DTestLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location

    for (auto& touch : touches)
    {
        if(!touch)
            break;

        auto location = touch->getLocation();
    
        addNewSpriteAtPosition( location );
    }
}

// Draw

void Box2DTestLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    Layer::draw(renderer, transform, transformUpdated);

    _customCmd.init(_globalZOrder);
    _customCmd.func = CC_CALLBACK_0(Box2DTestLayer::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCmd);
}

void Box2DTestLayer::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);

    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    _world->DrawDebugData();
    CHECK_GL_ERROR_DEBUG();

    kmGLPopMatrix();
}