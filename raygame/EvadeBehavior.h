#pragma once
#include "Behavior.h"
class EvadeBehavior :
    public Behavior
{

	public:
		EvadeBehavior();

		Actor* getTarget() { return m_target; }
		void setTarget(Actor* target) { m_target = target; }

		void update(Agent* agent, float deltaTime) override;
		void draw(Agent* agent) override;
	private:
		//the agent the behaviour is seeking
		Actor* m_target;
		float m_fleeForce;
	

};

