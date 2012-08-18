#ifndef _REMOVE_GRID_OBJECT_ACTION_H_
#define _REMOVE_GRID_OBJECT_ACTION_H_

#include "Action.h"

class RemoveGridObjectAction : public Action
{

public:
    RemoveGridObjectAction() : Action() {};
    static std::string NAME;
    void StartAction();
};

#endif