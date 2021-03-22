#pragma once
#include "Decision.h"
class ABDecision :
	public Decision
{
public:
	ABDecision(Decision* leftChild = nullptr, Decision* rightChild = nullptr);

	virtual void makeDecision(Agent* agent, float deltatime) override;

	virtual bool checkDecision(Agent* agent, float deltatime) { return false; }

private:
	Decision* m_leftchild;
	Decision* m_rightchild;
};

