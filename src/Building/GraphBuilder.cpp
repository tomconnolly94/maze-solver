#include <iostream>

#include <GraphBuilder.h>
#include <GraphNode.h>
#include <GraphDirection.h>


GraphBuilder::GraphBuilder(std::vector<std::vector<bool>> pixelMaze)
{
    PixelMaze = pixelMaze;
    directionMap = {{Up, -1}, {Down, 1}, {Left, -1}, {Right, 1}};
}

GraphNode* GraphBuilder::BuildGraph()
{
    GraphNode* startNode;
    GraphNode* lastParentNode;
    std::vector<GraphNode*> nodesUnderConsideration{};
    int columnIndex = 0;
    int rowIndex = 0;

    // find the first node
    for(; columnIndex < PixelMaze[rowIndex].size(); ++columnIndex)
    {
        if(PixelMaze[rowIndex][columnIndex] == true)
            startNode = lastParentNode = new GraphNode(std::tuple<int, int>(columnIndex, rowIndex));
    }

    bool travelling = true;
    GraphDirection currentDirection = Down;

    while(travelling)
    {
        std::tuple<int,int> oldPosition = std::tuple<int, int>{columnIndex, rowIndex};
        std::tuple<int,int> newPosition = GetNewPosition(std::tuple<int, int>{columnIndex, rowIndex}, currentDirection);

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


    //nodesUnderConsideration.push_back(new GraphNode(startNode, nullptr, nullptr, nullptr, std::tuple<int, int>(0, columnIndex)));
}

std::tuple<int, int> GraphBuilder::GetNewPosition(std::tuple<int, int> position, GraphDirection movementDirection)
{
    switch (movementDirection)
    {
    case Up:
        return std::tuple<int,int>{std::get<0>(position) - 1, std::get<1>(position)};
        break;
    case Down:
        return std::tuple<int,int>{std::get<0>(position) + 1, std::get<1>(position)};
        break;
    case Left:
        return std::tuple<int,int>{std::get<0>(position), std::get<1>(position) - 1};
        break;
    case Right:
        return std::tuple<int,int>{std::get<0>(position), std::get<1>(position) + 1};
    }
}