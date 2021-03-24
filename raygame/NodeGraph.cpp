#include "NodeGraph.h"
#include "Edge.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	// Find a path from start to end (The current implementation is obviously insufficient)

	Node* Current = start;

	std::deque<Node*> open;
	std::deque<Node*> close;

	
	open.push_front(start);

	while (!open.empty())
	{
		for (int i = 0; i < open.size(); i++)
		{
			for (int j = 0; j < open.size(); j++)
			{
				if (open[i] > open[j - 1])
				{
					Node* temp = open[i];
					open[i] = open[j - 1];
					open[j] = temp;
				}
			}
		}

		Node* Current = open[0];

		if (Current == end)
			return close;

		open.pop_front();

		close.push_front(Current);


	}


	/*std::deque<Node*> path;
	path.push_back(start);
	path.push_back(start);
	path.push_back(end);*/
	return close;
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}
