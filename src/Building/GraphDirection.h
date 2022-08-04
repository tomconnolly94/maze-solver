#ifndef GRAPHDIRECTION_H
#define GRAPHDIRECTION_H

enum GraphDirection{
    Up,
    Down,
    Left,
    Right
};

GraphDirection GetOppositeDirection( GraphDirection direction ) {
   switch (direction)
   {
    case Up:
        return Down;
    case Down:
        return Up;
    case Left:
        return Right;
    case Right:
        return Left;

   }
}

#endif