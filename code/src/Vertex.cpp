//Vertex.cpp
#include "Vertex.hpp"
#include "HalfEdge.hpp"


std::array<float, 3> Vertex::getPosition(){
    return {x, y, z};
}

HalfEdge* Vertex::getHalfEdge(){
    return halfedge;
}

void Vertex::setPosition(float newX,float newY,float newZ){
    x = newX; y = newY; z = newZ;
}

void Vertex::setHalfEdge(HalfEdge* he){
    halfedge = he;
}