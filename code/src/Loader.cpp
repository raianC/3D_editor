// Loader.cpp

#include "Loader.hpp"


const std::vector<Eigen::Vector3d>& Loader::GetPoints() const {
    return tabPoint;
}
const std::vector<std::vector<int>>& Loader::GetFaces() const {
    return tabFace;
}