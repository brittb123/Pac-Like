#pragma once
#include "Actor.h"

class Node;

class Edge : public Actor
{
public:
	Edge(Node* FirstNode, Node* SecondNode);

	Node* NodeConnected;

	Node* NodeConnected2;

	void draw() override;

	void update(float deltatime) override;

	Node* m_target;

	float cost;
};