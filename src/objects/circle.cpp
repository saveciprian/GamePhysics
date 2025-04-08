#include "circle.h"
#include "core/Draw.h"
#include <iostream>
#include <math.h>

Circle::Circle(glm::vec2 pos)
    : position(0, 4),
      circleRadius(1),
      velocity(0, 0),
      acceleration(0, 0),
      deltaTime(0) {

    position = pos;
}

Circle::~Circle() {}

void Circle::CalculateAcceleration() {
    acceleration = glm::vec2(0, 0);


    //should add forces here I think? If there are no forces acting on the object it should only respond to gravity; maybe also drag?
    glm::vec2 gravity = glm::vec2(0, -9.81);
    acceleration += gravity;

    for (int i = 0; i < forceFields.size(); i++) {
        acceleration += forceFields[i];
        
    }

    forceFields.clear();

}
    
void Circle::CalculateVelocity() {
    velocity = velocity + acceleration * deltaTime;
}

int Circle::getMangitude(glm::vec2 vec)
{
    return sqrt(pow(vec[0], 2) + pow(vec[1], 2));
}

void Circle::PhysicsStep(float dt) {
    deltaTime = dt; //set object's value for delta time
    CalculateAcceleration();
    CalculateVelocity();
    position = position + velocity * deltaTime;

    glm::vec2 forceField(-1, 0);
    if (getMangitude(forceField - position) < 1 + circleRadius)
    {
        glm::vec2 force = position - forceField;
        int scalar = 10;
        forceFields.push_back(glm::vec2(force[0] * scalar, force[1] * scalar));
        std::cout << "Force: " << (position - forceField)[0] << ", "
                  << (position - forceField)[1] << std::endl;
        
    }

    if (position[1] < 0 + circleRadius) {
        /*int i = abs(position[i]);*/


        position[1] = 0 + circleRadius;
        velocity = velocity * glm::vec2(1, -1);
    }

}

void Circle::Draw()
{
    Draw::Circle(glm::vec2(-1, 0), 1);
    Draw::Circle(position, circleRadius);
}

void Circle::Collide() {}
