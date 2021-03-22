#pragma once
#include "Behavior.h"

class Decision;

class DecisionBehavior : public Behavior

{
public:

	DecisionBehavior(Decision* root) {};

	void update(Agent* agent, float deltatime) override;

private:
	Decision* m_root;
};

