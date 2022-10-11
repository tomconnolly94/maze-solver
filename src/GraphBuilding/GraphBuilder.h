#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <string>
#include <vector>
#include <map>

#include <GraphNode.h>
#include <GraphPosition.h>
#include <GraphNodeEvaluationManager.h>
#include <GraphEntryPoints.h>

using namespace std;
using namespace Models;

namespace GraphBuilding {

    class GraphBuilder {

    private:
        #ifdef UNIT_TEST
            // code to expose this classes private members in a unit test environment
            #include "gtest/gtest_prod.h"
            //friend class TestGraphBuilder;
            FRIEND_TEST(TestGraphBuilder, TestGetNewPosition);
            FRIEND_TEST(TestGraphBuilder, TestEvaluatePositionConnections);
            FRIEND_TEST(TestGraphBuilder, TestCreateNewGraphNode);
            FRIEND_TEST(TestGraphBuilder, TestEvaluateGraphNodeConnections);
            FRIEND_TEST(TestGraphBuilder, TestTraverseForNewGraphNode);
            FRIEND_TEST(TestGraphBuilder, TestScanPixelMazeForNewGraphNode);
            FRIEND_TEST(TestGraphBuilder, TestBuildGraph);
        #endif
        vector<vector<bool>> _pixelMaze;
        map<GraphDirection, signed> directionMap;
        vector<GraphNode*> graphNodes;
        GraphNodeEvaluationManager graphNodeEvaluationManager;
        int _pixelMazeXPosition;

        // functions
        GraphPosition GetNewPosition(GraphPosition position, GraphDirection movementDirection);
        GraphNode* GetStartNode();
        map<GraphDirection, GraphPosition> EvaluatePositionConnections(const int& rowIndex, const int& columnIndex);
        bool NodeConnectionsIndicateNode(map<GraphDirection, GraphPosition> nodeConnections);
        void CreateNewGraphNode(GraphNode* parentNode, const GraphPosition graphNodePosition, const int distanceFromParent, const GraphDirection directionOfParent);
        void EvaluateGraphNodeConnections(GraphNode* graphNode);
        void TraverseForNewGraphNode(GraphNode& rootGraphNode, const GraphDirection& graphDirection);
        bool ScanPixelMazeForStartNode();

    public:
        GraphBuilder(vector<vector<bool>> pixelMaze);
        GraphEntryPoints BuildGraph();

    };
};

#endif