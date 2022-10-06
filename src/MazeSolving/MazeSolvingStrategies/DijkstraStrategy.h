#ifndef IDIJKSTRASTRATEGY_H
#define IDIJKSTRASTRATEGY_H

#include "IMazeSolvingStrategy.h"
#include "GraphNode.h"

namespace MazeSolvingStrategies {

    class DijkstraStrategy : public IMazeSolvingStrategy
    {
    public:
        DijkstraStrategy();
        GraphNode* GetShortestPath(GraphNode* startNode);
    };
}

#endif