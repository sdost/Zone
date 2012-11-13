//
//  RemoveGridObjectAction.cpp
//  BreakoutCocos2D-x
//
//  Created by Samuel Dost on 8/6/12.
//
//
#include "Grid.h"
#include "GridObject.h"
#include "RemoveGridObjectAction.h"

std::string RemoveGridObjectAction::NAME = "REMOVE_GRID_OBJECT_ACTION";

void RemoveGridObjectAction::StartAction()
{
    Action::StartAction();
    
    Grid* grid = ((GridObject*) _gameElement)->Grid();
    
    if ( grid )
    {
        grid->RemoveGridObject( (GridObject *)_gameElement );
    }
			
    SetFinished(true);
}