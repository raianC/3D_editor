// PlyLoader.hpp

#pragma once

#include "Loader.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <algorithm>

class PlyLoader : public Loader {
    private:
        bool Error;
        struct Property {
            std::string name;
            std::string type;        // scalar type, or the INDEX type for a list
            int size;
            bool isList = false;
            std::string countType;   // only used when isList
        };

        std::string format;
        
        std::vector<Property> vertexProps;
        std::vector<Property> faceProps;
        
        int vertexPropertyCount = 0;
        int facePropertyCount = 0;
        int nbVertices = 0;
        int nbFaces = 0;

    public:
        PlyLoader();
        void LoadFile(std::string filePath) override;
        int TypeSize(const std::string& type);

        void HeaderReader(std::ifstream& File3D);
        
        void AsciiLoader(std::ifstream& File3D);
        
        void BinaryLoader(std::ifstream& File3D);
        double ReadScalar(std::ifstream& f, const std::string& type);

};