// Loader.cpp

#include "PLYLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Loader::Loader(){ //initialisation des tableaux
    tabPoint.clear();
    tabFace.clear();
}

void Loader::LoadFile(std::string filePath){
    std::ifstream File3D(filePath);
    tabPoint.clear();
    tabFace.clear();
    //test de la bonne overture du fichier
    if(!File3D.is_open()){
        std::cout<<"Error : failed to open file"<<std::endl;
        exit(1);
    }

    std::string line;
    std::string format;
    std::string vertexType;
    std::string faceType;
    int facePropertyCount = 0;
    int nbVertices = 0;
    int nbFaces = 0;

    while (std::getline(File3D, line)) {

        if (line.rfind("format ", 0) == 0) {
            format = line;
        }
        // Nombre de vertices
        else if (line.rfind("element vertex", 0) == 0) {
            sscanf(line.c_str(), "element vertex %d", &nbVertices);
        }
        else if (line.rfind("property float x", 0) == 0) {
            vertexType = "float";
        } else if (line.rfind("property double x", 0) == 0) {
            vertexType = "double";
        }
        // Nombre de faces
        else if (line.rfind("element face", 0) == 0) {
            sscanf(line.c_str(), "element face %d", &nbFaces);
        }
        else if ( line.rfind("property uchar red", 0) == 0) {
            facePropertyCount += 1;
        }
        else if ( line.rfind("property uchar green", 0) == 0) {
            facePropertyCount += 1;
        }
        else if ( line.rfind("property uchar blue", 0) == 0) {
            facePropertyCount += 1;
        }
        else if ( line.rfind("property uchar alpha", 0) == 0) {
            facePropertyCount += 1;
        }
        else if (line.rfind("property list ", 0) == 0) {
            char temp1[20];
            char temp2[20];
            sscanf(line.c_str(), "property list %19s %19s vertex_indices", temp1, temp2);

            faceType = std::string(temp2);
        }

        
        
        
        if (line == "end_header") {
            break;
        }
    }

    tabPoint.reserve(nbVertices);
    tabFace.reserve(nbFaces);

    if (format == "format ascii 1.0") {
    // lecture ASCII
    if (vertexType == "float") {
        for (int i = 0; i < nbVertices; ++i) {
            std::getline(File3D, line);
            float x, y, z;
            sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
            tabPoint.push_back({static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)});
        }
    } else if (vertexType == "double") {
        for (int i = 0; i < nbVertices; ++i) {
            std::getline(File3D, line);
        
            double x, y, z;
            sscanf(line.c_str(), "%lf %lf %lf", &x, &y, &z);
            tabPoint.push_back({static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)});
        }
    }
    for (int i = 0; i < nbFaces; ++i) {
        std::getline(File3D, line);

        std::stringstream ss(line);

        // Skip color properties
        int temp;
        for (int j = 0; j < facePropertyCount; ++j) {
            ss >> temp;
        }

        int n, v1, v2, v3;
        ss >> n >> v1 >> v2 >> v3;

        if (n != 3) {
            std::cout << "Error: non-triangular face found" << std::endl;
            return;
        }

        tabFace.push_back({
            static_cast<double>(v1),
            static_cast<double>(v2),
            static_cast<double>(v3)
        });
    }
    }

    else if (format == "format binary_little_endian 1.0") {
        // lecture binaire little endian
        if (vertexType == "float") {
            for (int i = 0; i < nbVertices; ++i) {
                float x, y, z;
                File3D.read(reinterpret_cast<char*>(&x), sizeof(float));
                File3D.read(reinterpret_cast<char*>(&y), sizeof(float));
                File3D.read(reinterpret_cast<char*>(&z), sizeof(float));
                tabPoint.push_back({static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)});
            }
        } else if (vertexType == "double") {
            for (int i = 0; i < nbVertices; ++i) {
                double x, y, z;
                File3D.read(reinterpret_cast<char*>(&x), sizeof(double));
                File3D.read(reinterpret_cast<char*>(&y), sizeof(double));
                File3D.read(reinterpret_cast<char*>(&z), sizeof(double));
                tabPoint.push_back({static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)});
            }
        }
       
        for (int i = 0; i < nbFaces; ++i) {

            // Skip properties we don't need
            File3D.seekg(facePropertyCount, std::ios::cur);

            // Number of indices
            uint8_t n;
            File3D.read(reinterpret_cast<char*>(&n), sizeof(uint8_t));

            if (n != 3) {
                std::cout << "Error: non-triangular face found" << std::endl;
                return;
            }

            // Indices
            int v1, v2, v3;

            File3D.read(reinterpret_cast<char*>(&v1), sizeof(int));
            File3D.read(reinterpret_cast<char*>(&v2), sizeof(int));
            File3D.read(reinterpret_cast<char*>(&v3), sizeof(int));

            tabFace.push_back({
                static_cast<double>(v1),
                static_cast<double>(v2),
                static_cast<double>(v3)
            });
        }
    }

    else if (format == "format binary_big_endian 1.0") {
    std::cout << "Error: binary big-endian PLY is not supported." << std::endl;
    return;
    }

    else {  
        std::cout << "Unknown PLY format" << std::endl;
    }

}
