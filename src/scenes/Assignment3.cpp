#include "Assignment3.h"

#include "imgui.h"
#include "../core/Colors.h"

void Assignment3::OnEnable() {

    //cameraCenter = glm::vec2(0, -3);
    orthographicSize = 25;

    Circle* circle = new Circle(glm::vec2(0, 2), 2);
    addGameObject(*circle);

     // added bounds here
    Bounds* upperBounds = new Bounds(glm::vec2(0, 10), glm::vec2(0, -1), 10);
    Bounds* lowerBounds = new Bounds(glm::vec2(0, -10), glm::vec2(0, 1), 10);
    Bounds* rightSide = new Bounds(glm::vec2(10, 0), glm::vec2(-1, 0), 10);
    Bounds* leftSide = new Bounds(glm::vec2(-10, 0), glm::vec2(1, 0), 10);

    // added bounds to array
    boundsPool.push_back(*upperBounds);
    boundsPool.push_back(*lowerBounds);
    boundsPool.push_back(*rightSide);
    boundsPool.push_back(*leftSide);

    for (int i = 0; i < boundsPool.size(); i++) {
        registerBounds(boundsPool[i]);
    }

    Collider* collider1 = new Collider(glm::vec2(-10, -10), glm::vec2(10, -5));

    Collider* collider2 = new Collider(glm::vec2(-2, 3), glm::vec2(-4, -7));

    colliders.push_back(*collider1);
    colliders.push_back(*collider2);
    registerCollider(objectPool[0], *collider1);
    registerCollider(objectPool[0], *collider2);
    /*circle.colliders.push_back(*collider1);*/
    
}

void Assignment3::OnDisable() {}

void Assignment3::Update(float deltaTime) {
    for (int i = 0; i < objectPool.size(); i++) {
        objectPool[i].PhysicsStep(deltaTime);
    }
}

void Assignment3::Draw() {
    for (int i = 0; i < objectPool.size(); i++) {
        // Draw circle
        Draw::SetColor(0xffffffff);
        Draw::Circle(objectPool[i].position, objectPool[i].circleRadius);

        Draw::SetColor(0xff00ff00);
        Draw::Line(objectPool[i].position,
                   objectPool[i].position + objectPool[i].velocity / 4.0f);
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

    for (int i = 0; i < colliders.size(); i++) {
        Draw::SetColor(Colors::orange);
        colliders[i].Draw();
    } 
    

}

void Assignment3::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}

void Assignment3::addGameObject(Circle& obj) {
    objectPool.push_back(obj);
}

void Assignment3::registerBounds(Bounds& bound) {
    for (int i = 0; i < objectPool.size(); i++) {
        objectPool[i].bounds.push_back(bound);
    }
}

void Assignment3::registerCollider(Circle& obj, Collider& collider) {
    obj.colliders.push_back(collider);
}