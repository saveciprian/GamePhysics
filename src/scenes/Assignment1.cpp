#include "Assignment1.h"
#include <iostream>

#include "imgui.h"
using namespace std;

Assignment1::Assignment1() : circlePosition(0, 4), circleRadius(1), velocity(0, 0), acceleration(0, -9.81) {}
Assignment1::~Assignment1() {}

void Assignment1::OnEnable() {}

void Assignment1::OnDisable() {}

void Assignment1::Update(float deltaTime) {
    //float gravity = -9.81f;
    //acceleration[1] = gravity;
        
    if (circlePosition[1] < 0 + circleRadius)
    {
        circlePosition[1] = 0 + circleRadius;
        velocity = velocity * glm::vec2(-1, -1);

    }

    velocity = velocity + acceleration * deltaTime;
    circlePosition = circlePosition + velocity * deltaTime; 
}

void Assignment1::Draw() {
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
}

void Assignment1::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    ImGui::DragFloat2("Velocity", &velocity[0], 0.1f);
    ImGui::DragFloat2("Acceleration", &acceleration[0], 0.1f);
    ImGui::End();
}
