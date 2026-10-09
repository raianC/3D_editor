// ObjLoader.cpp

#include "ObjLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>




void ObjLoader::LoadFile(std::string filePath) {
    std::ifstream File3D(filePath);
    tabPoint.clear();
    tabFace.clear();

    if (!File3D.is_open()) {
        std::cout << "Error: failed to open file " << filePath << std::endl;
        exit(1);
    }

    std::string line;

    while(std::getline(File3D, line)) {
        
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        std::istringstream iss(line);
        std::string prefix;

        if (!(iss >> prefix)) continue; // Skip empty lines
        iss >> prefix;
        
        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            tabPoint.push_back({x, y, z});
        } else if (prefix == "f") {
            int v1, v2, v3;
            std::string vertex1, vertex2, vertex3;
            iss >> vertex1 >> vertex2 >> vertex3;
            // Extract vertex indices (ignoring texture and normal indices)
            v1 = std::stoi(vertex1);
            v2 = std::stoi(vertex2);
            v3 = std::stoi(vertex3);
            
            tabFace.push_back({static_cast<int>(v1 - 1), static_cast<int>(v2 - 1), static_cast<int>(v3 - 1)});
        }
    }
}
