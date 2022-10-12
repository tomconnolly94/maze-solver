
#include <stdlib.h> 

#include "PathFinder.h"
#include "DijkstraStrategy.h"

namespace GraphSolving
{
    enum InterPolationAxis{ X, Y };

    /*
        Constructor for DijkstraStrategy.
    */
    PathFinder::PathFinder(GraphEntryPoints graphEntryPoints)
    {
        _graphSolvingStrategy = new DijkstraStrategy();
        _graphEntryPoints = graphEntryPoints;

    }
    /*
        Destructor for DijkstraStrategy.
    */
    PathFinder::~PathFinder()
    {
        delete _graphSolvingStrategy;
    }

    vector<GraphPosition> PathFinder::FindPath()
    {
        vector<GraphPosition> path = _graphSolvingStrategy->GetShortestPath(_graphEntryPoints.startNode, _graphEntryPoints.endNode);
        vector<GraphPosition> interpolatedPath = InterpolateBetweenPathNodes(path);
        interpolatedPath.push_back(path[path.size() - 1]);
        return interpolatedPath;
    }

    vector<GraphPosition> PathFinder::InterpolateBetweenPathNodes(vector<GraphPosition> oldpath)
    {
        InterPolationAxis interPolationAxis;
        vector<GraphPosition> newPath{};

        for(int pathIndex = 0; pathIndex < oldpath.size() - 1; ++pathIndex)
        {
            GraphPosition graphPosition1 = oldpath[pathIndex];
            GraphPosition graphPosition2 = oldpath[pathIndex + 1];
            //newPath.push_back(graphPosition1);

            int fixedValue;
            int interpolationValueFrom;
            int interpolationValueTo;
            int interpolationValueDifference;
            int interpolationDirectionMovement = 1;

            // find the shared axis
            if(graphPosition1.first == graphPosition2.first)
            {
                interPolationAxis = Y;
                fixedValue = graphPosition1.first;
                interpolationValueFrom = graphPosition1.second;
                interpolationValueTo = graphPosition2.second;
            }
            if(graphPosition1.second == graphPosition2.second)
            {
                interPolationAxis = X;
                fixedValue = graphPosition1.second;
                interpolationValueFrom = graphPosition1.first;
                interpolationValueTo = graphPosition2.first;
            }
            
            interpolationValueDifference = abs(interpolationValueFrom - interpolationValueTo);

            if(interpolationValueFrom > interpolationValueTo)
                interpolationDirectionMovement = -1;


            for(int interpolationPointIndex = 0; interpolationPointIndex < interpolationValueDifference; ++interpolationPointIndex)
            {
                GraphPosition interpolationPosition{};
                if(interPolationAxis == X)
                    interpolationPosition = GraphPosition(interpolationValueFrom + (interpolationPointIndex * interpolationDirectionMovement), fixedValue);
                else if(interPolationAxis == Y)
                    interpolationPosition = GraphPosition(fixedValue, interpolationValueFrom + (interpolationPointIndex * interpolationDirectionMovement));
                newPath.push_back(interpolationPosition);
            }
        }
        return newPath;
    }
}