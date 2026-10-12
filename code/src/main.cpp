//main
#include "Mesh.hpp"
#include "Scene.hpp"
#include "camera.hpp"
#include "Loader.hpp"
#include "PLYLoader.hpp"



int main() {
    
    Scene scene;
    PlyLoader loader;
    loader.LoadFile("/mnt/c/Users/ghost/Documents/GitHub/3D_editor/3DModels/Cube.PLY");
    Mesh mesh(loader.GetPoints(), loader.GetFaces());
    std::cout << "test1" << std::endl;
    scene.window();
    std::cout << "test2" << std::endl;
    scene.draw(mesh.getHalfEdges(), scene.getwindow());

    return 0;
}