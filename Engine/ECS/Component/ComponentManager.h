#pragma once

#include <unordered_map>
#include <typeinfo>
#include <utility>
#include <vector>
#include <algorithm>

#include "Component.h"
#include "ComponentCollection.h"

class Entity;

class ComponentManager
{
public:
    template<typename T>
    ComponentCollection<T> FindAllComponents()
    {
        static_assert(std::is_base_of<class Component, T>::value, "The type must be derived from Component class");
    	
	    const size_t typeHash = typeid(T).hash_code();

        auto it = _componentsByType.find(typeHash);

        if (it == _componentsByType.end())
            return ComponentCollection<T>();
    	
        return ComponentCollection<T>(reinterpret_cast<T**>(it->second.data()), (int)it->second.size());
    }

    template<typename T, typename... TArg>
    T* Create(Entity* entity, TArg... args)
    {
        static_assert(std::is_base_of<class Component, T>::value, "The type must be derived from Component class");

        auto componentPtr = new T(entity, args...);

        const size_t typeHash = typeid(T).hash_code();

        _componentsByType[typeHash].push_back(componentPtr);

        return componentPtr;
    }

	// TODO use a own typeid system to move from forward typeHash
    void Destroy(size_t typeHash, Component* component)
    {
        auto vector = &_componentsByType[typeHash];
        auto it = std::find(vector->begin(), vector->end(), component);
        
        if (it != vector->end())
        {
            delete *it;
            vector->erase(it);
            // type hashes are keep inside the map
        }
    }

private:
    std::unordered_map<size_t, std::vector<Component*>> _componentsByType;
};