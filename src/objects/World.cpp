#include "World.h"
#include <typeinfo>
#include <string.h>
#include "imgui.h"


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

void World::deregisterObject(std::shared_ptr<GameObject> obj) {}


void World::testCircleCollision() {
     std::cout << "checking circle collisions" << std::endl;
}

void World::testHalfSpaceCollision(Circle& obj, Collider& collider) {
    std::cout << "checking half space collisions" << std::endl;
    float distance = glm::dot(obj.position, collider.normal) - obj.circleRadius -
                        glm::dot(collider.pointA, collider.normal);

    std::cout << distance << std::endl;

        if (distance <= 0) {
            std::cout << "Hit";
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

void World::tick(float deltaTime) {
    for (int i = 0; i < objects.size(); i++)
    {
        if (!objects[i].isDynamic) continue;
        objects[i].PhysicsStep(deltaTime);

        //Check collisions with other objects
        for (int j = 0; j < objects.size(); j++) {
            if (i == j) continue;

            testCircleCollision();
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