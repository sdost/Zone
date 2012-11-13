#include <typeinfo>
#include "GameElement.h"

using namespace std;

Action* GameElement::AddAction(Action* a)
{
    ActionList::iterator result = find_if(_actions.begin(), _actions.end(), ActionNameMatches(a->ActionName()));
    
    if(result == _actions.end())
    {
        _actions.push_back(a);
        result = find_if(_actions.begin(), _actions.end(), ActionNameMatches(a->ActionName()));
    }
    
    return (*result);
}

void GameElement::ActivateAction(string name)
{
    ActionList::iterator result = find_if(_actions.begin(), _actions.end(), ActionNameMatches(name));
    
    if(result != _actions.end())
    {
        Action* action = *result;
        _actionsQueued.push_back(action);
        action->StartAction();
    }
}

void GameElement::DeactivateAction(string name)
{
    ActionList::iterator result = find_if(_actions.begin(), _actions.end(), ActionNameMatches(name));
    
    if(result != _actions.end())
    {
        Action* action = *result;
        action->SetFinished(true);
    }
}

void GameElement::RemoveAction(string name)
{
    _actions.remove_if(ActionNameMatches(name));
}

void GameElement::Update(float t)
{
    ActionList::iterator pos;
    
    _actionsActive.splice(_actionsActive.end(), _actionsQueued);
    _actionsQueued.clear();
    
    for(pos = _actionsActive.begin(); pos != _actionsActive.end(); ++pos)
    {
        Action* action = *pos;
        if(action->Finished())
        {
            _actionsActive.remove_if(ActionNameMatches(action->ActionName()));
        }
        action->Update(t);
    }
}

bool GameElement::Active()
{
    return !(_actionsActive.empty());
}

void GameElement::Reset()
{
    _actions.clear();
    _actionsActive.clear();
    _actionsQueued.clear();
}