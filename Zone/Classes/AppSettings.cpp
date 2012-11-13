//
//  AppSettings.cpp
//  Zone
//
//  Created by Samuel Dost on 8/11/12.
//
//

#include "AppSettings.h"
#include "cocoa/CCDictionary.h"
#include <cstdlib>

using namespace cocos2d;

static AppSettings* pSharedAppSettings = NULL;

AppSettings* AppSettings::sharedAppSettings(void)
{
    if (! pSharedAppSettings)
    {
        pSharedAppSettings = new AppSettings();
    }

    return pSharedAppSettings;
}

void AppSettings::initWithPlistFile(const char* plistName)
{
    const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(plistName);
    CCDictionary* fullDict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);
    m_pAppSettings = (CCDictionary*)fullDict->objectForKey("debug");
}

float AppSettings::getFloat(const std::string& key)
{
    float value = m_pAppSettings->valueForKey(key)->floatValue();
    return value;
}

int AppSettings::getInt(const std::string& key)
{
    int value = m_pAppSettings->valueForKey(key)->intValue();
    return value;
}

std::string AppSettings::getString(const std::string& key)
{
    std::string value = m_pAppSettings->valueForKey(key)->getCString();
    return value;
}