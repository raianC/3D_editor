// Loader.hpp

#pragma once

#include <vector>
#include <iostream>

class Loader {
    private:
        std::vector<std::vector<double>> tabPoint;
        std::vector<std::vector<double>> tabFace;
    public:
        Loader();
        void LoadFile(std::string filePath);
};