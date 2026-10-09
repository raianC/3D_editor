// ObjLoader.hpp

#pragma once

#include "Loader.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class ObjLoader : public Loader {
    public:
        void LoadFile(std::string filePath) override;
};