#include <imgui.h>
#include <math.h>
#include <iostream>
#include "ForceField.h"
#include "core/Draw.h"

ForceField::ForceField(glm::vec2 pos, int rad)
    : position(0, 0), radius(3) {
    position = pos;
    radius = rad;
}

ForceField::~ForceField() {}

void ForceField::Draw() {
    Draw::SetColor(0x330000ff);
    Draw::Circle(position, radius, true);
}
