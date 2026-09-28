//Face.hpp

#pragma once

#include "HalfEdge.hpp"

class Face {
    private:
        HalfEdge* halfedge;
    public:
        HalfEdge* getHalfEdge();
        void setHalfEdge(HalfEdge* he);
};