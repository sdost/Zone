#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "GameElement.h"
#include "box2d.h"
#include "cocos2d.h"

class Paddle : public GameElement
{
private:
    cocos2d::CCSprite* _paddleSprite;
    b2Body* _paddleBody;
    b2Fixture* _paddleFixture;
protected:
    void InitializeDisplay(cocos2d::CCLayer* scene);
    void CreateAnimations();
    void InitializePhysics();
    void CleanupPhysics();
    void InitializeActions();
public:
    Paddle() {};
    void Init(cocos2d::CCLayer* scene);
    cocos2d::CCSprite* Sprite()
    {
        return _paddleSprite;
    };
    b2Body* Body()
    {
        return _paddleBody;
    };
    b2Fixture* Fixture()
    {
        return _paddleFixture;
    };
    float32 Width();
    float32 Height();
    void SetVisible(bool value);
    bool Visible();
    void Update(float t);
    void Destroy();
};

#endif