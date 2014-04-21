#include "EyeCandyLayer.h"
#include "LFParticleSystemNode.h"
#include "LFSpriteNode.h"

#include "GLES-Render.h"

using namespace cocos2d;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

EyeCandyLayer* EyeCandyLayer::create()
{
    auto layer = new EyeCandyLayer();
    layer->autorelease();
    return layer;
}

EyeCandyLayer::EyeCandyLayer()
: _world(nullptr)
{
    auto director = Director::getInstance();
    auto dispatcher = director->getEventDispatcher();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(EyeCandyLayer::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // init physics
    this->initPhysics();

    auto p = LFParticleSystemNode::create(_particleSystem, PTM_RATIO);
    this->addChild(p);

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

EyeCandyLayer::~EyeCandyLayer()
{
    delete _debugDraw;
    delete _world;
}

void EyeCandyLayer::initPhysics()
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
    flags += b2Draw::e_jointBit;
//    flags += b2Draw::e_aabbBit;
//    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
//    flags += b2Draw::e_particleBit;
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


    // particles
    b2ParticleSystemDef particleSystemDef;
    particleSystemDef.dampingStrength = 0.2f;
    particleSystemDef.radius = 0.3f;
    _particleSystem = _world->CreateParticleSystem(&particleSystemDef);
    _particleSystem->SetGravityScale(0.4f);
    _particleSystem->SetDensity(1.2f);

    b2ParticleGroupDef pd;
    pd.flags = b2_waterParticle | b2_colorMixingParticle;
    pd.color.Set(30, 64, 194, 255);

    b2PolygonShape shape2;
    shape2.SetAsBox(9.0f, 9.0f, b2Vec2(0.0f, 0.0f), 0.0);
    
    pd.shape = &shape2;
    _particleSystem->CreateParticleGroup(pd);


    // mover
    b2BodyDef bdg;
    bdg.position.Set(s.width/PTM_RATIO/2, s.height/PTM_RATIO/2);
    b2Body* ground = _world->CreateBody(&bdg);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(s.width/PTM_RATIO/2, s.height/PTM_RATIO/2);
    _mover = _world->CreateBody(&bd);
    b2PolygonShape shape;
    shape.SetAsBox(1.0f, 5.0f, b2Vec2(0.0f, 2.0f), 0.0);
    _mover->CreateFixture(&shape, 5.0f);

    b2RevoluteJointDef jd;
    jd.bodyA = ground;
    jd.bodyB = _mover;
    jd.localAnchorA.Set(0.0f, 0.0f);
    jd.localAnchorB.Set(0.0f, 5.0f);
    jd.referenceAngle = 0.0f;
    jd.motorSpeed = 0;
    jd.maxMotorTorque = 1e7f;
    jd.enableMotor = true;
    _joint = (b2RevoluteJoint*)_world->CreateJoint(&jd);
    _joint->SetMotorSpeed(0.7);
}

void EyeCandyLayer::addNewSpriteAtPosition(Point p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);

    auto parent = this->getChildByTag(kTagParentNode);
    auto sprite = LFSpriteNode::create("Images/r1.png");
    parent->addChild(sprite);

    // Define the dynamic body.
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

    sprite->setB2Body(body);
    sprite->setPTMRatio(PTM_RATIO);
}


void EyeCandyLayer::update(float dt)
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
}

void EyeCandyLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
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

void EyeCandyLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    Layer::draw(renderer, transform, transformUpdated);

    _customCmd.init(_globalZOrder);
    _customCmd.func = CC_CALLBACK_0(EyeCandyLayer::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCmd);
}

void EyeCandyLayer::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    kmGLPushMatrix();
    kmGLLoadMatrix(&transform);

    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    _world->DrawDebugData();
    CHECK_GL_ERROR_DEBUG();

    kmGLPopMatrix();
}