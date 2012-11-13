#ifndef _GAME_ELEMENT_H_
#define _GAME_ELEMENT_H_

#import <map>
#import <string>
#import <vector>
#import <list>
#import "Action.h"
#import "cocos2d.h"

typedef std::list<Action*> ActionList;

class GameElement : public cocos2d::CCObject
{
public:
    GameElement() {};
    Action* AddAction( Action* a );
    void ActivateAction(std::string name);
    void DeactivateAction(std::string name);
    void RemoveAction(std::string name);
    virtual void Update(float t);
    bool Active();
    virtual void Reset();
protected:
    ActionList _actions;
    ActionList _actionsQueued;
    ActionList _actionsActive;
};

class ActionNameMatches
{
    std::string _name;
public:
    ActionNameMatches(std::string aName) : _name(aName) {}
 
    // operator() is what's called when you do NumEquals()
    bool operator()(Action* a)
    {
        return a->ActionName() == _name;
    };
};

#endif
