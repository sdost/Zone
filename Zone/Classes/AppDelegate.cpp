//
//  ___PROJECTNAMEASIDENTIFIER___AppDelegate.cpp
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//

#include "AppDelegate.h"
#include "AppSettings.h"
#include "cocos2d.h"
#include "GameViewScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    AppSettings::sharedAppSettings()->initWithPlistFile("config.plist");
    
    char buffer[50];
    for(int i = 1; i <= 4; i++)
    {
        sprintf(buffer, "brickbig%d.wav", i);
        std::string absPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(buffer);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(absPath.c_str());
    }
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    float fRate = 1.0f / AppSettings::sharedAppSettings()->getFloat("defaultSpriteFrameRate");
    pDirector->setAnimationInterval(fRate);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameView::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}