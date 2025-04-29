#include "World.h"
#include <typeinfo>
#include <string.h>
#include "imgui.h"

float deltaT; 
float damping = 0.4;

World::World() {}

World::~World() {}

void World::registerObject(Circle& obj) {
    //std::cout << "Obj: " << obj->GetName() << std::endl;
    objects.push_back(obj);
    //std::cout << "Object list size: " << objects.size() << std::endl;
    //std::cout << "Is obj dynamic: " << objects[i].isDynamic << std::endl;
    
}

void World::registerCollider(Collider& col) {
    colliders.push_back(col);
}

void World::registerBounds(Bounds& bound) {
    bounds.push_back(bound);
}

void World::deregisterObject(std::shared_ptr<GameObject> obj) {}


void World::testCircleCollision(Circle& obj1, Circle& obj2) {
     //std::cout << "checking circle collisions" << std::endl;

    glm::vec2 AB = obj2.position - obj1.position;
    glm::vec2 normalAB = glm::normalize(AB);
    float distance = glm::length(AB);
    float intersectionDepth = obj1.circleRadius + obj2.circleRadius - distance;
    if (intersectionDepth >= 0) {
        glm::vec2 relativeVelocity = obj1.velocity - obj2.velocity;
        float force = glm::length(obj1.velocity) + glm::length(obj2.velocity);

        obj1.position -= normalAB * (intersectionDepth * 0.5f);
        obj2.position += normalAB * (intersectionDepth * 0.5f);

        /*obj1.velocity =
            glm::normalize(obj1.velocity -
            2.0f * (glm::dot(-normalAB, obj1.velocity) * -normalAB)) * force / obj1.mass;*/

        obj1.velocity += -normalAB * force / obj1.mass;

        /*obj2.velocity = glm::normalize(obj2.velocity - 2.0f * (glm::dot(-normalAB, obj2.velocity) * -normalAB)) * force / obj2.mass;*/

        //obj2.velocity = normalAB * force / obj2.mass;

        obj2.velocity += normalAB * force / obj2.mass;
    }

}

void World::testHalfSpaceCollision(Circle& obj, Collider& collider) {
    //std::cout << "checking half space collisions" << std::endl;
    float distance = glm::dot(obj.position, collider.normal) - obj.circleRadius -
                        glm::dot(collider.pointA, collider.normal);

    //std::cout << distance << std::endl;

        if (distance <= 0) {
            //std::cout << "Hit";
            glm::vec2 trajectory = glm::normalize(obj.velocity * -1.0f);
            // pos += trajectory * abs(distance);
            obj.position += collider.normal * abs(distance);
             //velocity = glm::vec2(0);

            /*std::cout << colliders[i].normal[0] << " ,"  <<
               colliders[i].normal[1]
                      << std::endl;*/

            obj.velocity =
                obj.velocity - 2.0f * (glm::dot(collider.normal, obj.velocity) *
                                   collider.normal);
        }
}

void World::testBoundsCollision(Circle& obj) {
    // implement bound hitting here
    for (int i = 0; i < bounds.size(); i++) {
        // Lower Bounds
        if (bounds[i].normal[1] > 0 &&
            obj.position[1] < bounds[i].position[1] + obj.circleRadius) {
            obj.position[1] = bounds[i].position[1] + obj.circleRadius;
            obj.velocity = obj.velocity * glm::vec2(1, -1);
        }

        // Upper Bounds
        if (bounds[i].normal[1] < 0 &&
            obj.position[1] > bounds[i].position[1] - obj.circleRadius) {
            obj.position[1] = bounds[i].position[1] - obj.circleRadius;
            obj.velocity = obj.velocity * glm::vec2(1, -1);
        }

        // Left Bounds
        if (bounds[i].normal[0] > 0 &&
            obj.position[0] < bounds[i].position[0] + obj.circleRadius) {
            obj.position[0] = bounds[i].position[0] + obj.circleRadius;
            obj.velocity = obj.velocity * glm::vec2(-1, 1);
        }

        // Right Bounds
        if (bounds[i].normal[0] < 0 &&
            obj.position[0] > bounds[i].position[0] - obj.circleRadius) {
            obj.position[0] = bounds[i].position[0] - obj.circleRadius;
            obj.velocity = obj.velocity * glm::vec2(-1, 1);
        }
        // should calculate bounce direction based on normal of the plane that
        // it's bouncing on, not hard code it but will do that some other time
    }
}

void World::calculateAcceleration(Circle& obj, glm::vec2 cummulative) {
    obj.acceleration = glm::vec2(0, 0);

    
    obj.acceleration += gravity;
    obj.acceleration += cummulative / obj.mass;
}

void World::physicsStep(Circle& obj, float dt) {
    glm::vec2 cummulativeForce = glm::vec2(0);

    

    for (int i = 0; i < obj.forces.size(); i++) {
        std::cout << "Force field at: " << obj.forces[i].position[0] << ", "
                  << obj.forces[i].position[1];
        if (glm::length(obj.forces[i].position - obj.position) <
            obj.forces[i].radius + obj.circleRadius) {
            glm::vec2 force = obj.position - obj.forces[i].position;
            int scalar = 10;
            cummulativeForce += glm::vec2(force[0] * scalar, force[1] * scalar);
        }
    }

    calculateAcceleration(obj, cummulativeForce);
    calculateVelocity(obj, dt);
    
    obj.position = obj.position + obj.velocity * dt;
    cummulativeForce = glm::vec2(0);
}

void World::imagine(glm::vec2 mousePos, int steps) {
    Circle tempCircle(objects[0].position, objects[0].mass);
    tempCircle.velocity = objects[0].velocity;
    tempCircle.acceleration = objects[0].acceleration;

    

    tempCircle.velocity += mousePos * 5.0f / tempCircle.mass;

    Draw::SetColor(0x44ff88ff);
    for (int i = 0; i < steps; i++) {
        calculateAcceleration(tempCircle,  glm::vec2(0));
        calculateVelocity(tempCircle, deltaT);

        tempCircle.position =
            tempCircle.position + tempCircle.velocity * deltaT;
        
        testBoundsCollision(tempCircle);
        for (int j = 0; j < colliders.size(); j++) {
            testHalfSpaceCollision(tempCircle, colliders[j]);
        }

        Draw::Circle(tempCircle.position, tempCircle.circleRadius);
    }
}

void World::addImpulse(glm::vec2 impulse) {
    objects[0].velocity += impulse / objects[0].mass;
}

void World::setDamping(float value) {
    damping = value;
}

void World::calculateVelocity(Circle& obj, float dt) {
    
    obj.velocity = obj.velocity + obj.acceleration * dt;
    obj.velocity *= 1 - damping * dt;
}


void World::tick(float deltaTime) {
    deltaT = deltaTime;
    for (int i = 0; i < objects.size(); i++)
    {
        if (!objects[i].isDynamic) continue;
        //objects[i].PhysicsStep(deltaTime);
        if (!isSimulating) physicsStep(objects[i], deltaTime);
        

        testBoundsCollision(objects[i]);

        //Check collisions with other objects
        for (int j = i + 1; j < objects.size(); j++) {
            if (i == j) continue;
            
            testCircleCollision(objects[i], objects[j]);
        }
        
        // Check collisions with colliders
        for (int j = 0; j < colliders.size(); j++) {
            testHalfSpaceCollision(objects[i], colliders[j]);
        }
    
    }

}

std::vector<Circle> World::getObjects() {
    return objects;
}





// std::cout << (typeid(circle) == typeid(Collider*));