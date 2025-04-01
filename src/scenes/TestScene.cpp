#include "TestScene.h"

#include "core/Draw.h"
#include "imgui.h"

TestScene::TestScene() : circlePosition(0, 1), circleRadius(1) {} //you can initialize the variables in the constructor of the class

TestScene::~TestScene() {}

void TestScene::OnEnable() {}

void TestScene::OnDisable() {}

void TestScene::Update(float deltaTime) {} //physics calculations go in here

void TestScene::Draw() { //drawing the objects go in here 
    Draw::Circle(circlePosition, circleRadius);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));
}

void TestScene::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f); //give the first value of the vector and it will find the second one automatically
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    ImGui::End();

    //for (size_t = 0; i < test3.size(); i++) {
    //    ImGUI::PushID(i);
    //    ImGUI::PopID();

    //}
}

// ImGUI = Immediate Mode GUI -- something something GUI that runs during the app?
//once you run the program, ImGUI has a Dear ImGUI command that launches a tutorial teaching you how it works
//you can cross reference the code for this tutorial at Dependencies > imgui > Source Files > imgui_demo.cpp
