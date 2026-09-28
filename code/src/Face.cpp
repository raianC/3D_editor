//Face.cpp
#include "Face.hpp"


HalfEdge* Face::getHalfEdge() {
    return halfedge;
}

void Face::setHalfEdge(HalfEdge* he){
    halfedge = he;
}