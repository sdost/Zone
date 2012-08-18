#ifndef _GAME_VIEW_H_
#define _GAME_VIEW_H_

#define COCOS2D_DEBUG 1

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "box2D.h"
#include "Ball.h"
#include "Paddle.h"
#include "Grid.h"
#include "PhysicsWorld.h"
#include "GameContactListener.h"
#include "SimpleAudioEngine.h"

class GameView : public cocos2d::CCLayer {
public:
    ~GameView();
    GameView();
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void setupSounds();
    void handleBallCollision(b2Fixture* a, b2Fixture* b, b2Vec2 p);
    virtual void draw();
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void tick(cocos2d::CCTime dt);
    
    static const unsigned int id_Ball = 0x0002;
    static const unsigned int id_Brick = 0x0004;
    static const unsigned int id_Paddle = 0x0008;
    static const unsigned int id_Bullet = 0x000F;
    static const unsigned int id_Collectable = 0x0020;
    static const unsigned int id_Wall = 0x0040;

private:
    b2Body *_groundBody;
    b2Fixture *_bottomFixture;
    Ball *_ball;
    Grid *_grid;
    Paddle *_paddle;
    
    b2MouseJoint *_mouseJoint;
    
    GameContactListener *_contactListener;
};

#endif