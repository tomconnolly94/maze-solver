#ifndef GRAPHDIRECTION_H
#define GRAPHDIRECTION_H

enum GraphDirection{
    Up,
    Down,
    Left,
    Right
};

GraphDirection GetOppositeDirection(GraphDirection direction);

#endif