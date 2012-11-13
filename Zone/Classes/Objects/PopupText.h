#ifndef _POPUP_TEXT_H_
#define _POPUP_TEXT_H_

#include "GameElement.h"
#include "cocos2d.h"

class PopupText : public GameElement
{
private:
    cocos2d::CCLabelBMFont* _font;
    float _fadeTime;
	float _elapTime;
    cocos2d::ccColor3B _color;
		
	float _scale;
	float _alpha;
		
	float _strength;
	bool _complete;
public:
    PopupText() {};
    void Init(cocos2d::CCLayer* scene, std::string text, cocos2d::CCPoint pos);
    void Update(float t);
    void Destroy();
    bool IsComplete()
    {
        return _complete;
    };
};

#endif