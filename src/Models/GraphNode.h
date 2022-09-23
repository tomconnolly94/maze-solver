#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>
#include <tuple>

#include <GraphDirection.h>
#include <GraphPosition.h>

namespace Models {

    //typedef pair<GraphNode*, int> GraphNodeConnection;

    class GraphNode {
    private:
        // members
        vector<pair<GraphNode*, int>> _connections;
        GraphPosition _position;
        GraphDirection _directionOfParent;
    public:
        GraphNode(GraphPosition position, GraphDirection directionOfParent);

        // functions
        vector<pair<GraphNode*, int>> GetConnections();
        void AddConnection(GraphNode* graphNode, int connectionLength);
        GraphPosition GetPosition();
        GraphDirection GetDirectionOfParent();
    };
}

#endif