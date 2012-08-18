#ifndef _GAME_CONTACT_LISTENER_H_
#define _GAME_CONTACT_LISTENER_H_

#include "box2D.h"
#include <vector>

struct GameContact
{
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    b2Vec2 point;
    bool operator==(const GameContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};


class GameContactListener : public b2ContactListener
{
public:
    std::vector<GameContact> _contacts;
    
    GameContactListener();
    ~GameContactListener();
    
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);    
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
private:
};

#endif