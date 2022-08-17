#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <string>
#include <vector>
#include <map>

#include <GraphNode.h>
#include <GraphPosition.h>

class GraphBuilder {
private:
    //members
    std::vector<std::vector<bool>> PixelMaze;
    std::map<GraphDirection, signed> directionMap;
    std::vector<GraphNode*> graphNodes;

    // functions
    GraphNode* FindExistingConnectingNodeInDirection(GraphPosition graphPosition, GraphDirection direction);
    GraphNode* GetGraphNodeByPosition(GraphPosition graphPosition);
    GraphPosition GetNewPosition(GraphPosition position, GraphDirection movementDirection);
    GraphNode* GetStartNode();
    std::map<GraphDirection, GraphPosition> EvaluatePositionConnections(const int& rowIndex, const int& columnIndex);
    bool NodeConnectionsIndicateNode(std::map<GraphDirection, GraphPosition> nodeConnections);
public:
    GraphBuilder(std::vector<std::vector<bool>> pixelMaze);
    GraphNode* BuildGraph();
};

#endif