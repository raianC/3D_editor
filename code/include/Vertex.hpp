//vertex.hpp

#pragma once
#include <Eigen>

class HalfEdge;

class Vertex {
    private:
        Eigen::Vector3d position;
        HalfEdge* halfedge;
    public:
        Eigen::Vector3d getPosition();
        HalfEdge* getHalfEdge();
        void setPosition(Eigen::Vector3d newPosition);
        void setHalfEdge(HalfEdge* he);
};