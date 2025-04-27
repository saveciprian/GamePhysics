#include "GameObject.h"

GameObject::GameObject() : isDynamic(false), deltaTime(0), position(0, 0) {}

GameObject::GameObject(bool dynamic)
    : isDynamic(false), deltaTime(0), position(0, 0) {

	isDynamic = dynamic;
}

GameObject::~GameObject() {}

const char* GameObject::GetName() {
    return "Game Object";
}
