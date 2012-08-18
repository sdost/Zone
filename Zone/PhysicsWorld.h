#ifndef _PHYSICS_WORLD_H_
#define _PHYSICS_WORLD_H_

#include "cocos2d.h"
#include "Box2D.h"

class PhysicsWorld
{
public:
    static void InitializePhysics();
    static void SetContactListener(b2ContactListener* listener);
    static void DrawDebugData();
    static float32 TimeStep();
    static float32 PhysScale();
    static b2Body* CreateBody( const b2BodyDef* def );
    static b2Joint* CreateJoint( const b2JointDef* def );
    static void UpdateWorld();
    static void DestroyBody( b2Body* body );
    static void DestroyJoint( b2Joint* joint );
    static void DestroyWorld();
    static bool Exists();
    static bool IsLocked();
private:
    static b2World* _world;
    static b2Draw* _debug;
    static bool _doSleep;
    static float32 _lastUpdate;
    static float32 _timeStep;
    static int32 _velIterations;
    static int32 _posIterations;
    static float32 _physScale;
};

#endif