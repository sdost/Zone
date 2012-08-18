//
//  Paddle.cpp
//  BreakoutCocos2D-x
//
//  Created by Samuel Dost on 7/29/12.
//
//

#include "Paddle.h"
#include "PhysicsWorld.h"
#include "GameViewScene.h"

using namespace cocos2d;

void Paddle::Init(CCLayer* scene)
{
    InitializeDisplay(scene);
    InitializePhysics();
    InitializeActions();
}

void Paddle::InitializeDisplay(CCLayer* scene)
{
    //CreateAnimations();
    
    //CCAction* anim = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("PADDLE_NORMAL"));
    //CCAction* repeat = CCRepeatForever::create((CCSequence *)anim);
    
    // Create sprite and add it to the layer
    _paddleSprite = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("PADDLE_NORMAL0000"));
    //_paddleSprite->runAction(repeat);
    _paddleSprite->setPosition(ccp(100, 100));
    _paddleSprite->setTag(1);
    scene->addChild(_paddleSprite, 5);
}

void Paddle::CreateAnimations()
{
    CCAnimation* normal = CCAnimation::create();
    for( int i = 1; i < 1; i++ )
    {
        char buffer [50];
        sprintf(buffer, "PADDLE_NORMAL00%02d", i);
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
        normal->addSpriteFrame(frame);
    }
    CCAnimationCache::sharedAnimationCache()->addAnimation(normal, "PADDLE_NORMAL");
}

void Paddle::InitializePhysics()
{
    if ( !PhysicsWorld::Exists() ) return;
    
    // Create paddle body
    b2BodyDef def = b2BodyDef();
    def.type = b2_dynamicBody;
    def.position.Set(320/2/PhysicsWorld::PhysScale(), 50/PhysicsWorld::PhysScale());
    def.userData = this;
    _paddleBody = PhysicsWorld::CreateBody(&def);
    
    // Create paddle shape
    b2PolygonShape paddleShape;
    paddleShape.SetAsBox(_paddleSprite->getContentSize().width/PhysicsWorld::PhysScale()/2,
                         _paddleSprite->getContentSize().height/PhysicsWorld::PhysScale()/2);
    
    // Create shape definition and add to body
    b2FixtureDef paddleShapeDef;
    paddleShapeDef.shape = &paddleShape;
    paddleShapeDef.density = 10.0f;
    paddleShapeDef.friction = 0.4f;
    paddleShapeDef.restitution = 0.1f;
    paddleShapeDef.filter.categoryBits = GameView::id_Paddle;
    paddleShapeDef.filter.maskBits = GameView::id_Collectable | GameView::id_Ball | GameView::id_Wall;
    paddleShapeDef.userData = this;
    _paddleFixture = _paddleBody->CreateFixture(&paddleShapeDef);
}

void Paddle::CleanupPhysics()
{
    if ( !PhysicsWorld::Exists() ) return;
    
    _paddleFixture->SetUserData(NULL);
    PhysicsWorld::DestroyBody(_paddleBody);
    _paddleBody->SetUserData(NULL);
    _paddleBody = NULL;
}

void Paddle::InitializeActions()
{
    
}

float32 Paddle::Width()
{
    return _paddleSprite->boundingBox().size.width;
}

float32 Paddle::Height()
{
    return _paddleSprite->boundingBox().size.height;
}

void Paddle::SetVisible(bool value)
{
    _paddleSprite->setVisible(value);
}

bool Paddle::Visible()
{
    return _paddleSprite->isVisible();
}

void Paddle::Update(float t)
{
    GameElement::Update(t);
						
    b2Vec2 pos = _paddleBody->GetPosition();
			
    float32 x = pos.x * PhysicsWorld::PhysScale();
    float32 y = pos.y * PhysicsWorld::PhysScale();
    
    _paddleSprite->setPosition( CCPointMake(x, y) );
    _paddleSprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(_paddleBody->GetAngle()) );
}

void Paddle::Destroy()
{
    CleanupPhysics();
}