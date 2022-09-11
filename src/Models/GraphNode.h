#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <GraphDirection.h>
#include <GraphPosition.h>
#include <GraphConnection.h>

class GraphNode {
private:
    // members
    std::vector<GraphConnection*> _connections;
    GraphPosition _position;
    GraphDirection _directionOfParent;
public:
    GraphNode(GraphPosition position, GraphDirection directionOfParent);

    // functions
    std::vector<GraphConnection*> GetConnections();
    void AddConnection(GraphConnection* connection);
    GraphPosition GetPosition();
    GraphDirection GetDirectionOfParent();
};

#endif