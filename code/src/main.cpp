//main
#include "Mesh.hpp"
#include "Scene.hpp"
#include "camera.hpp"
#include "Loader.hpp"
#include "PLYLoader.hpp"
#include "ObjLoader.hpp"



int main() {
    
    Scene scene;
    PlyLoader loader;
    loader.LoadFile("/mnt/c/Users/raian/Documents/GitHub/3D_editor/3DModels/Socket cap screw.ply");
    Mesh mesh(loader.GetPoints(), loader.GetFaces());
    
    std::cout << "test1" << std::endl;
    scene.window();
    
    // VÉRIFICATION CRITIQUE : Si la fenêtre n'a pas pu s'ouvrir, on arrête tout pour éviter le crash
    if (scene.getwindow() == nullptr) {
        std::cerr << "Erreur critique : Impossible d'initialiser la fenêtre ou OpenGL." << std::endl;
        return -1;
    }
    
    std::cout << "test2" << std::endl;
    scene.draw(mesh.getHalfEdges(), scene.getwindow());
    return 0;
}