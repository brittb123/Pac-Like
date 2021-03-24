#include "Node.h"
#include <raylib.h>
#include "Edge.h"

Node::Node(int x, int y, int nodeSize)
{
	graphPosition.x = x;
	graphPosition.y = y;
	size = nodeSize;
}

void Node::update(float deltatime)
{
	for (int i = 0; i < edge.size(); i++)
	{
		if (edge[i]->NodeConnected->graphPosition == graphPosition)
			edge[i]->update(deltatime);
	}
}

void Node::draw()
{
	DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, size, GetColor(color));

	for (int i = 0; i < edge.size(); i++)
	{
		if (edge[i]->NodeConnected->graphPosition == graphPosition)
			edge[i]->draw();
	}
}