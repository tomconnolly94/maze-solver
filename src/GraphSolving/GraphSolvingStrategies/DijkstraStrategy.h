#ifndef IDIJKSTRASTRATEGY_H
#define IDIJKSTRASTRATEGY_H

#include <map>

#include "IGraphSolvingStrategy.h"
#include "GraphNode.h"

using namespace std;

namespace GraphSolvingStrategies {

    struct GraphNodePathData
    {
        GraphNode* graphNode;
        int distanceFromParent;
        GraphNode* parentGraphNode;

        GraphNodePathData(GraphNode* graphNode, 
            int distanceFromParent,
            GraphNode* parentGraphNode)
        {
            this->graphNode = graphNode;
            this->distanceFromParent = distanceFromParent;
            this->parentGraphNode = parentGraphNode;
        }
        GraphNodePathData()
        {
            graphNode = nullptr;
            distanceFromParent = 0;
            parentGraphNode = nullptr;
        }
    };

    class DijkstraStrategy : public IGraphSolvingStrategy
    {
    private:
        #ifdef UNIT_TEST
            // code to expose this classes private members in a unit test environment
            #include "gtest/gtest_prod.h"
            //friend class TestGraphBuilder;
            FRIEND_TEST(TestDijkstraStrategy, TestGetNextNodeToVisit);
        #endif
        vector<GraphNodePathData> _graphNodePathDataList;
        vector<GraphNode*> _visitedNodes;
        GraphNodePathData GetNextNodeToVisit();
        void VisitNode(GraphNodePathData nextNodePathData);
    public:
        DijkstraStrategy();
        GraphNode* GetShortestPath(GraphNode* startNode);
    };
}

#endif