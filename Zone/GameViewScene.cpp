//
//  GameViewScene.cpp
//  BreakoutCocos2D-x
//
//  Created by Clawoo on 9/15/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#include "GameViewScene.h"
#include "Ball.h"
#include "SimpleBrick.h"
#include "AppSettings.h"
#include <typeinfo>
#include <iostream>

using namespace cocos2d;
using namespace CocosDenshion;

GameView::~GameView()
{
    _groundBody = NULL;
    delete _contactListener;
}

GameView::GameView()
{
    setTouchEnabled( true );
    setupSounds();
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gameassets_sheet.plist", "gameassets_sheet.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("brickassets_sheet.plist", "brickassets_sheet.png");
    
	PhysicsWorld::InitializePhysics();
    
    // Create edges around the entire screen
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	_groundBody = PhysicsWorld::CreateBody(&groundBodyDef);
    
    b2FixtureDef fixture;
    fixture.restitution = 1.0;
    fixture.filter.categoryBits = GameView::id_Wall;
    fixture.filter.maskBits = GameView::id_Ball | GameView::id_Bullet | GameView::id_Collectable | GameView::id_Paddle;
    //fixture.isSensor = false;
    //fixture.userData = NULL;
	
	// Define the ground box shape.
	b2EdgeShape groundBox;
	
	// bottom
    groundBox.Set(b2Vec2(0,0), b2Vec2(winSize.width/PhysicsWorld::PhysScale(),0));
    fixture.shape = &groundBox;
    _bottomFixture = _groundBody->CreateFixture(&fixture);
	
	// top
    groundBox.Set(b2Vec2(0,winSize.height/PhysicsWorld::PhysScale()), b2Vec2(winSize.width/PhysicsWorld::PhysScale(),winSize.height/PhysicsWorld::PhysScale()));
	fixture.shape = &groundBox;
    _groundBody->CreateFixture(&fixture);
	
	// left
    groundBox.Set(b2Vec2(0,winSize.height/PhysicsWorld::PhysScale()), b2Vec2(0,0));
	fixture.shape = &groundBox;
    _groundBody->CreateFixture(&fixture);
	
	// right
	groundBox.Set(b2Vec2(winSize.width/PhysicsWorld::PhysScale(),winSize.height/PhysicsWorld::PhysScale()), b2Vec2(winSize.width/PhysicsWorld::PhysScale(),0));
    fixture.shape = &groundBox;
	_groundBody->CreateFixture(&fixture);
    
    _ball = new Ball();
    _ball->Init(this);
    
    b2Vec2 force = b2Vec2(10,10);
    b2Vec2 point = b2Vec2(100/PhysicsWorld::PhysScale(), 100/PhysicsWorld::PhysScale());
    
    (_ball->Body())->ApplyLinearImpulse(force, point);
    
    _paddle = new Paddle();
    _paddle->Init(this);
    
    // Restrict paddle along the x axis
    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected = true;
    jointDef.Initialize(_paddle->Body(), _groundBody,
                        (_paddle->Body())->GetWorldCenter(), worldAxis);
    PhysicsWorld::CreateJoint(&jointDef);

    // in C++ you need to initialize objects to NULL
    _mouseJoint = NULL;
    
    // Create contact listener
    _contactListener = new GameContactListener();
    PhysicsWorld::SetContactListener(_contactListener);
    
    _grid = new Grid();
    _grid->Init(
        AppSettings::sharedAppSettings()->getInt("defaultGridWidth"),
        AppSettings::sharedAppSettings()->getInt("defaultGridHeight")
    );
    this->addChild(_grid->GridNode());
    
    int x = 0;
    int y = 0;
    for(int i = 0; i < 200; i++)
    {
        SimpleBrick* b = new SimpleBrick();
        b->Init(this, 4, 2);
        x = i / 20 * 4;
        y = i % 20 * 2;
        _grid->AddGridObject((*b), x, y);
    }
    
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.caf");
    
    this->schedule(schedule_selector(GameView::tick));
}

void GameView::setupSounds()
{
    std::string absPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("sound_list.plist");
    CCDictionary* fullSFX = CCDictionary::createWithContentsOfFileThreadSafe(absPath.c_str());
    CCDictionary* soundList = (CCDictionary*)fullSFX->objectForKey("sounds");
    
    CCDictElement* pElement;
    CCArray* arr;
    CCDICT_FOREACH(soundList, pElement)
    {
        // const char* key = pElement->getStrKey();
        arr = (CCArray*)pElement->getObject();
        
        for(int i = 0; i < arr->count(); i++)
        {
            absPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(((CCString*)arr->objectAtIndex(i))->getCString());
            CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(absPath.c_str());
        }
    }
}

void GameView::draw()
{
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    PhysicsWorld::DrawDebugData();

    kmGLPopMatrix();

    CHECK_GL_ERROR_DEBUG();
}

void GameView::handleBallCollision(b2Fixture* ballFixture, b2Fixture* fixture, b2Vec2 p)
{
    if( fixture == _bottomFixture )
    {
        
    }
    else if ( fixture->GetFilterData().categoryBits == GameView::id_Wall )
    {
        int v = ceil(rand() % 3 + 1);
        char buffer[50];
        sprintf(buffer, "wallcollision%d.wav", v);
        std::string absPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(buffer);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(absPath.c_str());
    }
    else if ( Paddle* paddle = dynamic_cast<Paddle*>((GameElement *)fixture->GetUserData()) )
    {
        /*
        if ( paddle->stickyMode && !a_fixture.GetUserData().occupied )
        {
            a_fixture.GetUserData().catchBall(a_ball.GetUserData() as Ball, false);
        }
        */
        //else
        {
            int v = ceil(rand() % 3 + 1);
            char buffer[50];
            sprintf(buffer, "paddlecollision%d.wav", v);
            std::string absPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(buffer);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(absPath.c_str());
        }
				
        /*
        if ( _paddleMultiplierManager.finished )
        {
            _multiplier.activateAction(PaddleMultiplierManagerAction.NAME);
        }
                            
        _paddleMultiplierManager.increaseMultiplier();
        */
    }
    else if( Brick* brick = dynamic_cast<Brick*>((GameElement*)fixture->GetUserData()))
    {
        Ball* ball = (Ball *)ballFixture->GetUserData();
        if ( brick->NotifyHit( ball->DamagePoints() ) )
        {
            /*
            if ( _brickMultiplierManager.finished )
            {
                _multiplier.activateAction(BrickMultiplierManagerAction.NAME)
            }
            */
					
            //_brickMultiplierManager.increaseMultiplier();
					
            //dispatchEvent( new ObjectEvent( "addPoints", { "basePoints": AppSettings.instance.brickPoints, "brickMult": _brickMultiplierManager.multiplier, "paddleMult": _paddleMultiplierManager.multiplier, "x": a_ball.GetUserData().x, "y": a_ball.GetUserData().y } ) );
        }
    }
}

void GameView::tick(CCTime dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
	
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	PhysicsWorld::UpdateWorld();
    
    std::vector<GameContact>::iterator pos;
    for(pos = _contactListener->_contacts.begin(); pos != _contactListener->_contacts.end(); ++pos)
    {
        GameContact contact = *pos;
        
        //_contactListener->_contacts.erase(pos);
        
        //if( contact.fixtureA->GetUserData() != NULL && contact.fixtureB->GetUserData() != NULL )
        {
            if( dynamic_cast<Ball*>((GameElement *)contact.fixtureA->GetUserData()) )
            {
                handleBallCollision(contact.fixtureA, contact.fixtureB, contact.point);
                continue;
            }
        
            if( dynamic_cast<Ball*>((GameElement *)contact.fixtureB->GetUserData()) )
            {
                handleBallCollision(contact.fixtureB, contact.fixtureA, contact.point);
                continue;
            }
        }
    }
}

void GameView::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    if (_mouseJoint != NULL) return;
    
    CCTouch *myTouch = (CCTouch *)touches->anyObject();
    CCPoint location = myTouch->locationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    b2Vec2 locationWorld = b2Vec2(location.x/PhysicsWorld::PhysScale(), location.y/PhysicsWorld::PhysScale());
    
    if ((_paddle->Fixture())->TestPoint(locationWorld)) {
        b2MouseJointDef md;
        md.bodyA = _groundBody;
        md.bodyB = _paddle->Body();
        md.target = locationWorld;
        md.collideConnected = true;
        md.maxForce = 1000.0f * _paddle->Body()->GetMass();
        
        _mouseJoint = (b2MouseJoint *)PhysicsWorld::CreateJoint(&md);
        _paddle->Body()->SetAwake(true);
    }
}

void GameView::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    if (_mouseJoint == NULL) return;
    
    CCTouch *myTouch = (CCTouch *)touches->anyObject();
    CCPoint location = myTouch->locationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    b2Vec2 locationWorld = b2Vec2(location.x/PhysicsWorld::PhysScale(), location.y/PhysicsWorld::PhysScale());

    _mouseJoint->SetTarget(locationWorld);
}

void GameView::ccTouchesCancelled(CCSet* touches, CCEvent* event)
{
    if (_mouseJoint) 
    {
        PhysicsWorld::DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }
}

void GameView::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    if (_mouseJoint) 
    {
        PhysicsWorld::DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }  
}

CCScene* GameView::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new GameView();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
