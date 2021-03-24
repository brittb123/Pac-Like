#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	 //Find a path from start to end (The current implementation is obviously insufficient)

	// A empty list just for returning if a node is null
	std::deque<Node*> empty;

	// A iterator to hold the current node
	Node* Current = start;

	// Checks if the nodes passed in isnt a null pointer
	if (!start || !end)
		return empty;

	// Creates two list to store the nodes checked and next to be checked
	std::deque<Node*> open;
	std::deque<Node*> closed;

	// Pushes the front starting node to the open list
	open.push_front(start);

	while (!open.empty())
	{
		// A Bubble sort by the f score to organize the list
		for (int i = 0; i < open.size(); i++)
		{
			for (int j = 0; j < open.size(); j++)
			{
				if (open[i]->fScore > open[j]->fScore)
				{
					Node* temp = open[i];
					open[i] = open[j];
					open[j] = temp;
				}
			}
		}

		// Current is set to be the first node of the opened list
		Node* Current = open[0];

		// Checks if the current node is the end node 
		if (Current == end)
		{
			// Marks the end Node was Reached and returns the list
			end->Reached = true;
			return open;
		}

		// Removes the first node in the open list and adds it to the closed list
		open.pop_front();
		closed.push_front(Current);

		// A For Loop to go through all the edges of the Iterator
		for (int i = 0; i < Current->connections.size(); i++)
		{


			// A Node pointer to hold the end of the edge
			Node* EndEdge = nullptr;

			if (Current = Current->connections[i].ConnecectedNode2)
				EndEdge = Current->connections[i].ConnecectedNode1;

			// Checks if the Node is in the closed list
			if (closed[i] == EndEdge)
			{
				// The G, F, and H score is calculated for use for the following
				float G = Current->gScore + Current->connections[i].cost;
				float H = EndEdge->hScore;
				float F = G + H;

				// If the node is in the opened list
				if (open[i] == EndEdge)
				{
					// The bool that marks if it has reached a node is set true
					EndEdge->Reached = true;

					// The G, F, and H score is set to the ones calculated earlier
					EndEdge->gScore = G;
					EndEdge->hScore = H;
					EndEdge->fScore = F;

					// The previous of the node is set to be the Iterator
					EndEdge->previous = Current;
				}

				// Else if the F score is less than the node's left score then this block is used
				else if (F < EndEdge->fScore)
				{
					// The Node's Reached Bool is set to be true as a flag
					EndEdge->Reached = true;

					// The F, G, and H score is set to the scores calculated earlier
					EndEdge->gScore = G;
					EndEdge->hScore = H;
					EndEdge->fScore = F;

					// The previous of the node is set to be the Iterator
					EndEdge->previous = Current;
				}
			}
		}
	}

	return closed;

	//std::deque<Node*> path;
	//path.push_back(start);
	//path.push_back(start);
	//path.push_back(end);
	//return path;
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
