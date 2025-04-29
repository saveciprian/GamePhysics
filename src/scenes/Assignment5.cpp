#include "Assignment5.h"

#include "../core/Colors.h"
#include "imgui.h"

World* world = new World();
glm::vec2 initMousePosition;
glm::vec2 mousePosition;
int trajectorySteps = 160;



void Assignment5::OnEnable() {
    // cameraCenter = glm::vec2(0, -3);
    orthographicSize = 25;

    Circle circle(glm::vec2(-15, 0), 2);
    Circle ball1(glm::vec2(11, 0), 2);
    Circle ball2(glm::vec2(13, -1.5), 2);
    Circle ball3(glm::vec2(13, 1.5), 2);
    Circle ball4(glm::vec2(15, -3), 2);
    Circle ball5(glm::vec2(15, 0), 2);
    Circle ball6(glm::vec2(15, 3), 2);
    Circle ball7(glm::vec2(17, -4.5), 2);
    Circle ball8(glm::vec2(17, -1.5), 2);
    Circle ball9(glm::vec2(17, 1.5), 2);
    Circle ball10(glm::vec2(17, 4.5), 2);
    //auto circle2 = std::make_shared<Circle>(glm::vec2(1, 5), 1);
    addGameObject(circle);
    addGameObject(ball1);
    addGameObject(ball2);
    addGameObject(ball3);
    addGameObject(ball4);
    addGameObject(ball5);
    addGameObject(ball6);
    addGameObject(ball7);
    addGameObject(ball8);
    addGameObject(ball9);
    addGameObject(ball10);

    // added bounds here
    Bounds* upperBounds = new Bounds(glm::vec2(0, 10), glm::vec2(0, -1), 20);
    Bounds* lowerBounds = new Bounds(glm::vec2(0, -10), glm::vec2(0, 1), 20);
    Bounds* rightSide = new Bounds(glm::vec2(20, 0), glm::vec2(-1, 0), 10);
    Bounds* leftSide = new Bounds(glm::vec2(-20, 0), glm::vec2(1, 0), 10);

    // added bounds to array
    boundsPool.push_back(*upperBounds);
    boundsPool.push_back(*lowerBounds);
    boundsPool.push_back(*rightSide);
    boundsPool.push_back(*leftSide);

    for (int i = 0; i < boundsPool.size(); i++) {
        registerBounds(boundsPool[i]);
    }

    //Collider collider1(glm::vec2(-10, -10), glm::vec2(10, -5));
    //Collider collider2(glm::vec2(-10, 3), glm::vec2(-4, -10));

    //colliders.push_back(collider1);
    //colliders.push_back(collider2);
    //registerCollider(objectPool[0], collider1);
    //registerCollider(objectPool[0], collider2);
    /*circle.colliders.push_back(*collider1);*/

    world->gravity = glm::vec2(0);
    world->registerObject(circle);
    world->registerObject(ball1);
    world->registerObject(ball2);
    world->registerObject(ball3);
    world->registerObject(ball4);
    world->registerObject(ball5);
    world->registerObject(ball6);
    world->registerObject(ball7);
    world->registerObject(ball8);
    world->registerObject(ball9);
    world->registerObject(ball10);
    //world->registerCollider(collider1);
    //world->registerCollider(collider2);
    
}

void Assignment5::OnDisable() {}

void Assignment5::Update(float deltaTime) {
    //for (int i = 0; i < objectPool.size(); i++) {
    //    objectPool[i].PhysicsStep(deltaTime);
    //}

    worldObjects = world->getObjects();
    world->tick(deltaTime);
}

void Assignment5::Draw() {
    if (Input::IsMouseClicked(0)) {
        world->isSimulating = true;
        initMousePosition = Input::GetMousePos();
    }

    if (Input::IsMouseDown(0)) {
        mousePosition = Input::GetMousePos();
        Draw::SetColor(Colors::orange);
        Draw::Arrow(worldObjects[0].position,
            worldObjects[0].position + mousePosition - initMousePosition);
        world->imagine(mousePosition - initMousePosition, trajectorySteps);
    }

    if (Input::IsMouseReleased(0)) {
        world->isSimulating = false;
        world->addImpulse((mousePosition - initMousePosition) * 5.0f);
    }

    for (int i = 0; i < worldObjects.size(); i++) {
        // Draw circle
        Draw::SetColor(0xffffffff);
        if (i == 0)
        {
            Draw::Circle(worldObjects[i].position,
                         worldObjects[i].circleRadius, true);
        } else {
            Draw::Circle(worldObjects[i].position, worldObjects[i].circleRadius);
        }

        Draw::SetColor(0xff00ff00);
        Draw::Line(worldObjects[i].position,
                   worldObjects[i].position + worldObjects[i].velocity / 4.0f);
    }

    for (int i = 0; i < boundsPool.size(); i++) {
        boundsPool[i].Draw();
    }

    

    for (int i = 0; i < colliders.size(); i++) {
        Draw::SetColor(Colors::orange);
        colliders[i].Draw();
    }
}

void Assignment5::DrawGUI() {
    ImGui::Begin("Inspector");
    for (int i = 0; i < worldObjects.size(); i++) {
        ImGui::PushID(i);
        ImGui::DragFloat2("Circle Position", &worldObjects[i].position[0],
                          0.1f);
        ImGui::DragFloat("Circle Radius", &worldObjects[i].circleRadius, 0.1f);
        ImGui::DragFloat2("Velocity", &worldObjects[i].velocity[0], 0.1f);
        ImGui::DragFloat2("Acceleration", &worldObjects[i].acceleration[0],
                          0.1f);
        ImGui::PopID();
    }


    ImGui::End();
}

void Assignment5::addGameObject(Circle& obj) {
    objectPool.push_back(obj);
}

void Assignment5::registerBounds(Bounds& bound) {
    for (int i = 0; i < objectPool.size(); i++) {
        //objectPool[i].bounds.push_back(bound);
        world->registerBounds(bound);
    }
}

void Assignment5::registerCollider(Circle& obj, Collider& collider) {
    obj.colliders.push_back(collider);
}