// Loader.cpp

#include "Loader.hpp"


const std::vector<std::vector<float>>& Loader::GetPoints() const {
    return tabPoint;
}
const std::vector<std::vector<int>>& Loader::GetFaces() const {
    return tabFace;
}