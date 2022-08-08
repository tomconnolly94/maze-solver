#include <iostream>

#include <GraphBuilder.h>
#include <GraphNode.h>
#include <GraphDirection.h>


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


std::map<GraphDirection, GraphNode*> GraphBuilder::EvaluateNodeConnections(const int& rowIndex, const int& columnIndex)
{
    std::map<GraphDirection, GraphNode*> directionMap{};
    for ( int graphDirectionIndex = Up; graphDirectionIndex != Right; ++graphDirectionIndex )
    {
        GraphDirection graphDirection = static_cast<GraphDirection>(graphDirectionIndex);
        if(PixelMaze[rowIndex][columnIndex] == true)
            directionMap[graphDirection] = new GraphNode(std::pair<int, int>(columnIndex, rowIndex));
        else
            directionMap[graphDirection] = nullptr;
    }
    return directionMap;
}


GraphNode* GraphBuilder::BuildGraph()
{
    GraphNode* startNode = GetStartNode();
    GraphNode* lastParentNode;
    std::vector<GraphNode*> nodesUnderConsideration{};
    int columnIndex = 0;
    int rowIndex = 0;

    bool travelling = true;
    GraphDirection currentDirection = Down;

    std::map<GraphDirection, GraphNode*> nodeConnections = EvaluateNodeConnections(startNode->Position.first, startNode->Position.second);

    for (const std::pair<GraphDirection, GraphNode*>& directionNodePair : nodeConnections)
    {
        
    }





    while(travelling)
    {
        std::pair<int,int> oldPosition = std::pair<int, int>{columnIndex, rowIndex};
        std::pair<int,int> newPosition = GetNewPosition(std::pair<int, int>{columnIndex, rowIndex}, currentDirection);

        if(PixelMaze[std::get<0>(newPosition)][std::get<1>(newPosition)] == true)
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

std::pair<int, int> GraphBuilder::GetNewPosition(std::pair<int, int> position, GraphDirection movementDirection)
{
    switch (movementDirection)
    {
    case Up:
        return std::pair<int,int>{position.first - 1, position.second};
        break;
    case Down:
        return std::pair<int,int>{position.first + 1, position.second};
        break;
    case Left:
        return std::pair<int,int>{position.first, position.second - 1};
        break;
    default:
    case Right:
        return std::pair<int,int>{position.first, position.second + 1};
    }
}