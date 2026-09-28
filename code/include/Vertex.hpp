//vertex.hpp

#pragma once

#include "HalfEdge.hpp"

class Vertex {
    private:
        double x,y,z;
        HalfEdge* halfedge;
    public:
        double getPosition();
        HalfEdge* getHalfEdge();
        void setPosition(double newX,double newY,double newZ);
        void setHalfEdge(HalfEdge* he);
};