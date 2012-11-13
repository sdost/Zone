#ifndef _BRICK_MULTIPLIER_MANAGER_ACTION_H_
#define _BRICK_MULTIPLIER_MANAGER_ACTION_H_

#include "Action.h"

class BrickMultiplierManagerAction : public Action
{
public:
    static std::string NAME;
    BrickMultiplierManagerAction() : Action() {};
    void StartAction();
    void FinishAction();
};

#endif