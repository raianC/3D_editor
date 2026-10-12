#include "Mesh.hpp"
#include "Scene.hpp"
#include "camera.hpp"
#include "Loader.hpp"


int main() {
    
    Scene scene;
    scene.window();
    scene.draw(halfEdges, scene.getwindow());

    return 0;
}