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
        
};