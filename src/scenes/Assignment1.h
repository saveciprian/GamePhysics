#pragma once

#include "core/Simple2DScene.h"
#include <iostream>
#include "./objects/circle.h"

class Assignment1 : public Simple2DScene {
public:
    Assignment1();
    ~Assignment1();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment1"; };

private:
    glm::vec2 circlePosition;
    float circleRadius;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    std::vector<Circle> vectorArray(Circle);
};

