#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <string>
#include <vector>
#include <map>

#include <GraphNode.h>
#include <GraphPosition.h>

namespace Building {

    class GraphBuilder {

    private:
        #ifdef UNIT_TEST
            // code to expose this classes private members in a unit test environment
            #include "gtest/gtest_prod.h"
            friend class TestGraphBuilder;
            FRIEND_TEST(TestGraphBuilder, TestGetNewPosition);
            FRIEND_TEST(TestGraphBuilder, TestEvaluatePositionConnections);
            FRIEND_TEST(TestGraphBuilder, TestCreateNewGraphNode);
            FRIEND_TEST(TestGraphBuilder, TestEvaluateGraphNodeConnections);
        #endif
        std::vector<std::vector<bool>> PixelMaze;
        std::map<GraphDirection, signed> directionMap;
        std::map<GraphNode*, int> graphNodesToBeEvaluated;
        std::vector<GraphNode*> graphNodes;

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
        GraphBuilder();
        GraphNode* BuildGraph();

    };
};

#endif