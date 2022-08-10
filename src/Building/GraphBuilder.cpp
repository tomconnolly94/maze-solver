#include <iostream>

#include <GraphBuilder.h>


struct PositionUnderEvaluation
{
    GraphDirection entryDirection;
    GraphPosition graphPosition;

};

GraphBuilder::GraphBuilder(std::vector<std::vector<bool>> pixelMaze)
{
    PixelMaze = pixelMaze;
    directionMap = {{Up, -1}, {Down, 1}, {Left, -1}, {Right, 1}};
}


GraphNode* GraphBuilder::GetStartNode()
{
    int rowIndex = 0;
    int columnIndex = 0;

    // find the first node
    for(int columnIndex = 0; columnIndex < PixelMaze[rowIndex].size(); ++columnIndex)
    {
        if(PixelMaze[rowIndex][columnIndex] == true)
            return new GraphNode(std::pair<int, int>(columnIndex, rowIndex));
    }
}


std::map<GraphDirection, GraphPosition> GraphBuilder::EvaluatePositionConnections(const int& rowIndex, const int& columnIndex, GraphDirection entryDirection)
{
    std::map<GraphDirection, GraphPosition> directionMap{};
    GraphPosition graphRootPosition{rowIndex, columnIndex};

    for ( int graphDirectionIndex = Up; graphDirectionIndex != Right; ++graphDirectionIndex )
    {
        if(graphDirectionIndex == entryDirection) continue; // skip the entry direction
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


GraphNode* GraphBuilder::BuildGraph()
{
    GraphNode* startNode = GetStartNode();
    GraphNode* lastParentNode;
    std::vector<PositionUnderEvaluation> nodesUnderConsideration{};
    int columnIndex = 0;
    int rowIndex = 0;

    bool travelling = true;
    GraphDirection currentDirection = Down;


    GraphPosition positionUnderEvaluation = GraphPosition(startNode->Position.first, startNode->Position.second);

    std::map<GraphDirection, GraphPosition> nodeConnections = EvaluatePositionConnections(positionUnderEvaluation.first, positionUnderEvaluation.second, currentDirection);

    // if currentDirection is not found in nodeConnections or there are multiple node 
    // connections then the current position is a node
    if(nodeConnections.find(currentDirection) == nodeConnections.end() || nodeConnections.size() > 1)
    {
        GraphNode* graphNode = new GraphNode(GraphPosition(positionUnderEvaluation.first, positionUnderEvaluation.second));
        graphNode->SetNode(GetOppositeDirection(currentDirection), lastParentNode);
        lastParentNode->SetNode(currentDirection, graphNode);
    }


    for (const std::pair<GraphDirection, GraphPosition>& directionNodePair : nodeConnections)
    {
        PositionUnderEvaluation positionUnderEvaluation;
        positionUnderEvaluation.entryDirection = directionNodePair.first;
        positionUnderEvaluation.graphPosition = directionNodePair.second;
        
        nodesUnderConsideration.push_back(positionUnderEvaluation);

        
    }





    while(travelling)
    {
        GraphPosition oldPosition = std::pair<int, int>{columnIndex, rowIndex};
        GraphPosition newPosition = GetNewPosition(GraphPosition{columnIndex, rowIndex}, currentDirection);

        if(PixelMaze[newPosition.first][newPosition.second] == true)
        {
            continue;
        }
        else
        {
            // lastPosition is a node
            GraphNode* newNode = new GraphNode(newPosition);
            newNode->SetNode(GetOppositeDirection(currentDirection), lastParentNode);
            lastParentNode->SetNode(currentDirection, newNode);
            lastParentNode = newNode;

        }
    }
    return startNode;


    //nodesUnderConsideration.push_back(new GraphNode(startNode, nullptr, nullptr, nullptr, std::tuple<int, int>(0, columnIndex)));
}

GraphPosition GraphBuilder::GetNewPosition(GraphPosition position, GraphDirection movementDirection)
{
    switch (movementDirection)
    {
    case Up:
        return GraphPosition{position.first - 1, position.second};
        break;
    case Down:
        return GraphPosition{position.first + 1, position.second};
        break;
    case Left:
        return GraphPosition{position.first, position.second - 1};
        break;
    default:
    case Right:
        return GraphPosition{position.first, position.second + 1};
    }
}