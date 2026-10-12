//Face.cpp
#include "Face.hpp"
#include "HalfEdge.hpp"


HalfEdge* Face::getHalfEdge() {
    return halfedge;
}

void Face::setHalfEdge(HalfEdge* he){
    halfedge = he;
}