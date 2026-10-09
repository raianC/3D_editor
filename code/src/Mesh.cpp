//Mesh.cpp

#include "Mesh.hpp"


Mesh::Mesh(std::vector<std::vector<double>> V,std::vector<std::vector<double>> F){
    tabVertex.resize(V.size());
    tabFace.resize(F.size());
    tabHE.resize(3*F.size());

    // Initialisation du tableau de Vertex
    for (int i=0; i<V.size(); ++i){
        Vertex* temp = new Vertex;
        temp->setPosition(V[i][0],V[i][1],V[i][2]);
        temp->setHalfEdge(nullptr);
        tabVertex[i]=temp;
    }

    // Initialisation du tableau de Face
    for (int i=0; i<F.size(); ++i){
        Face* temp = new Face;
        temp->setHalfEdge(nullptr);
        tabFace[i]=temp;
    }

    struct SortedEdge{
        int v1,v2;
        int maxv,minv;
        HalfEdge* he;

        int operator<(const SortedEdge& other) const {
            if (maxv == other.maxv){
                return minv < other.minv;
            }
            return maxv < other.maxv;
        }
    };

    std::vector<SortedEdge> edgeList;
    edgeList.reserve(3*F.size());

    // Initialisation du tableau de HalfEdge
    for (int i=0; i<F.size(); ++i){
        
        HalfEdge* pHE0,*pHE1,*pHE2;
        pHE0 = new HalfEdge; pHE1 = new HalfEdge; pHE2 = new HalfEdge;
        SortedEdge e0,e1,e2;

        e0.v1 = F[i][0]; e0.v2 = F[i][1]; e0.maxv = std::max(e0.v1,e0.v2); e0.minv = std::min(e0.v1,e0.v2); e0.he = pHE0;
        e1.v1 = F[i][1]; e1.v2 = F[i][2]; e1.maxv = std::max(e1.v1,e1.v2); e1.minv = std::min(e1.v1,e1.v2); e1.he = pHE1;
        e2.v1 = F[i][2]; e2.v2 = F[i][0]; e2.maxv = std::max(e2.v1,e2.v2); e2.minv = std::min(e2.v1,e2.v2); e2.he = pHE2;
        edgeList.push_back(e0); edgeList.push_back(e1); edgeList.push_back(e2);

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

        tabHE[3*i] = pHE0; tabHE[3*i+1] = pHE1; tabHE[3*i+2] = pHE2;
    }

    // Determination des twins
    std::sort(edgeList.begin(), edgeList.end());
    for (int i=0; i<edgeList.size(); ++i){
        for (int j=i+1; j<edgeList.size(); ++j){
            if (edgeList[i].v1 == edgeList[j].v2 && edgeList[i].v2 == edgeList[j].v1){
                edgeList[i].he->setTwin(edgeList[j].he);
                edgeList[j].he->setTwin(edgeList[i].he);
            }
        }
    }
}

Mesh::~Mesh(){
    for (int i = 0; i<tabVertex.size(); ++i){
        delete tabFace[i];
    }
    
    for (int i = 0; i<tabFace.size(); ++i){
        delete tabFace[i];
    }
    
    for (int i = 0; i<tabHE.size(); ++i){
        delete tabHE[i];
    }
}

void Mesh::addVertex(Vertex* newvertex){

}

void Mesh::addFace(Face* newface){

}

