#ifndef IMAZESOLVINGSTRATEGY_H
#define IMAZESOLVINGSTRATEGY_H

#include "GraphNode.h"

using namespace Models;

namespace MazeSolvingStrategies {

    class IMazeSolvingStrategy
    {
    public:
        virtual GraphNode* GetShortestPath(GraphNode* startNode) = 0;
    };
}
#endif