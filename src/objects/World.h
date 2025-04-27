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
    //void registerCollider();
    //should also add a collider type tag on the objects? so I don't have multiple lists but also know what checks to make
    void deregisterObject(std::shared_ptr<GameObject> obj);
    void tick(float dt);
    std::vector<Circle> getObjects();

private:
    void testCircleCollision();
    void testHalfSpaceCollision(Circle& obj, Collider& collider);
    std::vector<Circle> objects;
    std::vector<Collider> colliders;

};