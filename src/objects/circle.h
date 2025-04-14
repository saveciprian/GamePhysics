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
    virtual void AddImpulse(glm::vec2 impulsePos);
    
    float deltaTime;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    std::vector<Bounds> bounds;
    std::vector<glm::vec2> forceFields;
    std::vector<ForceField> forces;
    float circleRadius;
    float mass;
    float mapRange(float x, float in_min, float in_max, float out_min, float out_max);
    glm::vec2 normalized(glm::vec2 toNormalize);
    float magnitude(glm::vec2 vect);

private:

protected:

};