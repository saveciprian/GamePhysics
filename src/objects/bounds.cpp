#include "bounds.h"
#include "core/Draw.h"
#include <iostream>
#include <math.h>
#include <imgui.h>

Bounds::Bounds(glm::vec2 pos, glm::vec2 norm, int width)
    : position(0, 0), normal(0, 1), size(10) {
    position = pos;
    normal = norm;
    size = width;
}

Bounds::~Bounds() {}

void Bounds::Draw() {
    Draw::SetColor(0xffff3333);
    if (normal[0] == 0)
    {
        Draw::Line(glm::vec2(position[0] - size, position[1]),
                   glm::vec2(position[0] + size, position[1]));
    }
    else if (normal[1] == 0)
    {
        Draw::Line(glm::vec2(position[0], position[1] - size),
                   glm::vec2(position[0], position[1] + size));
    }
}
