#ifndef _DISINTEGRATE_BRICK_H_
#define _DISINTEGRATE_BRICK_H_

#include "Action.h"

class DisintegrateBrickAction : public Action
{
public:
    static std::string NAME;
    DisintegrateBrickAction() : Action() {};
    void StartAction();
    void FinishAction();
};

#endif