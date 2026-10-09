// Loader.hpp

#pragma once
#include <string>
#include <vector>

class Loader {
    protected:
        std::vector<std::vector<float>> tabPoint;
        std::vector<std::vector<int>> tabFace;
    public:
        virtual void LoadFile(std::string filePath) = 0;
        const std::vector<std::vector<float>>& GetPoints() const;
        const std::vector<std::vector<int>>& GetFaces() const;
};