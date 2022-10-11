
#include "GraphSolver.h"
#include "DijkstraStrategy.h"

namespace GraphSolving
{
    /*
        Constructor for DijkstraStrategy.
    */
    GraphSolver::GraphSolver(GraphEntryPoints graphEntryPoints)
    {
        _graphSolvingStrategy = new DijkstraStrategy();
        _graphEntryPoints = graphEntryPoints;

    }
    /*
        Destructor for DijkstraStrategy.
    */
    GraphSolver::~GraphSolver()
    {
        delete _graphSolvingStrategy;

    }

    vector<GraphPosition> GraphSolver::SolveGraph()
    {
        return _graphSolvingStrategy->GetShortestPath(_graphEntryPoints.startNode, _graphEntryPoints.endNode);
    }

}