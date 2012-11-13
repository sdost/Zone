//
//  PopupText.cpp
//  Zone
//
//  Created by Samuel Dost on 8/18/12.
//
//

#include "PopupText.h"
#include "AppSettings.h"

using namespace cocos2d;

void PopupText::Init(cocos2d::CCLayer* scene, std::string text, CCPoint pos)
{
    _scale = 0.1;
    _alpha = 1.0;
			
    _strength = 1;
			
    int intensity = 255 / 3 * _strength + (2 * 255 / 3);
			
    if( _strength < 1 )
        _color = ccc3(intensity, intensity, intensity);
    else
    {
        float r = arc4random() % 255;
        float g = arc4random() % 255;
        float b = arc4random() % 255;
        _color = ccc3(r,g,b);
    }
			
    _complete = false;
    _elapTime = 0;
    _fadeTime = AppSettings::sharedAppSettings()->getFloat("popupTextLifetime") / 1000.0f;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    _font = CCLabelBMFont::create(text.c_str(), "entsans.fnt");
    _font->setOpacityModifyRGB(false);
    scene->addChild(_font, 100);
    _font->setColor(_color);
    _font->setPosition(pos);
    _font->setScale(0.5);
}

void PopupText::Update(float t)
{
    if(_elapTime > _fadeTime)
    {
        CCFiniteTimeAction* fade = CCFadeOut::create(0.2);
        CCFiniteTimeAction* call = CCCallFunc::create(this, callfunc_selector(PopupText::Destroy));
        CCAction* seq = CCSequence::create(fade, call);
        _font->runAction(seq);
        
        _complete = true;
        return;
    }
    
    _elapTime += t;
    
    int intensity = 255 / 3 * _strength + (2 * 255 / 3);
			
    if( _strength < 1 )
        _color = ccc3(intensity, intensity, intensity);
    else
    {
        float r = arc4random() % 255;
        float g = arc4random() % 255;
        float b = arc4random() % 255;
        _color = ccc3(r,g,b);
    }
    
    _font->setColor(_color);
}

void PopupText::Destroy()
{
    _font->removeFromParentAndCleanup(true);
}