#pragma once
#include "Agent.h"
#include "SeekPathBehavior.h"
#include "EvadePathFinder.h"

enum GhostState
{
	SEEK,
	EVADE
};

class Maze;

class Ghost : public Agent
{
public:
	/// <param name="x">The x-position</param>
	/// <param name="y">The y-position</param>
	/// <param name="speed">The maximum movement speed (magnitude)</param>
	/// <param name="color">The color in 0xRRGGBBAA</param>
	/// <param name="maze">The maze used for pathfinding</param>
	Ghost(float x, float y, float speed, int color, Maze* maze);
	~Ghost();

	// Checks if the target can be seen by the ghost
	bool checkTargetinSight();

	// Checks if the player is to close to the ghost
	bool TooClosetoPlayer(Agent* other);

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

	/// <returns>The current target</returns>
	Actor* getTarget();
	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget(Actor* target);

private:
	SeekPathBehavior* m_pathfindBehavior;
	EvadePathFinder* m_EvadeFindBehavior;
	GhostState m_currentState;
	Maze* m_maze;
	float m_CloseRadius;

	Actor* m_target = nullptr;
};

