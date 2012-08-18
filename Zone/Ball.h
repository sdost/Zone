#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"
#include "Box2D.h"
#include "GameElement.h"

enum BallMode { NORMAL_BALL, SUPER_BALL, DESTRUCT_BALL };

class Ball : public GameElement
{
private:
    // Create sprite and add it to the layer
	cocos2d::CCSprite* _ballSprite;
    cocos2d::CCParticleSmoke* _ballTrail;
    cocos2d::CCAnimate* _ballAnimation;
    b2Body* _ballBody;
    b2Fixture* _ballFixture;
	
    float _speed;
	float _minSpeed;
    float _maxSpeed;
		
    BallMode _ballMode;
		
	std::string _currentEffectAction;
		
	bool _sleeping;
		
	int _damagePoints;
protected:
    void InitializeDisplay(cocos2d::CCLayer* scene);
    cocos2d::CCAnimation* CreateAnimations();
	void InitializePhysics();
    void CleanupPhysics();
	void InitializeActions();
public:
    Ball() {};
    void Init(cocos2d::CCLayer* scene);
    cocos2d::CCSprite* Sprite()
    {
        return _ballSprite;
    };
    b2Body* Body()
    {
        return _ballBody;
    };
    b2Fixture* Fixture()
    {
        return _ballFixture;
    };
    float Speed()
    {
        return _speed;
    };
    float32 Width();
    float32 Height();
    void SetDamagePoints(int dmg)
    {
        _damagePoints = dmg;
    };
    int DamagePoints()
    {
        return _damagePoints;
    };
    void SetSleeping(bool sleep);
    bool Sleeping()
    {
        return _sleeping;
    };
    void SetVisible(bool value);
    bool Visible();
    
    void Update(float t);
    void Destroy();
};

#endif