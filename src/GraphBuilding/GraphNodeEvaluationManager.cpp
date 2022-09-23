
#include "GraphNodeEvaluationManager.h"

namespace GraphBuilding {
    
    GraphNodeEvaluationManager::GraphNodeEvaluationManager(vector<vector<bool>> pixelMaze) : 
        _pixelMazeXPosition(0), 
        _pixelMazeYPosition(0),
        graphNodesToBeEvaluated{},
        _pixelMaze{pixelMaze}{};


    GraphNode* GraphNodeEvaluationManager::GetNextGraphNodeForEvaluation()
    {
        if(graphNodesToBeEvaluated.empty()) return nullptr;
        
        GraphNode* graphNode = graphNodesToBeEvaluated.front();
        graphNodesToBeEvaluated.pop();
        return graphNode;        
    }

    void GraphNodeEvaluationManager::AddGraphNode(GraphNode* graphNode)
    {
        graphNodesToBeEvaluated.push(graphNode);
    }

    bool GraphNodeEvaluationManager::IsNotEmpty()
    {
        return !graphNodesToBeEvaluated.empty();
    }
}