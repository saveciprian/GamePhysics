#pragma once
#include <glm/glm.hpp>
#include <vector>

class GameObject {
public:
    GameObject();
    GameObject(bool dynamic);
    ~GameObject();

    bool isDynamic;
    virtual const char* GetName();
    
    glm::vec2 position;
    
    float deltaTime;
    

private:
protected:
};