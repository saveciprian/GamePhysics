#include "circle.h"
#include "core/Draw.h"
#include <iostream>
#include <math.h>

int forceFieldRadius = 3;

Circle::Circle(glm::vec2 pos)
    : position(0, 4),
      circleRadius(1),
      velocity(0, 0),
      acceleration(0, 0),
      deltaTime(0),
      mass(10.0) {
    position = pos;
}

Circle::Circle(glm::vec2 pos, float m)
    : position(0, 4),
      circleRadius(1),
      velocity(0, 0),
      acceleration(0, 0),
      deltaTime(0),
      mass(10.0) {

    position = pos;
    mass = m;

}

Circle::~Circle() {}

void Circle::CalculateAcceleration(glm::vec2 cummulative) {
    acceleration = glm::vec2(0, 0);


    //should add forces here I think? If there are no forces acting on the object it should only respond to gravity; maybe also drag?
    glm::vec2 gravity = glm::vec2(0, -9.81);
    acceleration += gravity;
    acceleration += cummulative / mass;

    //for (int i = 0; i < forceFields.size(); i++) {
    //    acceleration += forceFields[i];
    //    
    //}



    forceFields.clear();

}
    
void Circle::CalculateVelocity() {
    velocity = velocity + acceleration * deltaTime;
}

int Circle::getMangitude(glm::vec2 vec)
{
    return sqrt(pow(vec[0], 2) + pow(vec[1], 2));
}

void Circle::AddImpulse(glm::vec2 impulsePos) {
    float mouseInfluence = 5.0;
    
    glm::vec2 mouseToObj = (position - impulsePos);
    


    velocity += normalized(mouseToObj) * mapRange(magnitude(mouseToObj), 0, 10, 20, 0);

}

float Circle::mapRange(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    
}

float Circle::magnitude(glm::vec2 v) {
    return (float)sqrt(pow(v.x, 2) + pow(v.y, 2));
}

glm::vec2 Circle::normalized(glm::vec2 v) {
    return glm::vec2(v.x, v.y) / magnitude(v);
}




void Circle::PhysicsStep(float dt) {

    deltaTime = dt; //set object's value for delta time
    glm::vec2 cummulativeForce = glm::vec2(0);
    for (int i = 0; i < forces.size(); i++) {
        /*std::cout << "Force field at: " << forces[i].position[0] << ", "
                  << forces[i].position[1];*/
        if (getMangitude(forces[i].position - position) < forces[i].radius + circleRadius) {
            glm::vec2 force = position - forces[i].position;
            int scalar = 10;
            cummulativeForce += glm::vec2(force[0] * scalar, force[1] * scalar);
        }
    }



    CalculateAcceleration(cummulativeForce);
    CalculateVelocity();
    position = position + velocity * deltaTime;
    //Reset cummulative force vector
    cummulativeForce = glm::vec2(0);

    //glm::vec2 forceField(-1, 0);
    
    //if (getMangitude(forceField - position) < forceFieldRadius /* <- force field's influence */ + circleRadius)
    //{
    //    glm::vec2 force = position - forceField;
    //    int scalar = 10;
    //    forceFields.push_back(glm::vec2(force[0] * scalar, force[1] * scalar));
    //    std::cout << "Force: " << (position - forceField)[0] << ", "
    //              << (position - forceField)[1] << std::endl;
    //    
    //}



    //implement bound hitting here
    for (int i = 0; i < bounds.size(); i++)
    {
        //Lower Bounds
        if (bounds[i].normal[1] > 0 && position[1] < bounds[i].position[1] + circleRadius) {
            position[1] = bounds[i].position[1] + circleRadius;
            velocity = velocity * glm::vec2(1, -1);
        }

        //Upper Bounds
        if (bounds[i].normal[1] < 0 && position[1] > bounds[i].position[1] - circleRadius) {
            position[1] = bounds[i].position[1] - circleRadius;
            velocity = velocity * glm::vec2(1, -1);
        }

        //Left Bounds
        if (bounds[i].normal[0] > 0 && position[0] < bounds[i].position[0] + circleRadius) {
            position[0] = bounds[i].position[0] + circleRadius;
            velocity = velocity * glm::vec2(-1, 1);
        }

        // Right Bounds
        if (bounds[i].normal[0] < 0 && position[0] > bounds[i].position[0] - circleRadius) {
            position[0] = bounds[i].position[0] - circleRadius;
            velocity = velocity * glm::vec2(-1, 1);
        }
        //should calculate bounce direction based on normal of the plane that it's bouncing on, not hard code it but will do that some other time

    }
}

void Circle::Draw()
{
    Draw::Circle(glm::vec2(-1, 0), 1);
    Draw::Circle(position, circleRadius);
}

void Circle::Collide() {}
