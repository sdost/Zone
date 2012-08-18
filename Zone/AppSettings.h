#ifndef _APP_SETTINGS_H_
#define _APP_SETTINGS_H_

#include "cocos2d.h"
#include "cocoa/CCObject.h"

class cocos2d::CCDictionary;

class AppSettings : public cocos2d::CCObject
{
public:
    static AppSettings* sharedAppSettings(void);
    void initWithPlistFile(const char* plistName);
    float getFloat(const std::string& key);
    int getInt(const std::string& key);
    std::string getString(const std::string& key);
private:
    AppSettings(void) : m_pAppSettings(NULL){}
protected:
    cocos2d::CCDictionary* m_pAppSettings;
};

#endif