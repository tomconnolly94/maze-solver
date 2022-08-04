#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

class GraphNode {
private:
    std::map<GraphDirection, GraphNode*> nodeMap;
    std::tuple <int, int> Position;
public:
    GraphNode(
        GraphNode* upNode, 
        GraphNode* downNode, 
        GraphNode* leftNode, 
        GraphNode* rightNode,
        std::tuple <int, int> position);
    GraphNode(
        std::tuple <int, int> position);
    void SetNode(GraphDirection direction, GraphNode* graphNode);
};

#endif