//
//  Grid.cpp
//  BreakoutCocos2D-x
//
//  Created by Samuel Dost on 7/29/12.
//
//

#include "Grid.h"
#include "GridObject.h"
#include "PhysicsWorld.h"

using namespace std;
using namespace cocos2d;

void Grid::Init(int width, int height)
{ 
    _gridWidth = width;
    _gridHeight = height;
			
    _shift = 0;
    int minLength = _gridWidth * _gridHeight;
    int powOfTwo = 1;
    while ( powOfTwo < minLength )
    {
        powOfTwo *= 2;
        _shift++;
    }
    
    _grid.resize(100 << _shift, NULL);
    		
    _count = 0;
		
    //Generate();
			
    _empty = false;
			
    _currentIndex = 0;
    
    InitializeDisplay();
    InitializeActions();
    InitializePhysics();
}

void Grid::InitializeDisplay()
{
    _gridNode = new CCNode();
    _gridNode->setPosition( ccp(0, 0) );
}

void Grid::InitializeActions()
{
    
}

void Grid::InitializePhysics()
{
    if ( !(PhysicsWorld::Exists()) ) return;
	
    b2BodyDef def = b2BodyDef();
    def.type = b2_staticBody;
    def.userData = this;
			
    _gridBody = PhysicsWorld::CreateBody(&def);
}

void Grid::CleanupPhysics()
{
    if ( !(PhysicsWorld::Exists()) ) return;
			
    PhysicsWorld::DestroyBody(_gridBody);
    _gridBody->SetUserData(NULL);
    _gridBody = NULL;
}

void Grid::Generate()
{
    for ( int i = 0; i < _grid.size(); i++)
    {
        _grid[i] = NULL;
    }
}

bool Grid::AddGridObject(GridObject &obj, int posx, int posy)
{
    if ( _gridObjectList.size() >= AppSettings::sharedAppSettings()->getInt("maxGridObjects") ) return false;
			
    int rightBounds = posx + obj.GridWidth();
    int bottomBounds = posy + obj.GridHeight();
			
    if ( posx < 0 ) return false;
			
    if ( posy < 0 ) return false;
			
    if ( rightBounds > _gridWidth ) return false;
			
    if ( bottomBounds > _gridHeight ) return false;
			
    int x, y;
    
    for ( x = posx; x < rightBounds; x++ )
    {
        for ( y = posy; y < bottomBounds; y++ )
        {
            int pos = (x << _shift) | y;
        
            GridObject * g = _grid[pos];
        
            if ( g != NULL )
                return false;
        }
    }
			
    _gridObjectList.push_back(&obj);
    obj.AddToGrid(this, posx, posy);
			
    for ( x = posx; x < rightBounds; x++ )
    {
        for ( y = posy; y < bottomBounds; y++ )
        {
            _grid[(x << _shift) | y] = &obj;
        }
    }
			
    return true;
}

bool Grid::RemoveGridObject(GridObject* obj)
{
    const bool is_in = (std::find(_gridObjectList.begin(), _gridObjectList.end(), obj) != _gridObjectList.end());
    if (!is_in) return false;
			
    int rightBounds = obj->GridX() + obj->GridWidth();
    int bottomBounds = obj->GridY() + obj->GridHeight();
			
    int x, y;
    
    for ( x = obj->GridX(); x < rightBounds; x++ )
    {
        for ( y = obj->GridY(); y < bottomBounds; y++ )
        {
            _grid[(x << _shift) | y] = NULL;
        }
    }
			
    _gridRemoveList.push_back(obj);
			
    return true;
}

GridObject* Grid::GetGridObjectAt(int x, int y)
{
    if ( x < 0 || y < 0 ) return NULL;

    return _grid[(x << _shift) | y];
}

void Grid::Update(float t)
{
    GameElement::Update(t);
	
    std::vector<GridObject*>::iterator pos;
    for( pos = _gridRemoveList.begin(); pos != _gridRemoveList.end(); ++pos )
    {
        /*
        if ( _collectables[go] )
        {
            var xOffset:Number = (go.gridX + go.gridWidth/2) * AppSettings.instance.defaultTileWidth;
            var yOffset:Number = (go.gridY + go.gridHeight/2) * AppSettings.instance.defaultTileHeight;
					
            _collectableSpawner.initParams({ "type": _collectables[go], "xOffset": xOffset, "yOffset": yOffset });
            activateAction(SpawnCollectable.NAME);
					
            _collectables[go] = null;
        }
        */
        
		GridObject* go = *pos;
        go->RemoveFromGrid();
        go->Destroy();
    }
    
    _gridRemoveList.clear();
			
    _empty = true;
					
    for( pos = _gridObjectList.begin(); pos != _gridObjectList.end(); ++pos )
    {
        GridObject* go = *pos;
        go->Update(t);
        /*
        if ( obj is Brick )
        {
            if ( obj is NanoBrick || obj is UnbreakableBrick ) continue;
            else if ( obj is Portal )
            {
                (obj as Portal).checkPortal(_gridObjectList.toArray());
            }
            else _empty = false;
        }
        */
    }
}

void Grid::Clear()
{
    std::vector<GridObject*>::iterator pos;
    for( pos = _gridRemoveList.begin(); pos != _gridRemoveList.end(); ++pos )
    {
        GridObject* go = *pos;
        go->RemoveFromGrid();
        go->Destroy();
    }
			
    _gridObjectList.clear();
			
    _gridRemoveList.clear();
    //_collectables.clear();
			
    Generate();
			
    _empty = false;
}

void Grid::Destroy()
{
    CleanupPhysics();
}