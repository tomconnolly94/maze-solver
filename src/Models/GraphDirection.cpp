#include <vector>

#include <GraphDirection.h>

GraphDirection GetOppositeDirection(GraphDirection direction) {
   switch (direction)
   {
        case Up:
            return Down;
        case Down:
            return Up;
        case Left:
            return Right;
        case Right:
        default:
            return Left;
   }
}


std::vector<GraphDirection> GetPerpendicularDirections(GraphDirection direction)
{
    std::vector<GraphDirection> UpDownDirections{Up, Down};
    std::vector<GraphDirection> LeftRightDirections{Left, Right};

    switch (direction)
    {
        case Up:
            return LeftRightDirections;
        case Down:
            return LeftRightDirections;
        case Left:
            return UpDownDirections;
        case Right:
        default:
            return UpDownDirections;
    }
}