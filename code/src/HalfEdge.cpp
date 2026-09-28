//HalfEdge.cpp

#include "HalfEdge.hpp"


Vertex* HalfEdge::Target(){
    return target;
}

HalfEdge* HalfEdge::Next(){
    return next;
}

HalfEdge* HalfEdge::Twin(){
    return twin;
}

Face* HalfEdge::getFace(){
    return face;
}

void HalfEdge::setTarget(Vertex* vtx){
    target = vtx;
}

void HalfEdge::setNext(HalfEdge* he){
    next = he;
}

void HalfEdge::setTwin(HalfEdge* he){
    twin = he;
}

void HalfEdge::setFace(Face* newface){
    face = newface;
}