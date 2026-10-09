// PlyLoader.cpp

#include "PlyLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <algorithm>




void PlyLoader::LoadFile(std::string filePath) {
    // Open in binary mode to prevent newline translations in binary PLY formats
    std::ifstream File3D(filePath, std::ios::binary);
    tabPoint.clear();
    tabFace.clear();

    if (!File3D.is_open()) {
        std::cout << "Error: failed to open file " << filePath << std::endl;
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
        // Strip trailing CR (\r) for cross-platform WSL/Windows compatibility
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.rfind("format ", 0) == 0) {
            format = line;
        }
        else if (line.rfind("element vertex", 0) == 0) {
            sscanf(line.c_str(), "element vertex %d", &nbVertices);
        }
        else if (line.rfind("property float x", 0) == 0) {
            vertexType = "float";
        } 
        else if (line.rfind("property double x", 0) == 0) {
            vertexType = "double";
        }
        else if (line.rfind("element face", 0) == 0) {
            sscanf(line.c_str(), "element face %d", &nbFaces);
        }
        else if (line.rfind("property uchar red", 0) == 0 ||
                 line.rfind("property uchar green", 0) == 0 ||
                 line.rfind("property uchar blue", 0) == 0 ||
                 line.rfind("property uchar alpha", 0) == 0) {
            facePropertyCount += 1;
        }
        else if (line.rfind("property list ", 0) == 0) {
            char temp1[20], temp2[20];
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
        // ASCII Reading
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
                tabPoint.push_back({static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)});
            }
        }

        for (int i = 0; i < nbFaces; ++i) {
            std::getline(File3D, line);
            std::stringstream ss(line);

            int n, v1, v2, v3;
            ss >> n >> v1 >> v2 >> v3;

            if (n != 3) {
                std::cout << "Error: non-triangular face found at face " << i << std::endl;
                return;
            }

            // Standard faces store index data as integers (storing as double if required by tabFace)
            tabFace.push_back({
                static_cast<int>(v1),
                static_cast<int>(v2),
                static_cast<int>(v3)
            });
        }
    }
    else if (format == "format binary_little_endian 1.0") {
        // Binary Little Endian Reading
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
                tabPoint.push_back({static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)});
            }
        }

        for (int i = 0; i < nbFaces; ++i) {
            uint8_t n;
            File3D.read(reinterpret_cast<char*>(&n), sizeof(uint8_t));

            if (n != 3) {
                std::cout << "Error: non-triangular face found at face " << i << std::endl;
                return;
            }

            int v1 = 0, v2 = 0, v3 = 0;

            // Handle index data types correctly based on faceType header definition
            if (faceType == "int" || faceType == "uint") {
                int idx[3];
                File3D.read(reinterpret_cast<char*>(idx), 3 * sizeof(int));
                v1 = idx[0]; v2 = idx[1]; v3 = idx[2];
            } else if (faceType == "short" || faceType == "ushort") {
                uint16_t idx[3];
                File3D.read(reinterpret_cast<char*>(idx), 3 * sizeof(uint16_t));
                v1 = idx[0]; v2 = idx[1]; v3 = idx[2];
            } else { // Default fallback to 32-bit integer
                File3D.read(reinterpret_cast<char*>(&v1), sizeof(int));
                File3D.read(reinterpret_cast<char*>(&v2), sizeof(int));
                File3D.read(reinterpret_cast<char*>(&v3), sizeof(int));
            }

            // Skip extra face properties (e.g., colors stored after indices)
            if (facePropertyCount > 0) {
                File3D.seekg(facePropertyCount, std::ios::cur);
            }

            tabFace.push_back({
                static_cast<int>(v1),
                static_cast<int>(v2),
                static_cast<int>(v3)
            });
        }
    }
    else if (format == "format binary_big_endian 1.0") {
        std::cout << "Error: binary big-endian PLY is not supported." << std::endl;
        return;
    }
    else {  
        std::cout << "Unknown PLY format: " << format << std::endl;
    }
}