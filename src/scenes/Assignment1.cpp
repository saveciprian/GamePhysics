#include "Assignment1.h"
#include <iostream>
#include "imgui.h"
using namespace std;

Assignment1::Assignment1() : circlePosition(0, 4), circleRadius(1), velocity(0, 0), acceleration(0, -9.81) {
    Circle *circle = new Circle(glm::vec2(0, 2), 2);
    addGameObject(*circle);

    Circle* circle2 = new Circle(glm::vec2(3, 5), 3);
    addGameObject(*circle2);

    Circle* circle3 = new Circle(glm::vec2(-3, 6), 30);
    addGameObject(*circle3);

    //added bounds here
    Bounds* upperBounds = new Bounds(glm::vec2(0, 10), glm::vec2(0, -1), 10);
    Bounds* lowerBounds = new Bounds(glm::vec2(0, -10), glm::vec2(0, 1), 10);
    Bounds* rightSide = new Bounds(glm::vec2(10, 0), glm::vec2(-1, 0), 10);
    Bounds* leftSide = new Bounds(glm::vec2(-10, 0), glm::vec2(1, 0), 10);
    

    //added bounds to array
    boundsPool.push_back(*upperBounds);
    boundsPool.push_back(*lowerBounds);
    boundsPool.push_back(*rightSide);
    boundsPool.push_back(*leftSide);

    for ( int i = 0; i < boundsPool.size(); i++) {
        registerBounds(boundsPool[i]);
    }

    ForceField* force1 = new ForceField(glm::vec2(-1, 2), 3);
    ForceField* force2 = new ForceField(glm::vec2(3, -3), 5);
    ForceField* force3 = new ForceField(glm::vec2(-6, 4), 3);

    forces.push_back(*force1);
    forces.push_back(*force2);
    forces.push_back(*force3);

    for (int i = 0; i < objectPool.size(); i++) {
        registerObject(objectPool[i], *force1);
        registerObject(objectPool[i], *force2);
        registerObject(objectPool[i], *force3);
    }

    


}
Assignment1::~Assignment1() {}


void Assignment1::OnEnable() {
    
}

void Assignment1::OnDisable() {
}

void Assignment1::Update(float deltaTime) {
    glm::vec2 mouse = Input::GetMousePos();

    // Stages for mouse position
    // ImGui::IsMouseClicked(0)
    // ImGui::IsMouseDown(0)
    // ImGui::IsMouseReleased(0)

    if (ImGui::IsMouseClicked(0)) { 
        for (int i = 0; i < objectPool.size(); i++) {
            //objectPool[i].AddImpulse(objectPool[i].position - mouse);
        }
    }

    if (ImGui::IsMouseDown(0)) { 
        Draw::SetColor(0xffffffff);
        Draw::Circle(mouse, 0.5f, true);
        //std::cout << "Mouse is being held at: (" << mouse.x << ", " << mouse.y
        //          << ")" << std::endl;
    }

    if (ImGui::IsMouseReleased(0)) { 
        
    }

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
    for (int i = 0; i < forces.size(); i++) {
        forces[i].Draw();
    }

    //Draw::SetColor(0xffaaffaa); // Wtf is this A-BGR ?
    //Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
    
    for (int i = 0; i < objectPool.size(); i++) {
        //Draw circle
        Draw::SetColor(0xffffffff);
        Draw::Circle(objectPool[i].position, objectPool[i].circleRadius);


        //Draw debug lines from origin point
        //Draw::SetColor(0xff0000ff);
        //Draw::Line(glm::vec2(0, 0), objectPool[i].position);
        Draw::SetColor(0xff00ff00);
        Draw::Line(objectPool[i].position,
                   objectPool[i].position + objectPool[i].velocity / 4.0f);
    }

    for (int i = 0; i < boundsPool.size(); i++) {
        boundsPool[i].Draw();
    }


    //Draw::AABB lets you draw a rectangle between 2 points and also fill it
    //can also add a position handle so you can move stuff directly in imgui    
}

void Assignment1::DrawGUI() {

    ImGui::Begin("Inspector");
    glm::vec2 mouse = Input::GetMousePos();

    if (ImGui::IsMouseDown(0)) {
        Draw::SetColor(0x33ff0000);
        Draw::Circle(mouse, 1.0f, true);
        
    }

    for (int i = 0; i < objectPool.size(); i++) {
        ImGui::PushID(i);
        ImGui::DragFloat2("Circle Position", &objectPool[i].position[0], 0.1f);
        ImGui::DragFloat("Circle Radius", &objectPool[i].circleRadius, 0.1f);
        ImGui::DragFloat2("Velocity", &objectPool[i].velocity[0], 0.1f);
        ImGui::DragFloat2("Acceleration", &objectPool[i].acceleration[0], 0.1f);
        ImGui::DragFloat("Mass", &objectPool[i].mass, 0.1f);
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

    //ImVec2 mousePos = ImGui::GetMousePos();
    //ImGui::Text("Mouse Position: (%.1f, %.1f)", mousePos.x, mousePos.y);

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

void Assignment1::registerObject(Circle& obj, ForceField& force) {
    obj.forces.push_back(force);
}




