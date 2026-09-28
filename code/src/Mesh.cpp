//Mesh.cpp
#include "Mesh.hpp"



Mesh::Mesh(std::vector<std::vector<double>> V,std::vector<std::vector<double>> F){
    tabVertex.resize(V.size());
    tabFace.resize(F.size());
    tabHE.resize(F.size());

    for (int i=0; i<V.size(); ++i){
        Vertex* temp = new Vertex;
        temp->setPosition(V[i][0],V[i][1],V[i][2]);
        temp->setHalfEdge(nullptr);
        tabVertex[i]=temp;
    }

    for (int i=0; i<F.size(); ++i){
        Face* temp = new Face;
        temp->setHalfEdge(nullptr);
        tabFace[i]=temp;
    }

    for (int i=0; i<F.size(); ++i){
        
        HalfEdge* pHE0,*pHE1,*pHE2;
        pHE0 = new HalfEdge; pHE1 = new HalfEdge; pHE2 = new HalfEdge;
        
        pHE0->setTarget(tabVertex[F[i][1]]);
        pHE1->setTarget(tabVertex[F[i][2]]);
        pHE2->setTarget(tabVertex[F[i][0]]);
        if (tabVertex[i]->getHalfEdge()==nullptr){
            tabVertex[i]->setHalfEdge(pHE0);
        }
        pHE0->setNext(pHE1); pHE1->setNext(pHE2); pHE2->setNext(pHE0);
        pHE0->setFace(tabFace[i]); pHE1->setFace(tabFace[i]); pHE2->setFace(tabFace[i]);
        if (tabFace[i]->getHalfEdge() == nullptr){
            tabFace[i]->setHalfEdge(pHE0);
        }
    }
}

Mesh::~Mesh(){

}

void Mesh::addVertex(Vertex* newvertex){

}

void Mesh::addFace(Face* newface){

}
