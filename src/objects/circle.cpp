#include "circle.h"
#include "core/Draw.h"
#include <iostream>
#include <math.h>
#include "imgui.h"
#include "../core/Colors.h"

int forceFieldRadius = 3;

Circle::Circle(glm::vec2 pos)
    : GameObject(true),
      position(0, 4),
      circleRadius(1),
      velocity(0, 0),
      acceleration(0, 0),
      deltaTime(0),
      mass(10.0) {
    
    position = pos;
    
}

Circle::Circle(glm::vec2 pos, float m)
    : GameObject(true),
      position(0, 4),
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

void Circle::AddImpulse(glm::vec2 impulse) {
    /*float mouseInfluence = 5.0;

     glm::vec2 mouseToObj = (position - impulsePos);


     std::cout << "Magnitude: " << mapRange(magnitude(mouseToObj), 0, 5, 40, 0)
     / mass << std::endl;*/
    // velocity += normalized(mouseToObj) *
    // mapRange(magnitude(mouseToObj), 0, 5, 100, 0) / mass;
    velocity += impulse / mass;

}

float Circle::mapRange(float x, float in_min, float in_max, float out_min, float out_max) {
    if (x < in_min)
        x = in_min;
    if (x > in_max)
        x = in_max;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    
}

float Circle::magnitude(glm::vec2 v) {
    return (float)sqrt(pow(v.x, 2) + pow(v.y, 2));
}

glm::vec2 Circle::normalized(glm::vec2 v) {
    //return glm::vec2(v.x, v.y) / magnitude(v);
    return glm::vec2(v.x, v.y) / glm::length(v);
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


    checkBounds(velocity, position);
    checkCollisions(velocity, position);

}

void Circle::checkBounds(glm::vec2& vel, glm::vec2& pos) {
    // implement bound hitting here
    for (int i = 0; i < Circle::bounds.size(); i++) {
        // Lower Bounds
        if (bounds[i].normal[1] > 0 &&
            pos[1] < bounds[i].position[1] + circleRadius) {
            pos[1] = bounds[i].position[1] + circleRadius;
            vel = vel * glm::vec2(1, -1);
        }

        // Upper Bounds
        if (bounds[i].normal[1] < 0 &&
            pos[1] > bounds[i].position[1] - circleRadius) {
            pos[1] = bounds[i].position[1] - circleRadius;
            vel = vel * glm::vec2(1, -1);
        }

        // Left Bounds
        if (bounds[i].normal[0] > 0 &&
            pos[0] < bounds[i].position[0] + circleRadius) {
            pos[0] = bounds[i].position[0] + circleRadius;
            vel = vel * glm::vec2(-1, 1);
        }

        // Right Bounds
        if (bounds[i].normal[0] < 0 &&
            pos[0] > bounds[i].position[0] - circleRadius) {
            pos[0] = bounds[i].position[0] - circleRadius;
            vel = vel * glm::vec2(-1, 1);
        }
        // should calculate bounce direction based on normal of the plane that
        // it's bouncing on, not hard code it but will do that some other time
    }
}

void Circle::checkCollisions(glm::vec2& vel, glm::vec2& pos) {
    //for (int i = 0; i < colliders.size(); i++)
    //{
    //    float distance = glm::dot(pos, colliders[i].normal) - 
    //                     circleRadius -
    //                     glm::dot(colliders[i].pointA, colliders[i].normal);

    //    if (distance <= 0)
    //    {
    //        std::cout << "Hit";
    //        glm::vec2 trajectory = glm::normalize(velocity * -1.0f);
    //        //pos += trajectory * abs(distance);
    //        pos += colliders[i].normal * abs(distance);
    //        //velocity = glm::vec2(0);

    //        /*std::cout << colliders[i].normal[0] << " ,"  << colliders[i].normal[1]
    //                  << std::endl;*/
    //        
    //        velocity = velocity - 2.0f * (glm::dot(colliders[i].normal, velocity) *
    //                   colliders[i].normal);
    //    }

    //}
}

void Circle::Imagine(glm::vec2 mousePos, int steps)
{   
    glm::vec2 tempPos = position;
    glm::vec2 tempVel = velocity;
    glm::vec2 tempAccel = acceleration;
    glm::vec2 gravity = glm::vec2(0, -9.81);

    tempVel += mousePos / mass;

    Draw::SetColor(0x448888ff);
    for (int i = 0; i < steps; i++)
    {
        tempAccel = glm::vec2(0);
        tempAccel += gravity;
       
        tempVel = tempVel + tempAccel * deltaTime;
        tempPos = tempPos + tempVel * deltaTime;
        checkBounds(tempVel, tempPos);
        Draw::Circle(tempPos, circleRadius);    
    }
}

void Circle::Draw()
{
    Draw::Circle(glm::vec2(-1, 0), 1);
    Draw::Circle(position, circleRadius);


    

}

void Circle::Collide() {}
