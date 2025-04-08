#include "Assignment1.h"
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

    Bounds* upperBounds = new Bounds(glm::vec2(0, 10), glm::vec2(0, -1), 10);

    Bounds* lowerBounds = new Bounds(glm::vec2(0, -10), glm::vec2(0, 1), 10);

    Bounds* rightSide = new Bounds(glm::vec2(10, 0), glm::vec2(-1, 0), 10);

    Bounds* leftSide = new Bounds(glm::vec2(-10, 0), glm::vec2(1, 0), 10);

    boundsPool.push_back(*upperBounds);
    boundsPool.push_back(*lowerBounds);
    boundsPool.push_back(*rightSide);
    boundsPool.push_back(*leftSide);

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

    for (int i = 0; i < boundsPool.size(); i++) {
        boundsPool[i].Draw();
    }

    //Draw::AABB lets you draw a rectangle between 2 points and also fill it
    //can also add a position handle so you can move stuff directly in imgui    
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

    if (ImGui::Button("Reset"))
    {
        for (int i = 0; i < objectPool.size(); i++) {
            objectPool[i].position = glm::vec2(0, 2);
            objectPool[i].velocity = glm::vec2(0);
            objectPool[i].acceleration = glm::vec2(0);
        }
    }

    //ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    //ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    //ImGui::DragFloat2("Velocity", &velocity[0], 0.1f);
    //ImGui::DragFloat2("Acceleration", &acceleration[0], 0.1f);
    ImGui::End();
}

void Assignment1::registerBounds(Bounds& bound) {
    for (int i = 0; i < objectPool.size(); i++)
    {
        objectPool[i].bounds.push_back(bound);
    }

}
