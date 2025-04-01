#include "circle.h"
#include "core/Draw.h"
#include <iostream>

Circle::Circle()
    : position(0, 4),
      circleRadius(1),
      velocity(0, 0),
      acceleration(0, -9.81),
      deltaTime(0) {
}

Circle::~Circle() {}

void Circle::CalculateAcceleration() {
    //should add forces here I think? If there are no forces acting on the object it should only respond to gravity; maybe also drag?


}
    
void Circle::CalculateVelocity() {
    velocity = velocity + acceleration * deltaTime;
}

void Circle::PhysicsStep(float dt) {
    deltaTime = dt; //set object's value for delta time
    CalculateAcceleration();
    CalculateVelocity();

    if (position[1] < 0 + circleRadius) {
        position[1] = 0 + circleRadius;
        velocity = velocity * glm::vec2(-1, -1);
    }

    position = position + velocity * deltaTime;
}

void Circle::Draw()
{
    Draw::Circle(position, circleRadius);
}

void Circle::Collide() {}
