#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include "bounds.h"
#include "ForceField.h"
#include "collider.h"
#include "circle.h"

class World {
public:
    World();
    ~World();

    //add a 'dynamic' bool on all game objects to decide whether to check for collisions or not
    void registerObject(Circle& obj);
    void registerCollider(Collider& col);
    void registerBounds(Bounds& bound);
    //void registerCollider();
    //should also add a collider type tag on the objects? so I don't have multiple lists but also know what checks to make
    void deregisterObject(std::shared_ptr<GameObject> obj);
    void tick(float dt);
    std::vector<Circle> getObjects();
    bool isSimulating = false;
    void imagine(glm::vec2 mousePos, int steps);
    void addImpulse(glm::vec2 impulse);
    glm::vec2 gravity = glm::vec2(0, -9.81f);
    void setDamping(float value);

private:
    void testCircleCollision(Circle& obj1, Circle& obj2);
    void testHalfSpaceCollision(Circle& obj, Collider& collider);
    void testBoundsCollision(Circle& obj);
    void calculateAcceleration(Circle& obj, glm::vec2 cummulative);
    void physicsStep(Circle& obj, float dt);
    void calculateVelocity(Circle& obj, float dt);

    std::vector<Circle> objects;
    std::vector<Collider> colliders;
    std::vector<Bounds> bounds;

};