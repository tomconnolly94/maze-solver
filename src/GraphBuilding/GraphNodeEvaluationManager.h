#ifndef GRAPHNODEEVALUATIONMANAGER_H
#define GRAPHNODEEVALUATIONMANAGER_H

#include <queue>
#include <GraphNode.h>

using namespace std;
using namespace Models;

namespace GraphBuilding {

    class GraphNodeEvaluationManager {

    private:
        int _pixelMazeXPosition;
        int _pixelMazeYPosition;
        vector<vector<bool>> _pixelMaze;
        queue<GraphNode*> graphNodesToBeEvaluated;
    public:
        GraphNodeEvaluationManager(vector<vector<bool>> pixelMaze);
        GraphNode* GetNextGraphNodeForEvaluation();
        void AddGraphNode(GraphNode* graphNode);
        bool IsNotEmpty();
    };
};
#endif