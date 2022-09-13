#include <iostream>
#include <sstream>

#include <GraphBuilder.h>

namespace Building {

    struct PositionUnderEvaluation
    {
        GraphDirection entryDirection;
        GraphPosition graphPosition;

    };

    GraphBuilder::GraphBuilder(std::vector<std::vector<bool>> pixelMaze) : graphNodes{}
    {
        PixelMaze = pixelMaze;
        directionMap = {{Up, -1}, {Down, 1}, {Left, -1}, {Right, 1}};
    }

    GraphBuilder::GraphBuilder()
    {
        directionMap = {{Up, -1}, {Down, 1}, {Left, -1}, {Right, 1}};
    }


    std::map<GraphDirection, GraphPosition> GraphBuilder::EvaluatePositionConnections(const int& rowIndex, const int& columnIndex)
    {
        std::map<GraphDirection, GraphPosition> directionMap{};
        GraphPosition graphRootPosition{rowIndex, columnIndex};

        for ( int graphDirectionIndex = Up; graphDirectionIndex != Right; ++graphDirectionIndex )
        {
            GraphDirection graphDirection = static_cast<GraphDirection>(graphDirectionIndex);
            int positionValue = PixelMaze[rowIndex][columnIndex];
            GraphPosition graphPosition = GetNewPosition(graphRootPosition, graphDirection);

            if(positionValue == 1)
            {
                directionMap[graphDirection] = graphPosition;
            }
        
        }
        return directionMap;
    }

    bool GraphBuilder::NodeConnectionsIndicateNode(std::map<GraphDirection, GraphPosition> nodeConnections)
    {
        if(nodeConnections.size() > 2) return true;
        if(nodeConnections.size() < 2) return false;

        // if up and down are both present or left and right are both present, position is not a node
        if((nodeConnections.find(Up) != nodeConnections.end() && nodeConnections.find(Down) != nodeConnections.end()) ||
            (nodeConnections.find(Left) != nodeConnections.end() && nodeConnections.find(Right) != nodeConnections.end()))
            return false;
        return true;
    }

    GraphNode* GraphBuilder::GetGraphNodeByPosition(GraphPosition graphPosition)
    {
        for(auto graphNode : graphNodes)
        {
            if(graphNode->GetPosition().first == graphPosition.first && 
                graphNode->GetPosition().second == graphPosition.second)
                return graphNode;
        }
        return nullptr;
    }


    GraphNode* GraphBuilder::FindExistingConnectingNodeInDirection(GraphPosition graphPosition, GraphDirection direction)
    {
        GraphPosition positionUnderEvaluation = graphPosition;
        GraphPosition previousPositionUnderEvaluation = graphPosition;

        while(true)
        {
            positionUnderEvaluation = GetNewPosition(positionUnderEvaluation, (GraphDirection) direction);

            // if the positionUnderEvaluation is not a path
            if(PixelMaze[positionUnderEvaluation.first][positionUnderEvaluation.second] == 0)
                return nullptr;
            GraphNode* graphNode = GetGraphNodeByPosition(positionUnderEvaluation);
            if(graphNode != nullptr)
                return graphNode;
        }
    }


    GraphNode* GraphBuilder::BuildGraph()
    {
        GraphNode* startNode;
        int columnIndex = 0;
        int rowIndex = 0;

        // loop through the matrix to find node positions
        for(int x = 0; x < PixelMaze.size(); ++x)
        {
            for(int y = 0; y < PixelMaze[x].size(); ++y)
            {
                GraphPosition positionUnderEvaluation{x,y};

                std::map<GraphDirection, GraphPosition> nodeConnections = EvaluatePositionConnections(positionUnderEvaluation.first, positionUnderEvaluation.second);
                
                // if currentDirection is not found in nodeConnections or there are multiple node 
                // connections then the current position is a node
                if(NodeConnectionsIndicateNode(nodeConnections))
                {
                    GraphNode* graphNode = new GraphNode(positionUnderEvaluation, Up);
                    if(startNode == nullptr) startNode = graphNode;
                    graphNodes.push_back(graphNode);
                    
                    for ( int direction = Up; direction != Right; ++direction )
                    {
                        GraphDirection graphDirection = (GraphDirection) direction;
                        GraphNode* existingConnectedGraphNode = FindExistingConnectingNodeInDirection(graphNode->GetPosition(), graphDirection);

                        if(existingConnectedGraphNode != nullptr)
                        {
                            // graphNode->AddConnection(graphDirection, existingConnectedGraphNode);
                            // existingConnectedGraphNode->SetNode(GetOppositeDirection(graphDirection), graphNode);
                        }
                    }
                }
            }
        }
        return startNode;
    }

    GraphPosition GraphBuilder::GetNewPosition(GraphPosition position, GraphDirection movementDirection)
    {
        GraphPosition graphPosition;
        switch (movementDirection)
        {
        case Up:
            graphPosition = GraphPosition{position.first - 1, position.second};
            if(graphPosition.first < 0)
                break;
            return graphPosition;
        case Down:
            graphPosition = GraphPosition{position.first + 1, position.second};
            if(graphPosition.first == PixelMaze[0].size())
                break;
            return graphPosition;
        case Left:
            graphPosition = GraphPosition{position.first, position.second - 1};
            if(graphPosition.second < 0)
                break;
            return graphPosition;
        default:
        case Right:
            graphPosition = GraphPosition{position.first, position.second + 1};
            if(graphPosition.second == PixelMaze.size())
                break;
            return graphPosition;
        }

        std::stringstream errorString;
        errorString << "GetNewPosition has invalid new position. x: " << graphPosition.first << ", y: " << graphPosition.second;
        throw std::invalid_argument(errorString.str());
    }


    void GraphBuilder::CreateNewGraphNode(GraphNode* parentNode, const GraphPosition& graphNodePosition, const int& distanceFromParent, const GraphDirection& directionOfParent)
    {
        GraphNode* graphNode = new GraphNode(graphNodePosition, directionOfParent);

        graphNodes.push_back(graphNode);
        GraphConnection* graphConnection = new GraphConnection(distanceFromParent);

        graphNode->AddConnection(graphConnection);
        if(parentNode != nullptr)
            parentNode->AddConnection(graphConnection);

        graphNodesToBeEvaluated[graphNode] = 1;

        graphNodesToBeEvaluated[parentNode]--;
        if(graphNodesToBeEvaluated[parentNode] == 0)
            graphNodesToBeEvaluated.erase(parentNode);
    }


    void GraphBuilder::EvaluateGraphNodeConnections(GraphNode* graphNode)
    {
        GraphPosition graphPosition = graphNode->GetPosition();
        std::map<GraphDirection, GraphPosition> nodeConnections = EvaluatePositionConnections(graphPosition.first, graphPosition.second);

        graphNodesToBeEvaluated[graphNode] = nodeConnections.size();

        auto nodeConnection = nodeConnections.begin();
        while (nodeConnection != nodeConnections.end()) 
        {
            GraphDirection graphDirection = nodeConnection->first;

            //skip the direction of the node parent
            if(graphDirection == graphNode->GetDirectionOfParent()) continue;
            TraverseForNewGraphNode(*graphNode, graphDirection);

            ++nodeConnection;
        }
    }

    void GraphBuilder::TraverseForNewGraphNode(GraphNode& rootGraphNode, const GraphDirection& graphDirection)
    {
        GraphPosition positionForEvaluation = rootGraphNode.GetPosition();
        int stepsTakenFromParent = 0;

        while(true)
        {
            positionForEvaluation = GetNewPosition(positionForEvaluation, graphDirection);
            ++stepsTakenFromParent;

            //evaluate surrounding locations
            std::map<GraphDirection, GraphPosition> nodeConnections = EvaluatePositionConnections(positionForEvaluation.first, positionForEvaluation.second);

            // this position is a node if the next position for evaluation is not a valid path
            if(nodeConnections.find(graphDirection) == nodeConnections.end())
            {
                CreateNewGraphNode(&rootGraphNode, positionForEvaluation, stepsTakenFromParent, GetOppositeDirection(graphDirection));
                return;
            }

            std::vector<GraphDirection> perpendicularDirections = GetPerpendicularDirections(graphDirection);

            // this position is a node if there are perpendicular connections
            for (const GraphDirection& perpendicularDirection : perpendicularDirections)
            {
                if(nodeConnections.find(perpendicularDirection) != nodeConnections.end())
                {
                    CreateNewGraphNode(&rootGraphNode, positionForEvaluation, stepsTakenFromParent, GetOppositeDirection(graphDirection));
                    return;
                }
            }
        }
    };
};