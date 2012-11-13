//
//  DisintegrateBrickAction.cpp
//  Zone
//
//  Created by Samuel Dost on 8/13/12.
//
//

#include "DisintegrateBrickAction.h"
#include "SimpleAudioEngine.h"
#include <math.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

string DisintegrateBrickAction::NAME = "DISINTEGRATE_BRICK_ACTION";

void DisintegrateBrickAction::StartAction()
{
    Action::StartAction();
    
    int v = ceil(rand() % 4 + 1);
    char buffer[50];
    sprintf(buffer, "brickbig%d.wav", v);
    std::string absPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(buffer);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(absPath.c_str());
}

void DisintegrateBrickAction::FinishAction()
{
    _finished = true;
}