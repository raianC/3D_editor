//Vertex.cpp
#include "Vertex.hpp"



double Vertex::getPosition(){
    return x,y,z;
}

HalfEdge* Vertex::getHalfEdge(){
    return halfedge;
}

void Vertex::setPosition(double newX,double newY,double newZ){
    x = newX; y = newY; z = newZ;
}

void Vertex::setHalfEdge(HalfEdge* he){
    halfedge = he;
}