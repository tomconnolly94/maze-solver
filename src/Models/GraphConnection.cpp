
#include <GraphConnection.h>

GraphConnection::GraphConnection(int connectionLength){
    _connectionLength = connectionLength;
}

int GraphConnection::GetConnectionLength(){
    return _connectionLength;
}