#ifndef GRAPHDIRECTION_H
#define GRAPHDIRECTION_H

#include <vector>

using namespace std;

namespace Models {
    
    enum GraphDirection{
        Up,
        Down,
        Left,
        Right
    };

    GraphDirection GetOppositeDirection(GraphDirection direction);
    vector<GraphDirection> GetPerpendicularDirections(GraphDirection direction);
}
#endif