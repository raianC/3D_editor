//Face.hpp

#pragma once

class HalfEdge;

class Face {
    private:
        HalfEdge* halfedge;
    public:
        HalfEdge* getHalfEdge();
        void setHalfEdge(HalfEdge* he);
};