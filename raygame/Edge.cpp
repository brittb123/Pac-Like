#include "Edge.h"
#include <raylib.h>
#include "Node.h"


Edge::Edge(Node* FirstNode, Node* SecondNode)
{
	NodeConnected = FirstNode;
	NodeConnected2 = SecondNode;
}

void Edge::update(float deltatime)
{
	Actor::update(deltatime);
	//up[dates the position to match the position of the first connected node
	setWorldPostion(NodeConnected->getWorldPosition());
}
