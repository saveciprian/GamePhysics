#pragma once

#include "core/Simple2DScene.h"
#include <iostream>
#include "./objects/circle.h"
#include <vector>

class Assignment1 : public Simple2DScene {
public:
    Assignment1();
    ~Assignment1();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    void addGameObject(Circle& obj);

    virtual const char* GetName() override { return "Assignment1"; };
    std::vector<Circle> objectPool;

private:
    glm::vec2 circlePosition;
    glm::vec2 velocity;
    float circleRadius;
    glm::vec2 acceleration;

};

