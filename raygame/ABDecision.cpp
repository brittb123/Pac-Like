#include "ABDecision.h"

ABDecision::ABDecision(Decision* leftChild, Decision* rightChild)
{
	m_leftchild = leftChild;
	m_rightchild = rightChild;
}

void ABDecision::makeDecision(Agent* agent, float deltatime)
{
	if (checkDecision(agent, deltatime))
	{
		if (m_leftchild)
			m_leftchild->makeDecision(agent, deltatime);

		else
		{
			if (m_rightchild)
				m_rightchild->makeDecision(agent, deltatime);
		}
	}
}
