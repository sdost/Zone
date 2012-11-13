#include "GameElement.h"
#include "Action.h"

using namespace std;

void Action::Init( string name, GameElement* gameElement )
{
    _actionName = name;
    _gameElement = gameElement;
			
    _finished = true;
}