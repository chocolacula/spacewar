#pragma once

#include <unordered_map>

#include "../../Types/Transform.h"
#include "../Component/Component.h"

class Entity
{
public:
	Entity() = default;

	explicit Entity(const Vector2& position);
	explicit Entity(const Transform& transform);

	~Entity();

    template<typename T>
	T* GetComponent();

    template<typename T, typename... TArg>
	T* AddComponent(TArg ... args);

    template<typename T>
	void RemoveComponent();

    bool enabled = true;

	Transform transform;

private:
    std::unordered_map<size_t, Component*> _componentsInEntity;
};
