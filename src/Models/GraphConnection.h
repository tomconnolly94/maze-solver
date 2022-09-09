#ifndef GRAPHCONNECTION_H
#define GRAPHCONNECTION_H


class GraphConnection {
private:
    // members
    int _connectionLength;
public:
    GraphConnection(int connectionLength);

    // functions
    int GetConnectionLength();
};

#endif