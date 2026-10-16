//Vertex.cpp
#include "Vertex.hpp"
#include "HalfEdge.hpp"


Eigen::Vector3d Vertex::getPosition(){
    return position;
}

HalfEdge* Vertex::getHalfEdge(){
    return halfedge;
}

void Vertex::setPosition(Eigen::Vector3d newPosition){
    position = newPosition;
}

void Vertex::setHalfEdge(HalfEdge* he){
    halfedge = he;
}