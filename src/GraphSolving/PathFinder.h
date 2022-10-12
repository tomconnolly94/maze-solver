#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "IGraphSolvingStrategy.h"
#include "GraphEntryPoints.h"

using namespace GraphSolvingStrategies;

namespace GraphSolving {

    class PathFinder {
    private:
        // fields
        IGraphSolvingStrategy* _graphSolvingStrategy;
        GraphEntryPoints _graphEntryPoints;
        // functions
        vector<GraphPosition> InterpolateBetweenPathNodes(vector<GraphPosition> path);
    public:
        PathFinder(GraphEntryPoints graphEntryPoints);
        ~PathFinder();
        vector<GraphPosition> FindPath();
    };
}

#endif