#ifndef _GRID_OBJECT_H_
#define _GRID_OBJECT_H_

#include "GameElement.h"

class Grid;

class GridObject : public GameElement
{
protected:
    Grid* _grid;

    int _gridX;
    int _gridY;

    int _gridWidth;
    int _gridHeight;
    virtual void InitializeActions();
public:
    GridObject() {};
    virtual void Init(int width, int height);
    int GridWidth()
    {
        return _gridWidth;
    };
    int GridHeight()
    {
        return _gridHeight;
    };
    int GridX()
    {
        return _gridX;
    };
    int GridY()
    {
        return _gridY;
    };
    Grid* Grid()
    {
        return _grid;
    };
    virtual void AddToGrid(class Grid* grid, int x, int y);
    virtual void Update(float t);
    virtual void RemoveFromGrid();
    virtual void Destroy();
};

#endif