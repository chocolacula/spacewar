#pragma once
#include"../Entity/EntityDef.h"

template<typename T>
struct ComponentCollection
{
    ComponentCollection() :
        _beginPtr(nullptr),
        _currentIdx(0),
        _size(0)
    {}
	
    ComponentCollection(T** beginPtr, int size) :
        _beginPtr(beginPtr),
        _currentIdx(0),
        _size(size)
    {}
	
    bool Next(T*& component, bool isAll = false)
    {
        static_assert(std::is_base_of<class Component, T>::value, "The type must be derived from Component class");
    	
        while (_currentIdx < _size)
        {
            component = _beginPtr[_currentIdx];
            _currentIdx++;

            if (!isAll && (!component->GetEntity()->enabled || !component->enabled))
                continue;

            return component;
        }

        Reset();
    	
        component = nullptr;
        return false;
    }

    bool Previous(T*& component, bool isAll = false)
    {
        static_assert(std::is_base_of<class Component, T>::value, "The type must be derived from Component class");
    	
        while (_currentIdx < _size)
        {
            // the difference with Next() just in index
            component = _beginPtr[_size - 1 - _currentIdx];
            _currentIdx++;

            if (!isAll && (!component->GetEntity()->enabled || !component->enabled))
                continue;

            return component;
        }

        Reset();

        component = nullptr;
        return false;
    }

    void Reset()
    {
        _currentIdx = 0;
    }

    int Size() const
    {
        return _size;
    }

private:
    T** _beginPtr;

    int _currentIdx;
    int _size;
};
