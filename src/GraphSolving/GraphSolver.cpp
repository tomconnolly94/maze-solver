
#include "GraphSolver.h"
#include "DijkstraStrategy.h"

namespace GraphSolving
{
    /*
        Constructor for DijkstraStrategy.
    */
    GraphSolver::GraphSolver(GraphNode* startNode)
    {
        _graphSolvingStrategy = new DijkstraStrategy();
        _startNode = startNode;

    }
    /*
        Constructor for DijkstraStrategy.
    */
    GraphSolver::~GraphSolver()
    {
        delete _graphSolvingStrategy;
        delete _startNode;

    }

    vector<GraphPosition> GraphSolver::SolveGraph()
    {
        return _graphSolvingStrategy->GetShortestPath(_startNode, nullptr);
    }

}