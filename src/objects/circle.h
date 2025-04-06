#pragma once
#include <glm/glm.hpp>

class Circle {
public:
    Circle(glm::vec2 pos);
    ~Circle();

    virtual void CalculateAcceleration();
    virtual void CalculateVelocity();
    virtual void PhysicsStep(float dt);
    virtual void Collide();
    virtual void Draw();
    virtual const char* GetName() { return "Circle Object"; };
    glm::vec2 position;
    float circleRadius;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float deltaTime;

private:

protected:

};