#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <GraphDirection.h>
#include <GraphPosition.h>

class GraphNode {
private:
    std::map<GraphDirection, GraphNode*> nodeMap;
public:
    GraphPosition Position;

    GraphNode(
        GraphNode* upNode, 
        GraphNode* downNode, 
        GraphNode* leftNode, 
        GraphNode* rightNode,
        GraphPosition position);
    GraphNode(
        GraphPosition position);
    void SetNode(GraphDirection direction, GraphNode* graphNode);
};

#endif