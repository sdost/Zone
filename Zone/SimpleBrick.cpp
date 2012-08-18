//
//  SimpleBrick.cpp
//  Zone
//
//  Created by Samuel Dost on 8/11/12.
//
//

#include "SimpleBrick.h"
#include "DisintegrateBrickAction.h"

using namespace cocos2d;

void SimpleBrick::Init(CCLayer* scene, int width, int height)
{
    Brick::Init(width, height, "MedYellow");
}

void SimpleBrick::InitializeActions()
{
    Brick::InitializeActions();
}

bool SimpleBrick::NotifyHit(int damage)
{
    if(Brick::NotifyHit(damage))
    {
        DisintegrateBrickAction* action = new DisintegrateBrickAction();
        action->Init(DisintegrateBrickAction::NAME, this);
        AddAction(action);
        ActivateAction(DisintegrateBrickAction::NAME);
        return true;
    }
    
    return false;
}

void SimpleBrick::Destroy()
{
    RemoveAction(DisintegrateBrickAction::NAME);

    Brick::Destroy();
}