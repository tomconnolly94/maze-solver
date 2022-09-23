#include <vector>

#include <GraphDirection.h>

using namespace Models;

namespace Models {

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


    vector<GraphDirection> GetPerpendicularDirections(GraphDirection direction)
    {
        vector<GraphDirection> UpDownDirections{Up, Down};
        vector<GraphDirection> LeftRightDirections{Left, Right};

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
}