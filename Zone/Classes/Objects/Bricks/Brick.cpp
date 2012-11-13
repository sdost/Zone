//
//  Brick.cpp
//  BreakoutCocos2D-x
//
//  Created by Samuel Dost on 8/2/12.
//
//

#include "Brick.h"
#include "PhysicsWorld.h"
#include "RemoveGridObjectAction.h"
#include "GameViewScene.h"
#include "AppSettings.h"

using namespace cocos2d;

void Brick::Init(int width, int height, std::string assets)
{
    GridObject::Init(width, height);
    
    _hitPoints = 1;
    
    InitializeDisplay(assets);
}

void Brick::InitializeDisplay(std::string assets)
{
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("brick_anim.plist", "brick_anim.png");
    
    //CreateAnimations();
    
    //CCAction* anim = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("MedBlue"));
    //CCAction* repeat = CCRepeatForever::create((CCSequence *)anim);
    
    // Create sprite and add it to the layer
    _brickSprite = CCSprite::create(
        CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(assets.append("0000").c_str()));
    //_brickSprite->runAction(repeat);
    //_brickSprite->setPosition(ccp(100, 100));
    //_brickSprite->setTag(2);
}

void Brick::CleanupDisplay()
{
    
}

void Brick::InitializePhysics()
{
    if(!(PhysicsWorld::Exists())) return;
    
    float b2Width = GridWidth() * AppSettings::sharedAppSettings()->getInt("defaultTileWidth");
	float b2Height = GridHeight() * AppSettings::sharedAppSettings()->getInt("defaultTileHeight");
			
    float b2X = GridX() * AppSettings::sharedAppSettings()->getInt("defaultTileWidth") + b2Width / 2;
    float b2Y = GridY() * AppSettings::sharedAppSettings()->getInt("defaultTileHeight") + b2Height / 2;
			
    b2PolygonShape shape;
    shape.SetAsBox(
        (b2Width / PhysicsWorld::PhysScale()) / 2,
        (b2Height / PhysicsWorld::PhysScale()) / 2,
        b2Vec2(b2X / PhysicsWorld::PhysScale(), (480 - b2Y) / PhysicsWorld::PhysScale()),
        0);
    		
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.1f;
    fixtureDef.filter.categoryBits = GameView::id_Brick;
    fixtureDef.filter.maskBits = GameView::id_Ball | GameView::id_Bullet | GameView::id_Collectable;
    fixtureDef.userData = this;
    _brickFixture = _grid->GridBody()->CreateFixture(&fixtureDef);
}

void Brick::CleanupPhysics()
{
    if(!(PhysicsWorld::Exists())) return;
    
    if( _grid )
    {
        _brickFixture->SetUserData(NULL);
        _grid->GridBody()->DestroyFixture(_brickFixture);
        _brickFixture = NULL;
    }
}

void Brick::InitializeActions()
{
    GridObject::InitializeActions();
}

void Brick::AddToGrid(class Grid* grid, int x, int y)
{
    GridObject::AddToGrid(grid, x, y);
    
    InitializePhysics();
    
    _grid->GridNode()->addChild(_brickSprite);
    float b2Width = GridWidth() * AppSettings::sharedAppSettings()->getInt("defaultTileWidth");
	float b2Height = GridHeight() * AppSettings::sharedAppSettings()->getInt("defaultTileHeight");
			
    float b2X = GridX() * AppSettings::sharedAppSettings()->getInt("defaultTileWidth") + b2Width / 2;
    float b2Y = GridY() * AppSettings::sharedAppSettings()->getInt("defaultTileHeight") + b2Height / 2;
    _brickSprite->setPosition( CCPointMake(b2X, 480 - b2Y) );
}

void Brick::RemoveFromGrid()
{
    CleanupPhysics();
    
    _grid->GridNode()->removeChild(_brickSprite, true);
    
    CleanupDisplay();

    GridObject::RemoveFromGrid();
}

bool Brick::NotifyHit(int dmg)
{
    _hitPoints -= dmg;
    
    if( _hitPoints <= 0 )
    {
        ActivateAction(RemoveGridObjectAction::NAME);
        return true;
    }
    
    return false;
}

void Brick::Update(float t)
{
    GridObject::Update(t);
}

void Brick::Destroy()
{
    GridObject::Destroy();
    
    GridObject::Reset();
}