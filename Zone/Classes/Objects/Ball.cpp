#include "Ball.h"
#include "PhysicsWorld.h"
#include "AppSettings.h"
#include <limits>
#include "GameViewScene.h"

using namespace cocos2d;

void Ball::Init(CCLayer* scene)
{
    _ballMode = NORMAL_BALL;
    
    _maxSpeed = 10;
    
    _damagePoints = 1;
    
    _speed = AppSettings::sharedAppSettings()->getFloat("defaultBallInitialSpeed");
    _minSpeed = AppSettings::sharedAppSettings()->getFloat("defaultBallMinSpeed");
    _maxSpeed = AppSettings::sharedAppSettings()->getFloat("defaultBallMaxSpeed");
    
    InitializeDisplay(scene);
    InitializePhysics();
    InitializeActions();
}

void Ball::InitializeDisplay(cocos2d::CCLayer* scene)
{
    CCAnimation* animation = CreateAnimations();
    animation->setDelayPerUnit(0.02);
    animation->setRestoreOriginalFrame(true);
    
    // Create sprite and add it to the layer
    _ballSprite = CCSprite::create();
    
    CCAction* repeat = CCRepeatForever::create(CCAnimate::create(animation));
    _ballSprite->runAction(repeat);
    scene->addChild(_ballSprite, 10);
    
    /*
    _ballTrail = CCParticleSmoke::create();
    _ballTrail->retain();
    scene->addChild(_ballTrail, 5);
    _ballTrail->setScaleX(0.1);
    _ballTrail->setScaleY(0.1);
    _ballTrail->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png") );
    */
}

CCAnimation* Ball::CreateAnimations()
{
    std::string animFile = AppSettings::sharedAppSettings()->getString("ballAnimationSet");
    CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile(animFile.c_str());
    
    return CCAnimationCache::sharedAnimationCache()->animationByName("BALL_NORMAL");
}
		
void Ball::InitializePhysics()
{
    if ( !(PhysicsWorld::Exists()) ) return;
	
    // Create ball body
    b2BodyDef def = b2BodyDef();
    def.type = b2_dynamicBody;
    def.position.Set(20/PhysicsWorld::PhysScale(), 40/PhysicsWorld::PhysScale());
    def.userData = this;
    
    _ballBody = PhysicsWorld::CreateBody(&def);

    // Create circle shape
    b2CircleShape circle;
    circle.m_radius = (_ballSprite->getContentSize().width / 2) / PhysicsWorld::PhysScale();
    
    // Create shape definition and add body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.f;
    ballShapeDef.restitution = 1.0f;
    ballShapeDef.userData = this;
    ballShapeDef.filter.categoryBits = GameView::id_Ball;
    ballShapeDef.filter.maskBits = GameView::id_Brick | GameView::id_Paddle | GameView::id_Wall | GameView::id_Ball | GameView::id_Collectable;
    _ballFixture = _ballBody->CreateFixture(&ballShapeDef);
}
		
void Ball::CleanupPhysics()
{
    if ( !PhysicsWorld::Exists() ) return;
			
    _ballFixture->SetUserData(NULL);
    PhysicsWorld::DestroyBody(_ballBody);
    _ballBody->SetUserData(NULL);
    _ballBody = NULL;
}
		
void Ball::InitializeActions()
{
    // addAction( new DestructoballAction(this, {"time":AppSettings.instance.defaultDestructoballTimer} ) );
    // addAction( new InvinciballAction(this, {"time":AppSettings.instance.defaultInvinciballTimer}) );
}

float32 Ball::Width()
{
    return _ballSprite->getContentSize().width;
}

float32 Ball::Height()
{
    return _ballSprite->getContentSize().height;
}
		
void Ball::SetSleeping(bool sleep)
{
    _sleeping = sleep;
			
    if ( _sleeping )
    {
        _ballBody->SetLinearDamping(numeric_limits<float32>::max());
    }
    else
    {
        _ballBody->SetLinearDamping(0.0f);
    }
}

void Ball::SetVisible(bool value)
{
    _ballSprite->setVisible(value);
}

bool Ball::Visible()
{
    return _ballSprite->isVisible();
}

void Ball::Update(float t)
{
    GameElement::Update(t);

    b2Vec2 pos = _ballBody->GetPosition();
    
    float32 x = pos.x * PhysicsWorld::PhysScale();
    float32 y = pos.y * PhysicsWorld::PhysScale();
			
    _ballSprite->setPosition( CCPointMake(x, y) );
    //_ballTrail->setPosition( CCPointMake(x, y) );
    		
    if (_sleeping) return;
    
    b2Vec2 bodyVelocity = _ballBody->GetLinearVelocity();
    
    float diff = _speed - bodyVelocity.Length();
    
    bodyVelocity.Normalize();
    bodyVelocity *= diff;
    _ballBody->ApplyLinearImpulse(bodyVelocity, _ballBody->GetWorldCenter());
		
    bodyVelocity = _ballBody->GetLinearVelocity();
		
    if (abs(bodyVelocity.x) <= AppSettings::sharedAppSettings()->getFloat("ballTrajectoryThreshold"))
    {
        _ballBody->ApplyForce(
            b2Vec2(AppSettings::sharedAppSettings()->getFloat("ballTrajectoryAdjustFactor") * _ballBody->GetMass(), 0),
            _ballBody->GetWorldCenter());
    }
			
    if (abs(bodyVelocity.y) <= AppSettings::sharedAppSettings()->getFloat("ballTrajectoryThreshold"))
    {
        _ballBody->ApplyForce(
            b2Vec2(0, AppSettings::sharedAppSettings()->getFloat("ballTrajectoryAdjustFactor") * _ballBody->GetMass()),
            _ballBody->GetWorldCenter());
    }
}
		
void Ball::Destroy()
{
    CleanupPhysics();
    
    /*
    if ( _ballMode == DESTRUCT_BALL )
    {
        this.deactivateAction(InvinciballAction.NAME);
    }
			
    removeAction(DestructoballAction.NAME);
    removeAction(InvinciballAction.NAME);
	*/
    
    Reset();
}