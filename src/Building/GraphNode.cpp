#include <iostream>

#include <GraphNode.h>
#include <GraphDirection.h>


GraphNode::GraphNode(GraphNode* upNode, GraphNode* downNode, GraphNode* leftNode, GraphNode* rightNode, std::tuple<int, int> position){
    nodeMap = std::map<GraphDirection, GraphNode*>{
        {Up, upNode},
        {Down, downNode},
        {Left, leftNode},
        {Right, rightNode},
    };
    Position = position;
}

GraphNode::GraphNode(std::tuple<int, int> position){
    nodeMap = std::map<GraphDirection, GraphNode*>{
        {Up, nullptr},
        {Down, nullptr},
        {Left, nullptr},
        {Right, nullptr},
    };
    Position = position;
}

void GraphNode::SetNode(GraphDirection direction, GraphNode* graphNode)
{
    nodeMap[direction] = graphNode;
}