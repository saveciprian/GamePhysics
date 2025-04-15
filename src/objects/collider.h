#pragma once
#include <glm/glm.hpp>
#include <vector>

class Collider {
public:
    Collider(glm::vec2 posA, glm::vec2 posB);
    ~Collider();


    glm::vec2 pointA;
    glm::vec2 pointB;
    glm::vec2 normal;
    enum dir {
        cw,
        ccw
    };
    glm::vec2 getNormal(dir val);
    glm::vec2 normalized(glm::vec2 v);
    virtual void Draw();

    


private:

protected:

};