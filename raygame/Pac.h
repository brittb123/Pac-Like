#pragma once
#include "Agent.h"
#include "KeyboardBehavior.h"

class Pac : public Agent
{
public:
	/// <param name="x">The x-position</param>
	/// <param name="y">The y-position</param>
	/// <param name="speed">The maximum movement speed (magnitude)</param>
	Pac(float x, float y, float speed);
	~Pac();

	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

private:
	KeyboardBehavior* m_keyboardBehavior;
	
};

