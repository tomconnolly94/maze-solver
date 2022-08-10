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
