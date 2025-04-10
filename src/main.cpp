#include "core/Application.h"
#include "scenes/Assignment1.h"
#include "scenes/TestScene.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = {
        new Assignment1(),
        new TestScene(),
    };
    Application app(scenes);
    return app.Run();
}
