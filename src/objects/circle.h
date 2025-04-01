#pragma once
#include <glm/glm.hpp>

class Circle {
public:
    Circle();
    ~Circle();

    virtual void CalculateAcceleration();
    virtual void CalculateVelocity();
    virtual void PhysicsStep(float dt);
    virtual void Collide();
    virtual const char* GetName() { return "Circle Object"; };

private:
    glm::vec2 position;
    float circleRadius;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float deltaTime;
};