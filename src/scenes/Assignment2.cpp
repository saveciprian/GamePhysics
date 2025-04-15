#include "Assignment2.h"

#include "../core/Colors.h"
#include "imgui.h"

glm::vec2 initMousePos;
glm::vec2 mousePos;
int steps = 160;

void Assignment2::OnEnable() {
    // cameraCenter = glm::vec2(0, -3);
    orthographicSize = 25;

    Circle* circle = new Circle(glm::vec2(-7, 1), 2);
    addGameObject(*circle);
    

    // added bounds here
    Bounds* upperBounds = new Bounds(glm::vec2(0, 10), glm::vec2(0, -1), 10);
    Bounds* lowerBounds = new Bounds(glm::vec2(0, 0), glm::vec2(0, 1), 10);
    Bounds* rightSide = new Bounds(glm::vec2(10, 5), glm::vec2(-1, 0), 5);
    Bounds* leftSide = new Bounds(glm::vec2(-10, 5), glm::vec2(1, 0), 5);

    // added bounds to array
    boundsPool.push_back(*upperBounds);
    boundsPool.push_back(*lowerBounds);
    boundsPool.push_back(*rightSide);
    boundsPool.push_back(*leftSide);

    for (int i = 0; i < boundsPool.size(); i++) {
        registerBounds(boundsPool[i]);
    }

}

void Assignment2::OnDisable() {}

void Assignment2::Update(float deltaTime) {
    for (int i = 0; i < objectPool.size(); i++) {
        objectPool[i].PhysicsStep(deltaTime);
    }

}

void Assignment2::Draw() {
    if (Input::IsMouseClicked(0)){
        isSimulating = true;
        initMousePos = Input::GetMousePos();
    }

    if (Input::IsMouseDown(0)){
        mousePos = Input::GetMousePos();
        Draw::SetColor(Colors::orange);
        Draw::Arrow(objectPool[0].position,
                    objectPool[0].position + mousePos - initMousePos);
        objectPool[0].Imagine(mousePos - initMousePos, steps);
    }

    if (Input::IsMouseReleased(0))
    {
        objectPool[0].AddImpulse(mousePos - initMousePos);
    }

    for (int i = 0; i < objectPool.size(); i++) {
        // Draw circle
        Draw::SetColor(0xffffffff);
        Draw::Circle(objectPool[i].position, objectPool[i].circleRadius);

        Draw::SetColor(0xff00ff00);
        Draw::Arrow(objectPool[i].position,
                   objectPool[i].position + objectPool[i].velocity * 0.3f);
    }

    for (int i = 0; i < boundsPool.size(); i++) {
        boundsPool[i].Draw();
    }

    if (Input::IsMouseClicked(0)) {
        mouseDownPos = Input::GetMousePos();
    }
    if (Input::IsMouseDown(0)) {
        glm::vec2 impulse = Input::GetMousePos() - mouseDownPos;
        Draw::SetColor(Colors::orange);
    }

}

void Assignment2::DrawGUI() {
    ImGui::Begin("Inspector");

    ImGui::DragInt("Steps", &steps, 0.1f, 0);
    for (int i = 0; i < objectPool.size(); i++) {
        ImGui::PushID(i);
        ImGui::DragFloat2("Circle Position", &objectPool[i].position[0], 0.1f);
        ImGui::DragFloat("Circle Radius", &objectPool[i].circleRadius, 0.1f);
        ImGui::DragFloat2("Velocity", &objectPool[i].velocity[0], 0.1f);
        ImGui::DragFloat2("Acceleration", &objectPool[i].acceleration[0], 0.1f);
        ImGui::PopID();
    }

    if (ImGui::Button("Reset")) {
        objectPool[0].position = glm::vec2(-7, 1);
        objectPool[0].velocity = glm::vec2(0);
        objectPool[0].acceleration = glm::vec2(0);

    }

    ImGui::End();
}

void Assignment2::addGameObject(Circle& obj) {
    objectPool.push_back(obj);
}

void Assignment2::registerBounds(Bounds& bound) {
    for (int i = 0; i < objectPool.size(); i++) {
        objectPool[i].bounds.push_back(bound);
    }
}
