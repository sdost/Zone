#ifndef _GRID_H_
#define _GRID_H_

#include "cocos2d.h"
#include "GameElement.h"
#include <vector>
#include <list>
#include "box2d.h"
#include "AppSettings.h"

class GridObject;

class Grid : public GameElement
{
private:
    cocos2d::CCNode* _gridNode;
    b2Body* _gridBody;
    int _gridWidth;
    int _gridHeight;
    int _shift;
    std::vector<GridObject *> _gridObjectList;
    std::vector<GridObject *> _gridRemoveList;
    //std::map<GridObject, std::string> _collectables;
    std::vector<GridObject *> _grid;
    int _count;
    bool _empty;
    int _currentIndex;
protected:
    void Generate();
    void InitializeDisplay();
    void InitializeActions();
    void InitializePhysics();
    void CleanupPhysics();
public:
    Grid() {};
    void Init(int width, int height);
    cocos2d::CCNode* GridNode()
    {
        return _gridNode;
    }
    b2Body* GridBody()
    {
        return _gridBody;
    }
	int GridWidth()
    {
        return _gridWidth;
    }
	int GridHeight()
    {
        return _gridHeight;
    }
    bool AddGridObject(GridObject &obj, int x, int y);
    bool RemoveGridObject(GridObject* obj);
    GridObject* GetGridObjectAt(int x, int y);
    std::vector<GridObject *> GridObjectList()
    {
        return _gridObjectList;
    };
    bool IsEmpty()
    {
        return _empty;
    };
    void Update(float t);
    void Clear();
    void Destroy();
};

#endif