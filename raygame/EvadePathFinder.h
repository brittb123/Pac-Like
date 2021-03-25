#pragma once
#include "PathfindBehavior.h"

class EvadePathFinder :
    public PathfindBehavior
{
public:
    EvadePathFinder(Maze* maze) : PathfindBehavior(maze) { }

protected:
    virtual MathLibrary::Vector2 findDestination(Agent* agent) override;

};

