#pragma once
#include "Actor.h"
#include <Vector>

class Edge;

class Node :
	public Actor
{
public:
	Node(int x, int y, int nodeSize);
	void update(float deltatime) override;
	std::vector<Edge*> edge;
	MathLibrary::Vector2 graphPosition;
	int color = 0xFFFFFFFF;
	int size = 1;
	bool visited;
	void draw() override;
};