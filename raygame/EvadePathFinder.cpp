#include "EvadePathFinder.h"

MathLibrary::Vector2 EvadePathFinder::findDestination(Agent* agent)
{
	return getTarget()->getWorldPosition();
}
