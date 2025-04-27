#include "Assignment5.h"

#include "../core/Colors.h"
#include "imgui.h"

World* world = new World();



void Assignment5::OnEnable() {
    // cameraCenter = glm::vec2(0, -3);
    orthographicSize = 25;

    Circle circle(glm::vec2(0, 2), 2);
    //auto circle2 = std::make_shared<Circle>(glm::vec2(1, 5), 1);
    addGameObject(circle);
    //addGameObject(*circle2);

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

    Collider collider1(glm::vec2(-10, -10), glm::vec2(10, -5));
    Collider collider2(glm::vec2(-2, 3), glm::vec2(-4, -7));

    colliders.push_back(collider1);
    colliders.push_back(collider2);
    registerCollider(objectPool[0], collider1);
    registerCollider(objectPool[0], collider2);
    /*circle.colliders.push_back(*collider1);*/

    
    world->registerObject(circle);
    //world->registerObject(circle2);
    world->registerCollider(collider1);
    world->registerCollider(collider2);
    
}

void Assignment5::OnDisable() {}

void Assignment5::Update(float deltaTime) {
    //for (int i = 0; i < objectPool.size(); i++) {
    //    objectPool[i].PhysicsStep(deltaTime);
    //}

    world->tick(deltaTime);
    worldObjects = world->getObjects();
}

void Assignment5::Draw() {
    

    for (int i = 0; i < worldObjects.size(); i++) {
        // Draw circle
        Draw::SetColor(0xffffffff);
        Draw::Circle(worldObjects[i].position, worldObjects[i].circleRadius);

        Draw::SetColor(0xff00ff00);
        Draw::Line(worldObjects[i].position,
                   worldObjects[i].position + worldObjects[i].velocity / 4.0f);
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

void Assignment5::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}

void Assignment5::addGameObject(Circle& obj) {
    objectPool.push_back(obj);
}

void Assignment5::registerBounds(Bounds& bound) {
    for (int i = 0; i < objectPool.size(); i++) {
        objectPool[i].bounds.push_back(bound);
    }
}

void Assignment5::registerCollider(Circle& obj, Collider& collider) {
    obj.colliders.push_back(collider);
}