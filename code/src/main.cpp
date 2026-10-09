// main.cpp

#include <iostream>
#include "Loader.hpp"
#include "PLYLoader.hpp"
#include "ObjLoader.hpp"

void PrintMesh(Loader& loader, const std::string& filename) {
    loader.LoadFile(filename);
    const auto& points = loader.GetPoints();
    const auto& faces = loader.GetFaces();

    for (const auto& point : points) {
        std::cout << "Point: ";
        for (const auto& coord : point) {
            std::cout << coord << " ";
        }
        std::cout << std::endl;
    }
    for (const auto& face : faces) {
        std::cout << "Face: ";
        for (const auto& index : face) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    PlyLoader plyLoader;

    PrintMesh(plyLoader, "3DModel/Cube.ply");
}