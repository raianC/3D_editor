//main
#include "Mesh.hpp"
#include "Scene.hpp"
#include "camera.hpp"
#include "Loader.hpp"
#include "PLYLoader.hpp"
#include "ObjLoader.hpp"



int main() {
    std::string filePath = "/mnt/c/Users/ghost/Documents/GitHub/3D_editor/3DModels/cube.obj";
    Scene scene;
    if (filePath.empty()) {
        std::cerr << "Erreur : Aucun fichier spécifié." << std::endl;
        return -1;
    }
    else if (filePath.substr(filePath.find_last_of(".") + 1) == "PLY") {
        std::cout << "Chargement d'un fichier PLY." << std::endl;
        PlyLoader Plyloader;
        Plyloader.LoadFile(filePath);
        Mesh mesh(Plyloader.GetPoints(), Plyloader.GetFaces());
        //scene.window();
    
        // VÉRIFICATION CRITIQUE : Si la fenêtre n'a pas pu s'ouvrir, on arrête tout pour éviter le crash
        //if (scene.getwindow() == nullptr) {
            //std::cerr << "Erreur critique : Impossible d'initialiser la fenêtre ou OpenGL." << std::endl;
            //return -1;
        //}
    
        //scene.draw(mesh.getHalfEdges(), scene.getwindow());
    }
    else if (filePath.substr(filePath.find_last_of(".") + 1) == "obj") {
        std::cout << "Chargement d'un fichier OBJ." << std::endl;
        ObjLoader Objloader;
        Objloader.LoadFile(filePath);
        Mesh mesh(Objloader.GetPoints(), Objloader.GetFaces());
        //scene.window();
    
        // VÉRIFICATION CRITIQUE : Si la fenêtre n'a pas pu s'ouvrir, on arrête tout pour éviter le crash
        //if (scene.getwindow() == nullptr) {
            //std::cerr << "Erreur critique : Impossible d'initialiser la fenêtre ou OpenGL." << std::endl;
            //return -1;
        //}
    
        //scene.draw(mesh.getHalfEdges(), scene.getwindow());
    }
    else {
        std::cerr << "Erreur : Format de fichier non supporté. Seuls les fichiers .ply et .obj sont acceptés." << std::endl;
        return -1;
    }
    
    

    return 0;
}