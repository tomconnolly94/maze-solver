#include <iostream>
#include <sstream>

#include <GraphBuilder.h>

namespace Building {

    /*
        Constructor for GraphBuilder.
        @param pixelMaze 2D vector representing the maze for analysis.
    */
    GraphBuilder::GraphBuilder(std::vector<std::vector<bool>> pixelMaze) : 
        graphNodes{},
        graphNodeEvaluationManager{pixelMaze}
    {
        _pixelMaze = pixelMaze;
        directionMap = {{Up, -1}, {Down, 1}, {Left, -1}, {Right, 1}};
    }
    
    /*
        EvaluatePositionConnections takes a pixelMaze position and evaluates its immediate surroundings for positions of that 
            should be included in the graph, not necessarily as GraphNodes.
        @test Building::TestGraphBuilder - TestEvaluatePositionConnections
        @param xPosition position on the x axis.
        @param yPosition position on the y axis.
        @return map of each position that can be considered part of the graph with the direction from the input position as the map key.
    */
    std::map<GraphDirection, GraphPosition> GraphBuilder::EvaluatePositionConnections(const int& xPosition, const int& yPosition)
    {
        std::map<GraphDirection, GraphPosition> directionMap{};
        GraphPosition graphRootPosition{xPosition, yPosition};

        for ( int graphDirectionIndex = Up; graphDirectionIndex != Right; ++graphDirectionIndex )
        {
            GraphDirection graphDirection = static_cast<GraphDirection>(graphDirectionIndex);
            GraphPosition graphPosition;
            try{
                graphPosition = GetNewPosition(graphRootPosition, graphDirection);
            }
            catch (const std::invalid_argument& exception){
                std::cerr << exception.what() << std::endl;
                continue;
            }

            if(_pixelMaze[graphPosition.second][graphPosition.first])
                directionMap[graphDirection] = graphPosition;        
        }
        return directionMap;
    }
    
    /*
        ScanPixelMazeForNewGraphNode scans the _pixelMaze from the top right hand corner, and returns when it finds a position it 
            considers to be a Node.
        @test Building::TestGraphBuilder - TestScanPixelMazeForNewGraphNode
        @param xPosition position on the x axis.
        @param yPosition position on the y axis.
        @return map of each position that can be considered part of the graph with the direction from the input position as the map key.
    */
    bool GraphBuilder::ScanPixelMazeForStartNode()
    {
        while(_pixelMazeXPosition < _pixelMaze[0].size())
        {
            bool pixel = _pixelMaze[0][_pixelMazeXPosition];
            if(!pixel)
            {
                ++_pixelMazeXPosition;
            }
            else
            {
                GraphPosition GraphPosition{0, _pixelMazeXPosition};
                CreateNewGraphNode(nullptr, GraphPosition, 0, Up);
                ++_pixelMazeXPosition;
                return true;
            }
        }
        return false;
    }

    /*
        BuildGraph uses the pixelMaze to populate a list of graphNodes with connections indicating the possible paths in the pixelMaze.
        @test Building::TestGraphBuilder - TestBuildGraph
        @return GraphNode* representing the start position.
    */
    GraphNode* GraphBuilder::BuildGraph()
    {
        GraphNode* startNode = nullptr;
        ScanPixelMazeForStartNode();

        while(graphNodeEvaluationManager.IsNotEmpty())
        {
            GraphNode* graphNodeForEvaluation = graphNodeEvaluationManager.GetNextGraphNodeForEvaluation();
            if(startNode == nullptr) startNode = graphNodeForEvaluation;
            EvaluateGraphNodeConnections(graphNodeForEvaluation);
        }
        return startNode;
    }

    /*
        GetNewPosition takes a position and a direction and returns the new position based on a one step
            move in that direction on the _pixelMaze. It throws an exception if the direction causes the
            new position to move off the _pixelMaze.
        @test Building::TestGraphBuilder - TestGetNewPosition
        @return GraphPosition representing the new position.
    */
    GraphPosition GraphBuilder::GetNewPosition(GraphPosition position, GraphDirection movementDirection)
    {
        GraphPosition graphPosition;
        switch (movementDirection)
        {
        case Up:
            graphPosition = GraphPosition{position.first, position.second - 1};
            if(graphPosition.second < 0)
                break;
            return graphPosition;
        case Down:
            graphPosition = GraphPosition{position.first, position.second + 1};
            if(graphPosition.second == _pixelMaze[0].size())
                break;
            return graphPosition;
        case Left:
            graphPosition = GraphPosition{position.first - 1, position.second};
            if(graphPosition.first < 0)
                break;
            return graphPosition;
        default:
        case Right:
            graphPosition = GraphPosition{position.first + 1, position.second};
            if(graphPosition.first == _pixelMaze.size())
                break;
            return graphPosition;
        }

        std::stringstream errorString;
        errorString << "GetNewPosition has invalid new position. x: " << graphPosition.first << ", y: " << graphPosition.second;
        throw std::invalid_argument(errorString.str());
    }


    void GraphBuilder::CreateNewGraphNode(GraphNode* parentNode, const GraphPosition graphNodePosition, const int& distanceFromParent, const GraphDirection& directionOfParent)
    {
        GraphNode* graphNode = new GraphNode(graphNodePosition, directionOfParent);

        graphNodes.push_back(graphNode);
        GraphConnection* graphConnection = new GraphConnection(distanceFromParent);

        graphNode->AddConnection(graphConnection);
        //graphNodesToBeEvaluated[graphNode] = 1;
        graphNodeEvaluationManager.AddGraphNode(graphNode);

        if(parentNode == nullptr) return;
        
        parentNode->AddConnection(graphConnection);
    }


    void GraphBuilder::EvaluateGraphNodeConnections(GraphNode* graphNode)
    {
        GraphPosition graphPosition = graphNode->GetPosition();
        std::map<GraphDirection, GraphPosition> nodeConnections = EvaluatePositionConnections(graphPosition.second, graphPosition.first);

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