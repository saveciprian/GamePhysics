#include "Assignment1.h"
#include "./objects/circle.h"
#include <iostream>

#include "imgui.h"
using namespace std;

Assignment1::Assignment1() : circlePosition(0, 4), circleRadius(1), velocity(0, 0), acceleration(0, -9.81) {
    Circle *circle = new Circle(glm::vec2(0, 2));
    addGameObject(*circle);

    Circle* circle2 = new Circle(glm::vec2(3, 5));
    addGameObject(*circle2);

    Circle* circle3 = new Circle(glm::vec2(-3, 6));
    addGameObject(*circle3);
}
Assignment1::~Assignment1() {}


void Assignment1::OnEnable() {
    
}

void Assignment1::OnDisable() {
}

void Assignment1::Update(float deltaTime) {
    //float gravity = -9.81f;
    //acceleration[1] = gravity;
        
    /*if (circlePosition[1] < 0 + circleRadius)
    {
        circlePosition[1] = 0 + circleRadius;
        velocity = velocity * glm::vec2(-1, -1);

    }*/

    //circle.PhysicsStep(deltaTime);

    for (int i = 0; i < objectPool.size(); i++)
    {
        objectPool[i].PhysicsStep(deltaTime);
    }

    

    //velocity = velocity + acceleration * deltaTime;
    //circlePosition = circlePosition + velocity * deltaTime; 
}

void Assignment1::addGameObject(Circle& obj) {
    objectPool.push_back(obj);
}

void Assignment1::Draw() {
    Draw::SetColor(0xffaaffaa); // Wtf is this A-BGR ?
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
    
    for (int i = 0; i < objectPool.size(); i++) {
        //Draw circle
        Draw::SetColor(0xffffffff);
        Draw::Circle(objectPool[i].position, objectPool[i].circleRadius);


        //Draw debug lines from origin point
        Draw::SetColor(0xff0000ff);
        Draw::Line(glm::vec2(0, 0), objectPool[i].position);
    }

    
}

void Assignment1::DrawGUI() {
    ImGui::Begin("Inspector");

    for (int i = 0; i < objectPool.size(); i++) {
        ImGui::PushID(i);
        ImGui::DragFloat2("Circle Position", &objectPool[i].position[0], 0.1f);
        ImGui::DragFloat("Circle Radius", &objectPool[i].circleRadius, 0.1f);
        ImGui::DragFloat2("Velocity", &objectPool[i].velocity[0], 0.1f);
        ImGui::DragFloat2("Acceleration", &objectPool[i].acceleration[0], 0.1f);
        ImGui::PopID();
    }

    //ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    //ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    //ImGui::DragFloat2("Velocity", &velocity[0], 0.1f);
    //ImGui::DragFloat2("Acceleration", &acceleration[0], 0.1f);
    ImGui::End();
}
