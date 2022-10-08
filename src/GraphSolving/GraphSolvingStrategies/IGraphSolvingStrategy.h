#ifndef IMAZESOLVINGSTRATEGY_H
#define IMAZESOLVINGSTRATEGY_H

#include "GraphNode.h"

using namespace Models;

namespace GraphSolvingStrategies {

    class IGraphSolvingStrategy
    {
    public:
        virtual GraphNode* GetShortestPath(GraphNode* startNode) = 0;
    };
}
#endif