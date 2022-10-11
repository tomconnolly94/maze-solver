#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "IGraphSolvingStrategy.h"
#include "GraphEntryPoints.h"

using namespace GraphSolvingStrategies;

namespace GraphSolving {

    class GraphSolver {
    private:
        IGraphSolvingStrategy* _graphSolvingStrategy;
        GraphEntryPoints _graphEntryPoints;
    public:
        GraphSolver(GraphEntryPoints graphEntryPoints);
        ~GraphSolver();
        vector<GraphPosition> SolveGraph();
    };
}

#endif