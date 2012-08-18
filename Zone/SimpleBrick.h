#ifndef _SIMPLE_BRICK_H_
#define _SIMPLE_BRICK_H_

#import "Brick.h"

class SimpleBrick : public Brick
{
public:
    SimpleBrick() : Brick() {}
    void Init(cocos2d::CCLayer* scene, int width, int height);
    bool NotifyHit(int damage);
    void Destroy();
protected:
    void InitializeActions();
};

#endif