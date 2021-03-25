#include "Ghost.h"
#include "Maze.h"
#include "Wall.h"
#include "raylib.h"

Ghost::Ghost(float x, float y, float maxSpeed, int color, Maze* maze)
	: Agent(x, y, Maze::TILE_SIZE / 4.0f, maxSpeed, maxSpeed, color)
{
	m_maze = maze;
	m_pathfindBehavior = new SeekPathBehavior(maze);
	m_EvadeFindBehavior = new EvadePathFinder(maze);
	m_CloseRadius = 5;
	m_currentState = SEEK;
	m_pathfindBehavior->setColor(color);
	addBehavior(m_pathfindBehavior);
}

Ghost::~Ghost()
{
	delete m_pathfindBehavior;
}

bool Ghost::checkTargetinSight()
{
	//Check if target is null ans return false if it is
	if (getTarget() == nullptr)
		return false;

	//Find the direction from the ghost and the target
	MathLibrary::Vector2 direction = getTarget()->getWorldPosition() - getWorldPosition();

	//Find the dot product of the taget's forward and the direction vector
	MathLibrary::Vector2 dotProduct = getForward() - direction;

	//Find the angle using the dot product
	float angle = (float)MathLibrary::Vector2::findAngle(getTarget()->getForward(), direction);

	//Check if the angle surpasses the ghost's viewing sight
	if (angle > 0)
		//Return true if the target is seen
		return true;

	return false;
}


void Ghost::update(float deltaTime)
{
	Agent::update(deltaTime);

	// A switch statement that changes depending on the current state
	switch (m_currentState)
	{
		// If the target is in sight then the ghost uses the evade case
	case EVADE:
		m_EvadeFindBehavior->setTarget(m_target);
		m_EvadeFindBehavior->update(this, deltaTime);
		break;

		// If the target is not in sight the ghost seek's the target and uses this case
	case SEEK:
		m_pathfindBehavior->update(this, deltaTime);
		m_pathfindBehavior->setTarget(m_target);
		break;
	}

	// Checks if the target is in sight if so the current state is switched
	if (checkTargetinSight())
		m_currentState = EVADE;

	// If the target is not in sight the current state is set to Seek the target
	else
		m_currentState = SEEK;

}

void Ghost::draw()
{
	m_pathfindBehavior->draw(this);
	m_EvadeFindBehavior->draw(this);
	Agent::draw();
}

void Ghost::onCollision(Actor* other)
{
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		setWorldPostion(tilePosition);

		setVelocity({ 0, 0 });
	}
}

void Ghost::setTarget(Actor* target)
{
	m_target = target;
	m_pathfindBehavior->setTarget(target);
}

Actor* Ghost::getTarget()
{
	return m_target;
}
