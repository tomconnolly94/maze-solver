#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <GraphDirection.h>

class GraphNode {
private:
    std::map<GraphDirection, GraphNode*> nodeMap;
public:
    std::pair <int, int> Position;

    GraphNode(
        GraphNode* upNode, 
        GraphNode* downNode, 
        GraphNode* leftNode, 
        GraphNode* rightNode,
        std::pair <int, int> position);
    GraphNode(
        std::pair <int, int> position);
    void SetNode(GraphDirection direction, GraphNode* graphNode);
};

#endif