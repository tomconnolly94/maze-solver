#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <string>
#include <vector>
#include <map>

#include <GraphNode.h>
#include <GraphPosition.h>

class GraphBuilder {
private:
    std::vector<std::vector<bool>> PixelMaze;
    std::map<GraphDirection, signed> directionMap;
public:
    GraphBuilder(std::vector<std::vector<bool>> pixelMaze);
    GraphNode* BuildGraph();
private:
    GraphPosition GetNewPosition(GraphPosition position, GraphDirection movementDirection);
    GraphNode* GetStartNode();
    std::map<GraphDirection, GraphPosition> EvaluatePositionConnections(const int& rowIndex, const int& columnIndex, GraphDirection entryDirection);
};

#endif