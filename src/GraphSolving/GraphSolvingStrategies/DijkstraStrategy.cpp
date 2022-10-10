#include <algorithm>

#include "DijkstraStrategy.h"
#include "GraphDirection.h"
#include "GraphPosition.h"

using namespace Models;

namespace GraphSolvingStrategies {

    /*
        Constructor for DijkstraStrategy.
    */
    DijkstraStrategy::DijkstraStrategy() : IGraphSolvingStrategy(){}

    /*
        GetShortestPath takes a GraphNode* and returns a GraphNodePint.
    */
    vector<GraphPosition> DijkstraStrategy::GetShortestPath(GraphNode* startNode, GraphNode* endNode)
    {
        PopulatePathDataList(startNode);

        GraphNodePathData currentNodePathData = GetNodePathData(currentNodePathData.parentGraphNode);
        vector<GraphPosition> positionList{};

        while(currentNodePathData.parentGraphNode != nullptr)
        {
            positionList.push_back(currentNodePathData.graphNode->GetPosition());
            currentNodePathData = GetNodePathData(currentNodePathData.parentGraphNode);
        }

        positionList.push_back(startNode->GetPosition());

        return positionList;
    }

    GraphNodePathData DijkstraStrategy::GetNodePathData(GraphNode* graphNode)
    {
        for(auto pathData : _graphNodePathDataList)
        {
            if(pathData.graphNode == graphNode)
                return pathData;
        }
        return GraphNodePathData();
    }

    /*
        GetShortestPath takes a GraphNode* and returns a GraphNodePint.
    */
    void DijkstraStrategy::PopulatePathDataList(GraphNode* startNode)
    {
        // visit the first GraphNode*
        GraphNodePathData startNodePathData = GraphNodePathData(startNode, 0, nullptr);
        _graphNodePathDataList.push_back(startNodePathData);
        VisitNode(startNodePathData);

        while(true)
        {
            GraphNodePathData nextNodePathData = GetNextNodeToVisit();
            if(nextNodePathData.distanceFromParent == 0) return;
            VisitNode(nextNodePathData);
        }
    }
    /*
        GetNextNodeToVisit takes a GraphNode* and returns a pair<GraphNode*, int> representing the 
            next GraphNode* to be visited and the distance from its parent.
    */
    GraphNodePathData DijkstraStrategy::GetNextNodeToVisit()
    {
        GraphNodePathData nextNodeData;

        for (GraphNodePathData graphNodePathData : _graphNodePathDataList)
        {
            // if graphNode is not in _visitedNodes
            if(find(_visitedNodes.begin(), _visitedNodes.end(), graphNodePathData.graphNode) != _visitedNodes.end()) continue;

            //if nextNodeData is empty, or pathData has a shorter distance, assign pathData details to the nextNodeData
            if(nextNodeData.distanceFromParent == 0 || graphNodePathData.distanceFromParent < nextNodeData.distanceFromParent)
                nextNodeData = graphNodePathData;
        }
        return nextNodeData;
    }

    /*
        VisitNode takes a GraphNodePathData and analyses the connections of
        the contained GraphNode adding them to the path data store.
        @param GraphNodePathData
    */
    void DijkstraStrategy::VisitNode(GraphNodePathData nextNodePathData)
    {
        vector<pair<GraphNode*, int>> connectedGraphNodes = nextNodePathData.graphNode->GetConnections();

        for(auto graphNodeAndDistancePair : connectedGraphNodes)
        {
            int distanceFromStartNode = nextNodePathData.distanceFromParent;
            _graphNodePathDataList.push_back(GraphNodePathData(graphNodeAndDistancePair.first, nextNodePathData.distanceFromParent + graphNodeAndDistancePair.second, nextNodePathData.graphNode));
        }
        _visitedNodes.push_back(nextNodePathData.graphNode);
    }
}