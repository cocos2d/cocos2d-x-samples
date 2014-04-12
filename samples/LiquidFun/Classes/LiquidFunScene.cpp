/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2014 Google, Inc

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "LiquidFunScene.h"
#include "FaucetEmitter.h"
#include "Box2DGLESDebugDrawLayer.h"
#include "GLES-Render.h"

USING_NS_CC;

namespace {

// Width of the world in meters.  This is used to calculate the world extents
// from the view's aspect ratio.
const float k_worldWidth = 10.0f;
// Gravity vector.
const b2Vec2 k_gravity(0.0f, -9.8f);
// Particle size as a fraction of the minimum world extent.
const float k_particleSize = 0.01f;
// Size of world walls as a fraction of the minimum world extent.
const float k_wallSize = 0.05f;
// Size of drawable boxes as a fraction of the minimum world extent.
const float k_drawableBoxThickness = 0.025f;

// Determine the maximum value of an element in a b2Vec.
float b2Vec2Max(const b2Vec2& vector) {
  return b2Max(vector.x, vector.y);
}

// Determine the minimum value of an element in a b2Vec.
float b2Vec2Min(const b2Vec2& vector) {
  return b2Min(vector.x, vector.y);
}

}  // namespace

Scene* LiquidFunScene::scene()
{
  // 'scene' is an autorelease object
  Scene *scene = Scene::create();

  // 'layer' is an autorelease object
  LiquidFunScene *layer = LiquidFunScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

LiquidFunScene::LiquidFunScene() :
  m_world(NULL),
  m_worldExtentMin(0.0f),
  m_worldExtentMax(0.0f),
  m_startSprite(NULL),
  m_endSprite(NULL) {
}

LiquidFunScene::~LiquidFunScene() {
  while (m_emitters.begin() != m_emitters.end()) {
    delete m_emitters.front();
    m_emitters.pop_front();
  }
  while (m_killFields.begin() != m_killFields.end()) {
    delete m_killFields.front();
    m_killFields.pop_front();
  }
}

// on "init" you need to initialize your instance
bool LiquidFunScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !CCLayer::init() ) {
    return false;
  }

  Size visibleSize = Director::getInstance()->getVisibleSize();
  Point origin = Director::getInstance()->getVisibleOrigin();

  /////////////////////////////
  // 2. add a menu item with "X" image, which is clicked to quit the program
  //    you may modify it.

  // add a "close" icon to exit the progress. it's an autorelease object
  MenuItemImage *pCloseItem =
    MenuItemImage::create( "CloseNormal.png",
                          "CloseSelected.png",
                          CC_CALLBACK_1(LiquidFunScene::menuCloseCallback, this));

  pCloseItem->setPosition(Point(origin.x +
                              visibleSize.width -
                              pCloseItem->getContentSize().width/2,
                              origin.y +
                              pCloseItem->getContentSize().height/2));

  // create menu, it's an autorelease object
  Menu* pMenu = Menu::create(pCloseItem, NULL);
  pMenu->setPosition(Point::ZERO);
  addChild(pMenu, 1);

  // Add a label shows the title of the demo.
  LabelTTF* pLabel = LabelTTF::create("LiquidFun Demo in Cocos2Dx",
                                          "Arial", 24);
  // Position the label on the center of the screen.
  pLabel->setPosition(Point(origin.x + visibleSize.width/2,
                          origin.y + visibleSize.height -
                            pLabel->getContentSize().height));

  // add the label as a child to this layer
  addChild(pLabel, 1);

  // add "LiquidFunScene" splash screen"
  Sprite* pSprite = Sprite::create("HelloWorld.png");

  // position the sprite on the center of the screen
  pSprite->setPosition(Point(visibleSize.width/2 + origin.x,
                           visibleSize.height/2 + origin.y));
  // scale the background to fill the screen.
  const Size &size = pSprite->getTextureRect().size;
  pSprite->setScale(b2Max(visibleSize.width, visibleSize.height) /
                    b2Max(size.width, size.height));

  // add the sprite as a child to this layer
  addChild(pSprite, 0);

  // ----------------------------------
  // Immediately start level 0, since we have no other interface to manage
  // levels
  LayoutLevel(0);
  StartLevel();

  return true;
}

// Add a particle emitter to the world with a default size, emit rate and
// starting velocity.
FaucetEmitter* LiquidFunScene::AddEmitter(
    const b2Vec2& origin, const std::vector<b2ParticleColor> &colors,
    const float colorCycleRate) {
  // Initial velocity of each emitted particle.
  static const b2Vec2 k_startingVelocity(0, -5.0);
  // Faucet size as a fraction of the world's maximum dimension.
  static const float32 k_faucetSize = 0.01f;
  // Number of particles to emit per second.
  static const float32 k_emitRate = 10.0f;
  return AddEmitter(origin, m_worldExtentMax * k_faucetSize,
                    k_emitRate, k_startingVelocity, colors, colorCycleRate);
}

// Add a particle emitter to the world with customized parameters.
FaucetEmitter* LiquidFunScene::AddEmitter(
    const b2Vec2& origin, const float32 faucetSize, const float32 emitRate,
    const b2Vec2& startingVelocity, const std::vector<b2ParticleColor>& colors,
    const float colorCycleRate) {
  FaucetEmitter * const faucetEmitter = new FaucetEmitter(
      m_world, origin, startingVelocity, faucetSize, emitRate, colors,
      colorCycleRate);
  m_emitters.push_back(faucetEmitter);
  return faucetEmitter;
}

// Add a kill field.
LiquidFunScene::ParticleKillField* LiquidFunScene::AddParticleKillField(
    const b2Transform &xf, const b2Shape &shape, const int32 shapeSize) {
  ParticleKillField * const killField = new ParticleKillField(
      xf, shape, shapeSize, &m_shapeAllocator, m_world);
  m_killFields.push_back(killField);
  return killField;
}


// Create a ball.
void LiquidFunScene::CreateBall(const b2Vec2& worldPosition,
                                const b2Vec2& worldSize) {
  const Point screenPosition = ConvertWorldToScreenPosition(worldPosition);
  // Create a ball sprite
  Sprite* const ball = Sprite::create("ball.png");
  ball->setPosition(screenPosition);
  ball->setScale(CalculateSpriteScale(ball, worldSize));
  ball->setTag(1);
  addChild(ball);

  // Create ball body
  b2BodyDef ballBodyDef;
  ballBodyDef.type = b2_dynamicBody;
  ballBodyDef.position = worldPosition;
  ballBodyDef.userData = ball;
  b2Body* ballBody = m_world->CreateBody(&ballBodyDef);

  // Create circle shape
  b2CircleShape circle;
  circle.m_radius = b2Vec2Min(worldSize) * 0.5f;

  // Create shape definition and add to body
  b2FixtureDef ballShapeDef;
  ballShapeDef.shape = &circle;
  ballShapeDef.density = 1.0f;
  ballShapeDef.friction = 0.f;
  ballShapeDef.restitution = 1.0f;
  ballBody->CreateFixture(&ballShapeDef);
}

// Create a number of balls across the world.
void LiquidFunScene::CreateBalls(const int numberOfBalls,
                                 const float relativeBallSize) {
  const float oneOverNumberOfBalls =
      1.0f / static_cast<float>(numberOfBalls);
  const b2Vec2 worldInWallsSize = m_worldExtentsInWalls - m_worldOffsetInWalls;
  const float ballDiameter = b2Vec2Min(b2Vec2(
      worldInWallsSize.x * relativeBallSize,
      worldInWallsSize.y * relativeBallSize));

  for (int i = 0; i < numberOfBalls; i++) {
    const float relativeOffset = static_cast<float>(i) *
                                 oneOverNumberOfBalls;
    const b2Vec2 worldPosition(
        m_worldOffsetInWalls.x + worldInWallsSize.x * relativeOffset,
        m_worldOffsetInWalls.y + worldInWallsSize.y * relativeOffset);
    CreateBall(worldPosition, b2Vec2(ballDiameter, ballDiameter));
  }
}

void LiquidFunScene::CreateBlockOfParticles() {
  b2PolygonShape shape;
  const b2Vec2 center = ConvertRelativePositionToWorld(b2Vec2(0.5f, 0.5f));
  const b2Vec2 halfSize = ConvertRelativeSizeToWorld(
      b2Vec2(0.4f, 0.02f));
  shape.SetAsBox(halfSize.x, halfSize.y, b2Vec2(0.0f, 0.0f), 0.0f);

  b2ParticleGroupDef pd;
  pd.flags = b2_viscousParticle;
  pd.position = center;
  pd.shape = &shape;
  pd.color = b2ParticleColor(255, 128, 128, 255);
  m_world->CreateParticleGroup(pd);
}

// Create a box fixture.
b2Fixture* LiquidFunScene::CreateBoxFixture(b2Body * const body,
                                            const b2Vec2& position,
                                            const b2Vec2& size) {
  b2PolygonShape shape;
  const b2Vec2 halfSize(size.x * 0.5f, size.y * 0.5f);
  const b2Vec2 center(position.x + halfSize.x, position.y + halfSize.y);
  shape.SetAsBox(halfSize.x, halfSize.y, center, 0.0f);
  return body->CreateFixture(&shape, 0);
}


void LiquidFunScene::CreateWalls() {
  // Create the walls of the world.
  b2BodyDef bd;
  bd.type = b2_staticBody;
  bd.position.Set(0,0);
  b2Body* ground = m_world->CreateBody(&bd);

  // Calculate wall size in meters.
  const float wallSize = k_wallSize * m_worldExtentMin;

  m_worldOffsetInWalls.Set(wallSize, wallSize);
  m_worldExtentsInWalls.Set(m_worldExtents.x - wallSize,
                            m_worldExtents.y - wallSize);

  const b2Vec2 topBottomWallSize = b2Vec2(m_worldExtents.x, wallSize);
  CreateBoxFixture(ground, b2Vec2(0, 0), topBottomWallSize);
  CreateBoxFixture(ground, b2Vec2(0, m_worldExtents.y - topBottomWallSize.y),
                   topBottomWallSize);
  const b2Vec2 leftRightWallSize = b2Vec2(wallSize, m_worldExtents.y);
  CreateBoxFixture(ground, b2Vec2(0, 0), leftRightWallSize);
  CreateBoxFixture(ground, b2Vec2(m_worldExtents.x - leftRightWallSize.x, 0),
                   leftRightWallSize);
}

// Creates a physics world and lays outt he
void LiquidFunScene::LayoutLevel(int level) {
  // Scale the dimensions of the world to fit the view.
  const Size viewSize = Director::getInstance()->getVisibleSize();
  const float aspectRatio = viewSize.width / viewSize.height;
  m_worldExtents.x = k_worldWidth;
  m_worldExtents.y = k_worldWidth / aspectRatio;
  m_worldExtentMin = b2Vec2Min(m_worldExtents);
  m_worldExtentMax = b2Vec2Max(m_worldExtents);
  m_worldExtentsInWalls = m_worldExtents;
  m_worldOffsetInWalls.Set(0.0f, 0.0f);

  // Create a world.
  m_world = new b2World(k_gravity);
  m_world->SetParticleRadius(m_worldExtentMin * k_particleSize);
  m_world->SetParticleDamping(0.2f);

  // Enable the Box2D rendering layer.
  Box2DGLESDebugDrawLayer* box2dLayer = new Box2DGLESDebugDrawLayer(
    m_world, b2Vec2Min(b2Vec2(viewSize.width / m_worldExtents.x,
                              viewSize.height / m_worldExtents.y)));
  box2dLayer->init();
  addChild(box2dLayer);
  GLESDebugDraw* const debugDraw = box2dLayer->GetGLESDebugDraw();
  // Turn off AABB drawing.
  debugDraw->SetFlags(debugDraw->GetFlags() & ~b2Draw::e_aabbBit);
  // Render particles as solid circles.
  debugDraw->SetSolidParticlesEnable(true);

  // Create boundaries
  CreateWalls();
  CreateBalls(5, 0.075f);
  CreateBlockOfParticles();

  // Define map-specific stuff
  switch (level) {
    case 0: {
      // Add an emitter in the middle
      static const float k_colorCycleRate = 5.0f;
      std::vector<b2ParticleColor> colors;
      colors.push_back(b2ParticleColor(0xff, 0x00, 0x00, 0xff));
      colors.push_back(b2ParticleColor(0xff, 0xff, 0xff, 0xff));
      colors.push_back(b2ParticleColor(0x00, 0x00, 0xff, 0xff));
      colors.push_back(b2ParticleColor(0x00, 0xff, 0x00, 0xff));
      colors.push_back(b2ParticleColor(0x22, 0xff, 0x44, 0xff));
      AddEmitter(ConvertRelativePositionToWorld(b2Vec2(0.5f, 0.1f)),
                 colors, k_colorCycleRate);

      // Add a kill field to the bottom right of the screen.
      b2CircleShape circle;
      circle.m_radius = m_worldExtentMax * 0.025f;
      b2Transform circleLocationSize;
      circleLocationSize.SetIdentity();
      circleLocationSize.Set(ConvertRelativePositionToWorld(
          b2Vec2(0.8f, 0.9f)), 0.0f);
      AddParticleKillField(circleLocationSize, circle, sizeof(circle));
      break;
    }
    default:
      CCLOG("ERROR: Invalid level %d defined.", level);
      break;
  }
}

void LiquidFunScene::StartLevel() {
  // Kicks off emitters
  for (FaucetEmitterList::iterator it = m_emitters.begin();
       it != m_emitters.end(); ++it) {
    (*it)->SetIsEmitting(true);
  }
}

void LiquidFunScene::Reset() {
  // Walk all the bodies and remove the sprites
  for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      Sprite* myActor = (Sprite*)b->GetUserData();
      removeChild(myActor);
    }
  }
  // Now destroy the world
  delete m_world;
}

void LiquidFunScene::update(float dt) {
  static const int k_velocityIterations = 8;
  static const int k_positionIterations = 3;
  static const float k_stepTime = 1.0f/60.0f;

  // Instruct the world to perform a single step of simulation. It is
  // generally best to keep the time step and iterations fixed.
  m_world->Step(k_stepTime, k_velocityIterations, k_positionIterations);

  // Iterate over the bodies in the physics world and synchronize the position
  // of sprites with the bodies that have them present.
  // NOTE: This will break if a body's user data does *not* point to a sprite.
  for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
    if (b->GetUserData() != NULL) {
      // Synchronize the AtlasSprites position and rotation with the
      // corresponding body
      Sprite* myActor = (Sprite*)b->GetUserData();
      myActor->setPosition(ConvertWorldToScreenPosition(b->GetPosition()));
      myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
    }
  }

  // Step the emitters and kill fields.
  for (FaucetEmitterList::iterator it = m_emitters.begin();
       it != m_emitters.end(); ++it) {
    (*it)->Step(k_stepTime, b2_waterParticle | b2_colorMixingParticle);
  }
  for (ParticleKillFieldList::iterator it = m_killFields.begin();
       it != m_killFields.end(); ++it) {
    (*it)->Step();
  }
}

void LiquidFunScene::menuCloseCallback(cocos2d::Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not "
                 "implement a close button.","Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void LiquidFunScene::onEnter() {
  CCLOG("On Enter");
  CCLayer::onEnter();

  // Finally tell what happens
  scheduleUpdate();

  Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(
      this, 0, true);
}

void LiquidFunScene::onExit() {
  CCLOG("On Exit");
  Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
}

// Get the maximum dimension from the view size.
float LiquidFunScene::GetMaxViewDimension() const {
  const Size viewSize = Director::getInstance()->getVisibleSize();
  return b2Max(viewSize.width, viewSize.height);
}

// Convert a relative coordinates to a position in meters.
b2Vec2 LiquidFunScene::ConvertRelativePositionToWorld(
    const b2Vec2& relativeLocation) const {
  return ConvertRelativeSizeToWorld(b2Vec2(relativeLocation.x,
                                            1.0f - relativeLocation.y));
}

// Convert a size relative to world space to a size in meters.
b2Vec2 LiquidFunScene::ConvertRelativeSizeToWorld(
    const b2Vec2& relativeSize) const {
  return b2Vec2(relativeSize.x * m_worldExtents.x,
                relativeSize.y * m_worldExtents.y);
}

// Convert a screen location to a position in meters.
b2Vec2 LiquidFunScene::ConvertScreenPositionToWorld(
    const b2Vec2& screenLocation) const {
  const Size viewSize = Director::getInstance()->getVisibleSize();
  // Using ConvertRelativeSizeToWorld() since there is no need to invert y.
  return ConvertRelativeSizeToWorld(
      b2Vec2(screenLocation.x / viewSize.width,
             screenLocation.y / viewSize.height));
}

// Convert meters to screen location.
Point LiquidFunScene::ConvertWorldToScreenPosition(
    const b2Vec2& worldPosition) const {
  const Size viewSize = Director::getInstance()->getVisibleSize();
  return Point((worldPosition.x / m_worldExtents.x) * viewSize.width,
                 (worldPosition.y / m_worldExtents.y) * viewSize.height);
}

// Create a pointer sprite
Sprite* LiquidFunScene::CreatePointerSprite(
    const char * const assetName, const Point& position,
    const float scale) {
  Sprite * sprite = Sprite::create(assetName);
  sprite->setPosition(position);
  sprite->setScale(CalculateSpriteScale(
      sprite, ConvertRelativeSizeToWorld(b2Vec2(scale, scale))));
  addChild(sprite);
  return sprite;
}

float LiquidFunScene::CalculateSpriteScale(
    cocos2d::Sprite * const sprite, const b2Vec2& worldSize) const {
  const Size &size = sprite->getTextureRect().size;
  const float maxSpriteDimension = b2Max(size.width, size.height);
  const float maxViewDimension = GetMaxViewDimension();
  const float maxWorldSizeDimension = b2Vec2Max(worldSize);
  return ((maxWorldSizeDimension / m_worldExtentMax) * maxViewDimension) /
      maxSpriteDimension;
}

bool LiquidFunScene::ccTouchBegan(cocos2d::Touch* touch,
                                  cocos2d::Event* event) {
  CCLOG("Touch begins!");
  if (m_startSprite != NULL) {
    return true;
  }

  // Size of the pointer relative to the screen.
  static const float k_pointerScale = 0.05f;
  // Create the start / end pointers.
  const Point &position = touch->getLocation();
  m_startSprite = CreatePointerSprite(
      "StartSprite.png", position, k_pointerScale);
  m_endSprite = CreatePointerSprite(
      "EndSprite.png", position, k_pointerScale);
  return true;
}

void LiquidFunScene::ccTouchMoved(cocos2d::Touch* touch,
                                  cocos2d::Event* event) {
  if (m_endSprite != NULL) {
    m_endSprite->setPosition(touch->getLocation());
  }
}

void LiquidFunScene::ccTouchEnded(cocos2d::Touch* touch,
                                  cocos2d::Event* event){

  if (m_startSprite != NULL) {
    const Point& startSpritePosition = m_startSprite->getPosition();
    const Point& endSpritePosition = m_endSprite->getPosition();
    // Calculate the start / end and length of the vector between them in
    // world coordinates.
    const b2Vec2 startPosition = ConvertScreenPositionToWorld(
        b2Vec2(startSpritePosition.x, startSpritePosition.y));
    const b2Vec2 endPosition = ConvertScreenPositionToWorld(
        b2Vec2(endSpritePosition.x, endSpritePosition.y));
    const b2Vec2 startEndVector = endPosition - startPosition;
    const float32 startEndLength = startEndVector.Length();

    // Calculate the middle point along the vector between startPosition and
    // endPosition.
    b2Vec2 midPoint;
    midPoint = startEndVector;
    midPoint *= 0.5f;
    midPoint += startPosition;

    b2PolygonShape box;
    box.SetAsBox(startEndLength * 0.5f,
                 k_drawableBoxThickness * m_worldExtentMin);
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = midPoint;
    bodyDef.angle = atan2(startEndVector.y, startEndVector.x);
    b2Body* body = m_world->CreateBody(&bodyDef);
    body->CreateFixture(&box, 0);

    removeChild(m_startSprite);
    removeChild(m_endSprite);
    // These will be cleaned up by the autorelease system since they were
    // allocated by init()
    m_startSprite = NULL;
    m_endSprite = NULL;
  }
}
