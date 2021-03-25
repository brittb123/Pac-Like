#include "EvadeBehavior.h"
#include "Maze.h"
#include "raylib.h"

EvadeBehavior::EvadeBehavior()
{
	m_target = nullptr;
	m_fleeForce = 1;
}

void EvadeBehavior::update(Agent* agent, float deltaTime)
{
	//Does not update if not enabled or the target is null
	if (!getEnabled() || !m_target)
		return;

	// Gets the location and the destination of the target
	MathLibrary::Vector2 Location = agent->getWorldPosition();
	MathLibrary::Vector2 destination = m_target->getWorldPosition();

	// If at the Destination then returns and exits function
	if (Location == destination)
		return;

	//Finds the direction using the target's velocity and position with the agents position
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() + m_target->getVelocity()) - agent->getWorldPosition();

	//Calculates the force by multiplying the direction by the force scale and adding the velocity
	MathLibrary::Vector2 desiredVel = direction * m_fleeForce;
	MathLibrary::Vector2 Force = desiredVel + agent->getVelocity();

	//Applies the force to the agent that is passed in
	agent->applyForce(Force);
}

void EvadeBehavior::draw(Agent* agent)
{
	int x = (int)agent->getWorldPosition().x;
	int y = (int)agent->getWorldPosition().y;
	x += Maze::TILE_SIZE / 2;
	y += Maze::TILE_SIZE / 2;
	DrawCircle(x, y, Maze::TILE_SIZE / 2, GetColor(agent->getColor()));
}


