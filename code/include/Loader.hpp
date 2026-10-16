// Loader.hpp

#pragma once
#include <string>
#include <vector>
#include <Eigen>

class Loader {
    protected:
        std::vector<Eigen::Vector3d> tabPoint;
        std::vector<std::vector<int>> tabFace;
    public:
        virtual void LoadFile(std::string filePath) = 0;
        const std::vector<Eigen::Vector3d>& GetPoints() const;
        const std::vector<std::vector<int>>& GetFaces() const;
};