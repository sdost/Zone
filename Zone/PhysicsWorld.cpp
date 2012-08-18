#include "PhysicsWorld.h"
#include "GameElement.h"
#include "GLES-Render.h"

using namespace cocos2d;

#define PTM_RATIO 32

b2World* PhysicsWorld::_world;
bool PhysicsWorld::_doSleep = false;
float32 PhysicsWorld::_lastUpdate = 0.0f;
float32 PhysicsWorld::_timeStep = 1.0f / 60.0f;
int32 PhysicsWorld::_velIterations = 3;
int32 PhysicsWorld::_posIterations = 8;
float32 PhysicsWorld::_physScale = 25.0f;

void PhysicsWorld::InitializePhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    _world = new b2World( gravity );
    _world->SetAllowSleeping(false);
    
    GLESDebugDraw* b2dDebugDraw = new GLESDebugDraw( _physScale );
    _world->SetDebugDraw(b2dDebugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    b2dDebugDraw->SetFlags(flags);
}

void PhysicsWorld::SetContactListener(b2ContactListener* listener)
{
    _world->SetContactListener(listener);
}

void PhysicsWorld::DrawDebugData()
{
    _world->DrawDebugData();
}

float32 PhysicsWorld::PhysScale()
{
    return _physScale;
}

b2Body* PhysicsWorld::CreateBody(const b2BodyDef* def)
{
    return _world->CreateBody(def);
}

b2Joint* PhysicsWorld::CreateJoint(const b2JointDef *def)
{
    return _world->CreateJoint(def);
}

void PhysicsWorld::UpdateWorld()
{
    if( _world )
    {
        _world->Step(_timeStep, _velIterations, _posIterations);
        
        //Iterate over the bodies in the physics world
        for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
        {
            if (b->GetUserData() != NULL)
            {
                GameElement* myActor = (GameElement*)b->GetUserData();
                myActor->Update(_timeStep);
            }
        }
    }
}

void PhysicsWorld::DestroyBody(b2Body *body)
{
    _world->DestroyBody(body);
}

void PhysicsWorld::DestroyJoint(b2Joint *joint)
{
    _world->DestroyJoint(joint);
}

void PhysicsWorld::DestroyWorld()
{
    delete _world;
}

bool PhysicsWorld::Exists()
{
    return (_world != NULL);
}

bool PhysicsWorld::IsLocked()
{
    return _world->IsLocked();
}