#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "IGraphSolvingStrategy.h"

using namespace GraphSolvingStrategies;

namespace GraphSolving {

    class GraphSolver {
    private:
        IGraphSolvingStrategy* _graphSolvingStrategy;
        GraphNode* _startNode;
    public:
        GraphSolver(GraphNode* startNode);
        ~GraphSolver();
        GraphNode* SolveGraph();
    };
}

#endif