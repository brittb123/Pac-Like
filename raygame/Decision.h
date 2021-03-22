#pragma once

class Agent;

class Decision
{
public:
	virtual void makeDecision(Agent* agent, float deltatime) = 0;
};

