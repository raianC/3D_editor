//vertex.hpp

#pragma once
#include <array>
class HalfEdge;

class Vertex {
    private:
        float x,y,z;
        HalfEdge* halfedge;
    public:
        std::array<float, 3> getPosition();
        HalfEdge* getHalfEdge();
        void setPosition(float newX,float newY,float newZ);
        void setHalfEdge(HalfEdge* he);
};