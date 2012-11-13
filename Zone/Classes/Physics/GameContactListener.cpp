//
//  MyContactListener.cpp
//  BreakoutCocos2D-x
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "PhysicsWorld.h"
#include "GameContactListener.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "AppSettings.h"
#include <typeinfo>

GameContactListener::GameContactListener() : _contacts()
{
}

GameContactListener::~GameContactListener()
{
}

void GameContactListener::BeginContact(b2Contact* contact) 
{
    //b2WorldManifold* wm;
    //contact->GetWorldManifold(wm);
		
	//b2Vec2 point = wm->points[0];
		
    //if ( contact->IsEnabled() )
    //{
    GameContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(myContact);
    //}
}

void GameContactListener::EndContact(b2Contact* contact) 
{
    GameContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<GameContact>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), myContact);
    if (pos != _contacts.end()) 
    {
        _contacts.erase(pos);
    }
}

void GameContactListener::PreSolve(b2Contact* contact, 
                                 const b2Manifold* oldManifold) 
{
    /*
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
		
    if (typeof(fixtureA->GetUserData()) == "Brick" && typeof(fixtureB->GetUserData()) == "Ball")
    {
        if ( fixtureB->GetUserData()->ballMode == Ball.DESTRUCT_BALL )
        {
            //contact.SetSensor(true);
        }
    }
    
    if (!(typeid(Paddle) == typeid(fixtureA->GetUserData()) && typeid(Ball) == typeid(fixtureB->GetUserData())))
        return;
		
    b2Vec2 positionPaddle = fixtureA->GetBody()->GetPosition();
    b2Vec2 positionBall = fixtureB->GetBody()->GetPosition();
		
    Paddle* paddle = (Paddle *)fixtureA->GetUserData();
    //Ball* ball = (Ball *)fixtureB->GetUserData();
    float heightPhys = paddle->Height() / PhysicsWorld::PhysScale();
		
    if (positionBall.y > (positionPaddle.y - heightPhys / 2))
    {
        contact->SetEnabled(false);
    }
    */
}

void GameContactListener::PostSolve(b2Contact* contact, 
                                  const b2ContactImpulse* impulse) 
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
		
    if(!(dynamic_cast<Paddle*>((GameElement *)fixtureA->GetUserData()) && dynamic_cast<Ball*>((GameElement *)fixtureB->GetUserData())))
        return;
		
    b2Vec2 paddle = fixtureA->GetBody()->GetPosition();
    b2Vec2 ball = fixtureB->GetBody()->GetPosition();
		
    float ballXDiff = ball.x - paddle.x;
		
    float extent = (dynamic_cast<Paddle*>((GameElement *)fixtureA->GetUserData())->Width() / 2) / PhysicsWorld::PhysScale();
				
    float ballXRatio = ballXDiff / (extent * 2);
		
    if (ballXRatio < -0.95) ballXRatio = -0.95;
    if (ballXRatio > 0.95) ballXRatio = 0.95;
		
    b2WorldManifold wm;
    contact->GetWorldManifold(&wm);
		
    b2Vec2 point = wm.points[0];
		
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);
		
    b2Vec2 newVel = vB;
    newVel.x = ballXRatio * AppSettings::sharedAppSettings()->getFloat("paddleReflectionMultiplier");
    	
    float solvedYVel = sqrt(abs(vB.LengthSquared() - (newVel.x * newVel.x)));
		
    newVel.y = solvedYVel;
		
    bodyB->SetLinearVelocity(newVel);
}