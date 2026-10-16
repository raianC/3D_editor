//Mesh.hpp

#pragma once

#include "Vertex.hpp"
#include "Face.hpp"
#include "HalfEdge.hpp"
#include <vector>
#include <algorithm>


class Mesh {
    private:
        std::vector<Vertex*> tabVertex;
        std::vector<Face*> tabFace;
        std::vector<HalfEdge*> tabHE;
        Eigen::Vector3d gravcenter;

    public:
        Mesh(std::vector<Eigen::Vector3d> V,std::vector<std::vector<int>> F);
        ~Mesh();
        void addVertex(Vertex* newvertex);
        void addFace(Face* newface);
        const std::vector<Vertex*>& getVertices() const;
        const std::vector<Face*>& getFaces() const;
        const std::vector<HalfEdge*>& getHalfEdges() const;
        Eigen::Vector3d getGravityCenter() const;

};
