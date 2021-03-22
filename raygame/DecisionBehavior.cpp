#include "DecisionBehavior.h"
#include "Decision.h"

void DecisionBehavior::update(Agent* agent, float deltatime)
{
	if (agent)
		return m_root->makeDecision(agent, deltatime);
}
