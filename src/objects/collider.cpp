#include <iostream>
#include <math.h>
#include "core/Draw.h"
#include "imgui.h"
#include "collider.h"

Collider::Collider(glm::vec2 posA, glm::vec2 posB)
    : pointA(0, 0), pointB(1, 0), normal(0, 0) {
    
    pointA = posA;
    pointB = posB;
    normal = getNormal(ccw);

}

Collider::~Collider() {}

glm::vec2 Collider::getNormal(dir val) {
    glm::vec2 line = pointB - pointA;
    glm::vec2 lineNormalized = normalized(line);

    if (val == cw){
        return glm::vec2(lineNormalized.y, lineNormalized.x * -1);
    }
    else if (val == ccw){
        return glm::vec2(lineNormalized.y * -1, lineNormalized.x);
    } else {
        std::cout << "wrong input" << std::endl;
        return glm::vec2(-1, 0);
    }
}

glm::vec2 Collider::normalized(glm::vec2 v) {
    float magnitude = sqrt(pow(v.x, 2) + pow(v.y, 2));

    return glm::vec2(v / magnitude);
}

void Collider::Draw() {
    Draw::Line(pointA, pointB);

    glm::vec2 offset = (pointB - pointA) * 0.5f;

    Draw::Line(pointA + offset, normal + pointA + offset);
}
