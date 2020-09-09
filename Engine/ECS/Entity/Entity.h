#pragma once
#include "EntityDef.h"

#include <typeinfo>
#include <string>
#include <stdexcept>

#include "../../Scene.h"
#include "../../Utils/StringUtils.h"

inline Entity::Entity(const Vector2& position) :
	transform(position)
{}

inline Entity::Entity(const Transform& transform) :
	transform(transform)
{}

inline Entity::~Entity()
{
	for (auto&& component : _componentsInEntity)
	{
		Scene::GetComponentManager().Destroy(component.first, component.second);
	}
}

template <typename T>
T* Entity::GetComponent()
{
	static_assert(std::is_base_of<class Component, T>::value, "The type must be derived from Component class");

	const auto typeHash = typeid(T).hash_code();
	auto it = _componentsInEntity.find(typeHash);

	if (it != _componentsInEntity.end())
		return reinterpret_cast<T*>(it->second);

	return nullptr;
}

template <typename T, typename ... TArg>
T* Entity::AddComponent(TArg ... args)
{
	static_assert(std::is_base_of<class Component, T>::value, "The type must be derived from Component class");

	const auto typeHash = typeid(T).hash_code();
	const auto it = _componentsInEntity.find(typeHash);

	if (it != _componentsInEntity.end())
	{
		const auto msg = 
			std::string("Entity ")
			+ StringUtils::PtrToHexString((uintptr_t)this).value
			+ " already has a Component with type: "
			+ typeid(T).name();
		
		throw std::runtime_error(msg);
	}

	auto componentPtr = Scene::GetComponentManager().Create<T>(this, args...);

	_componentsInEntity[typeHash] = componentPtr;

	return componentPtr;
}

template <typename T>
void Entity::RemoveComponent()
{
	static_assert(std::is_base_of<class Component, T>::value, "The type must be derived from Component class");

	const auto typeHash = typeid(T).hash_code();
	auto it = _componentsInEntity.find(typeHash);

	if (it == _componentsInEntity.end())
	{
		return;
	}

	Scene::GetComponentManager().Destroy(typeHash, it->second);

	_componentsInEntity.erase(typeHash);
}
