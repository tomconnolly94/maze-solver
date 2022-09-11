#include <iostream>

#include <GraphNode.h>


GraphNode::GraphNode(std::pair<int, int> position, GraphDirection directionOfParent){
    _position = position;
    _directionOfParent = directionOfParent;
}

std::vector<GraphConnection*> GraphNode::GetConnections()
{
    return _connections;
}

void GraphNode::AddConnection(GraphConnection* connection)
{
    _connections.push_back(connection);
}

GraphPosition GraphNode::GetPosition(){
    return _position;
}

GraphDirection GraphNode::GetDirectionOfParent(){
    return _directionOfParent;
}