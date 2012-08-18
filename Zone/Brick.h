#ifndef _BRICK_H_
#define _BRICK_H_

#include "cocos2d.h"
#include "box2d.h"
#include "Grid.h"
#include "GridObject.h"

class Brick : public GridObject
{
private:
    int _hitPoints;
protected:
    cocos2d::CCSprite* _brickSprite;
    b2Fixture* _brickFixture;
    void InitializeDisplay(std::string assets);
    void CleanupDisplay();
    cocos2d::CCAnimation* CreateAnimations();
    virtual void InitializeActions();
    void InitializePhysics();
    void CleanupPhysics();
public:
    Brick() {};
    void Init(int width, int height, std::string assets);
    void AddToGrid(class Grid *, int x, int y);
    void RemoveFromGrid();
    b2Fixture* Fixture()
    {
        return _brickFixture;
    }
    cocos2d::CCSprite* Sprite()
    {
        return _brickSprite;
    }
    int Width()
    {
        return _brickSprite->getContentSize().width;
    }
    int Height()
    {
        return _brickSprite->getContentSize().height;
    }
    int HitPoints()
    {
        return _hitPoints;
    }
    void SetHitPoints(int hp)
    {
        _hitPoints = hp;
    }
    virtual bool NotifyHit(int damage);
    void Update(float t);
    virtual void Destroy();
};

#endif