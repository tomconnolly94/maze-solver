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
    std::map<GraphNode*, int> graphNodesToBeEvaluated;

    // functions
    GraphNode* FindExistingConnectingNodeInDirection(GraphPosition graphPosition, GraphDirection direction);
    GraphNode* GetGraphNodeByPosition(GraphPosition graphPosition);
    GraphPosition GetNewPosition(GraphPosition position, GraphDirection movementDirection);
    GraphNode* GetStartNode();
    std::map<GraphDirection, GraphPosition> EvaluatePositionConnections(const int& rowIndex, const int& columnIndex);
    bool NodeConnectionsIndicateNode(std::map<GraphDirection, GraphPosition> nodeConnections);
    
    
    void CreateNewGraphNode(GraphNode* parentNode, const GraphPosition& graphNodePosition, const int& distanceFromParent, const GraphDirection& directionOfParent);
    void EvaluateGraphNodeConnections(GraphNode* graphNode);
    void TraverseForNewGraphNode(GraphNode& rootGraphNode, const GraphDirection& graphDirection);

public:
    GraphBuilder(std::vector<std::vector<bool>> pixelMaze);
    GraphNode* BuildGraph();
};

#endif