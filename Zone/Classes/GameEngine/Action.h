#ifndef _ACTION_H_
#define _ACTION_H_

#include <string>
#include "cocos2d.h"

class GameElement;

class Action : public cocos2d::CCObject
{
    public:
        Action() {};
        virtual void Init(std::string name, GameElement* gameElement);
        std::string ActionName()
        {
            return _actionName;
        };
		virtual void StartAction()
        {
            _finished = false;
        };
        virtual void Update(float t) {};
        void SetFinished(bool finished)
        {
            _finished = finished;
        };
        bool Finished()
        {
            return _finished;
        };
        bool operator==(const Action& a)
        {
            return ((*this)._actionName.compare(a._actionName) == 0);
        };
    protected:
        std::string _actionName;
        GameElement* _gameElement;
		bool _finished;
};

#endif
