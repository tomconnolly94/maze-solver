#include <iostream>

#include <GraphNode.h>


GraphNode::GraphNode(std::pair<int, int> position){
    _position = position;
}

std::vector<GraphConnection*> GraphNode::GetConnections()
{
    return connections;
}

void GraphNode::AddConnection(GraphConnection* connection)
{
    connections.push_back(connection);
}

GraphPosition GraphNode::GetPosition(){
    return _position;
}