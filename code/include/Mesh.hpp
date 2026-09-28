//Mesh.hpp

#pragma once

#include "HalfEdge.hpp"
#include <vector>


class Mesh {
    private:
        std::vector<Vertex*> tabVertex;
        std::vector<Face*> tabFace;
        std::vector<HalfEdge*> tabHE;

    public:
        Mesh(std::vector<std::vector<double>> V,std::vector<std::vector<double>> F);
        ~Mesh();
        void addVertex(Vertex* newvertex);
        void addFace(Face* newface);

};
