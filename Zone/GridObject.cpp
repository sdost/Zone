//
//  GridObject.cpp
//  BreakoutCocos2D-x
//
//  Created by Samuel Dost on 7/29/12.
//
//

#include "Grid.h"
#include "GridObject.h"
#include "RemoveGridObjectAction.h"

void GridObject::Init(int width, int height)
{
    _gridWidth = width;
    _gridHeight = height;
    
    InitializeActions();
}

void GridObject::InitializeActions()
{
    RemoveGridObjectAction* action = new RemoveGridObjectAction();
    action->Init(RemoveGridObjectAction::NAME, this);
    AddAction(action);
}

void GridObject::AddToGrid(class Grid* grid, int x, int y)
{
    _grid = grid;
    _gridX = x;
    _gridY = y;
}

void GridObject::Update(float t)
{
    GameElement::Update(t);
}
		
void GridObject::RemoveFromGrid()
{
    _grid = NULL;
    _gridX = 0;
    _gridY = 0;
}
		
void GridObject::Destroy()
{
    RemoveAction(RemoveGridObjectAction::NAME);
}