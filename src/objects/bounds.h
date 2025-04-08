#pragma once
#include <glm/glm.hpp>


class Bounds {
public:
    Bounds(glm::vec2 pos, glm::vec2 normal, int size);
    ~Bounds();

    virtual void Draw();
    virtual const char* GetName() { return "Bounds Object"; };

    glm::vec2 position;
    glm::vec2 normal;
    int size;

private:
	
};