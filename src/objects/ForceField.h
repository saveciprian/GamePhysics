#pragma once
#include <glm/glm.hpp>

class ForceField {
public:
    ForceField(glm::vec2 pos, int radius);
    ~ForceField();

    virtual void Draw();
    virtual const char* GetName() { return "Force Field Object"; };

    glm::vec2 position;
    int radius;

private:
};