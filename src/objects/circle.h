#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "bounds.h"
#include "ForceField.h"

class Circle {
public:
    Circle(glm::vec2 pos);
    Circle(glm::vec2 pos, float mass);
    ~Circle();

    virtual void CalculateAcceleration(glm::vec2 cummulative);
    virtual void CalculateVelocity();
    virtual void PhysicsStep(float dt);
    virtual void Collide();
    virtual void Draw();
    virtual const char* GetName() { return "Circle Object"; };
    int getMangitude(glm::vec2 vec);
    
    float deltaTime;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    std::vector<Bounds> bounds;
    std::vector<glm::vec2> forceFields;
    std::vector<ForceField> forces;
    float circleRadius;
    float mass;

private:

protected:

};