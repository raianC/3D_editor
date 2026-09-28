// HalfEdge.hpp

#pragma once

#include "Face.hpp"
#include "Vertex.hpp"

class HalfEdge {
    private:
        Vertex* target;
        HalfEdge* next;
        HalfEdge* twin;
        Face* face;
    public:
        Vertex* Target();
        HalfEdge* Next();
        HalfEdge* Twin();
        Face* getFace();
        void setTarget(Vertex* vtx);
        void setNext(HalfEdge* he);
        void setTwin(HalfEdge* he);
        void setFace(Face* newface);
};