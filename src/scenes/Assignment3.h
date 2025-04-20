#pragma once
#include <iostream>
#include <vector>

#include "core/Simple2DScene.h"

#include "./objects/circle.h"
#include "./objects/bounds.h"
#include "./objects/ForceField.h"
#include "./objects/collider.h"

class Assignment3 : public Simple2DScene {
public:
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    void addGameObject(Circle& obj);
    void registerBounds(Bounds& bound);
    void registerCollider(Circle& obj, Collider& collider);

    virtual const char* GetName() override { return "Assignment 3"; };

    std::vector<Circle> objectPool;
    std::vector<Bounds> boundsPool;
    std::vector<ForceField> forces;
    std::vector<Collider> colliders;
    glm::vec2 mouseDownPos;
};