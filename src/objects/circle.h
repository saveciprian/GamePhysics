#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "bounds.h"
#include "ForceField.h"
#include "collider.h"
#include "GameObject.h"

class Circle : public GameObject {
public:
    Circle(glm::vec2 pos);
    Circle(glm::vec2 pos, float mass);
    ~Circle();

    virtual void CalculateAcceleration(glm::vec2 cummulative);
    virtual void CalculateVelocity();
    virtual void PhysicsStep(float dt);
    virtual void Collide();
    virtual void Draw();
    const char* GetName() override { return "Circle"; };
    int getMangitude(glm::vec2 vec);
    virtual void AddImpulse(glm::vec2 impulsePos);
    void Imagine(glm::vec2 mousePos, int steps);
    void checkBounds(glm::vec2& vel, glm::vec2& pos);
    void checkCollisions(glm::vec2& vel, glm::vec2& pos);
    
    float deltaTime;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    std::vector<Bounds> bounds;
    std::vector<glm::vec2> forceFields;
    std::vector<ForceField> forces;
    std::vector<Collider> colliders;
    float circleRadius;
    float mass;
    float mapRange(float x, float in_min, float in_max, float out_min, float out_max);
    glm::vec2 normalized(glm::vec2 toNormalize);
    float magnitude(glm::vec2 vect);

private:

protected:

};