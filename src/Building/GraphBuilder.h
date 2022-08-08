#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <string>
#include <vector>
#include <map>

#include <GraphNode.h>
#include <GraphDirection.h>

class GraphBuilder {
private:
    std::vector<std::vector<bool>> PixelMaze;
    std::map<GraphDirection, signed> directionMap;
public:
    GraphBuilder(std::vector<std::vector<bool>> pixelMaze);
    GraphNode* BuildGraph();
private:
    std::pair<int, int> GetNewPosition(std::pair<int, int> position, GraphDirection movementDirection);
    GraphNode* GetStartNode();
    std::map<GraphDirection, GraphNode*> EvaluateNodeConnections(const int& rowIndex, const int& columnIndex);
};

#endif