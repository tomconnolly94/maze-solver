#include <iostream>

#include <GraphNode.h>

namespace Models {

    GraphNode::GraphNode(pair<int, int> position, GraphDirection directionOfParent){
        _position = position;
        _directionOfParent = directionOfParent;
    }

    vector<pair<GraphNode*, int>> GraphNode::GetConnections()
    {
        return _connections;
    }

    void GraphNode::AddConnection(GraphNode* graphNode, int connectionLength)
    {
        pair<GraphNode*, int> graphNodeConnection{graphNode, connectionLength};
        _connections.push_back(graphNodeConnection);
    }

    GraphPosition GraphNode::GetPosition(){
        return _position;
    }

    GraphDirection GraphNode::GetDirectionOfParent(){
        return _directionOfParent;
    }
}
