#pragma once

#include "ISystem.h"
#include "SystemQueue/SystemQueue.h"

class SystemManager
{
public:
	~SystemManager()
	{
		for (auto&& entry : _systems)
		{
			delete entry.system;
		}
	}
	
	void HandleAllSystems()
	{
		for (auto&& entry : _systems)
		{
			entry.system->Run();
		}
	}
	
	template <typename T, typename... TArg>
	T* Create(int priority, TArg... args)
	{
		static_assert(std::is_base_of<class ISystem, T>::value, "The type must realize the ISystem interface");

		auto system = new T(args...);

		_systems.Add(reinterpret_cast<ISystem*>(system), priority);

		return system;
	}

private:
	SystemQueue _systems;
};