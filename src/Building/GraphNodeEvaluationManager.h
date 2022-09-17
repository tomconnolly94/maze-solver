#ifndef GRAPHNODEEVALUATIONMANAGER_H
#define GRAPHNODEEVALUATIONMANAGER_H

#include <queue>
#include <GraphNode.h>

namespace Building {

    class GraphNodeEvaluationManager {

    private:
        int _pixelMazeXPosition;
        int _pixelMazeYPosition;
        std::vector<std::vector<bool>> _pixelMaze;
        std::queue<GraphNode*> graphNodesToBeEvaluated;
    public:
        GraphNodeEvaluationManager(std::vector<std::vector<bool>> pixelMaze);
        GraphNode* GetNextGraphNodeForEvaluation();
        void AddGraphNode(GraphNode* graphNode);
        bool IsNotEmpty();
    };
};
#endif