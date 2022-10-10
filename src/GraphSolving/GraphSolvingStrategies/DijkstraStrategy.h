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
            // code to expose this class's private members in a unit test environment
            #include "gtest/gtest_prod.h"
            //friend class TestGraphBuilder;
            FRIEND_TEST(TestDijkstraStrategy, TestGetNextNodeToVisitSimple);
            FRIEND_TEST(TestDijkstraStrategy, TestGetNextNodeToVisitComplex);
            FRIEND_TEST(TestDijkstraStrategy, TestVisitNode);
            FRIEND_TEST(TestDijkstraStrategy, TestPopulatePathDataList);
            FRIEND_TEST(TestDijkstraStrategy, TestGetShortestPath);
        #endif
        vector<GraphNodePathData> _graphNodePathDataList;
        vector<GraphNode*> _visitedNodes;
        GraphNodePathData GetNextNodeToVisit();
        void VisitNode(GraphNodePathData nextNodePathData);
        void PopulatePathDataList(GraphNode* startNode);
        GraphNodePathData GetNodePathData(GraphNode* graphNode);
    public:
        DijkstraStrategy();
        vector<GraphPosition> GetShortestPath(GraphNode* startNode, GraphNode* endNode);
    };
}

#endif