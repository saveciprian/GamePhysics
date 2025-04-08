#pragma once
#include <glm/glm.hpp>
#include <vector>

class GameObject {
public:
    GameObject(glm::vec2 pos);
    ~GameObject();

    virtual void CalculateAcceleration();
    virtual void CalculateVelocity();
    virtual void PhysicsStep(float dt);
    virtual void Collide();
    virtual void Draw();
    virtual const char* GetName() { return "GameObject"; };
    int getMangitude(glm::vec2 vec);
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float circleRadius;
    float deltaTime;
    std::vector<glm::vec2> forceFields;

private:
protected:
};