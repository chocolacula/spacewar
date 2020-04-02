#include "SystemQueue.h"

#include <algorithm> 
#include <stdexcept>

void SystemQueue::Add(ISystem* system, int priority)
{
	{
		//TODO it has O(n) complexity, at the moment it's fine but could be optimized
		const auto it = std::find_if(_data.begin(), _data.end(),
			[system](QueueEntry e) { return e.system == system; });

		if (it != _data.end())
		{
			throw std::runtime_error("The System already exist in queue");
		}
	}

	auto it = _data.rbegin();
	for(; it != _data.rend(); ++it)
	{
		if (it->priority <= priority)
		{
			break;
		}
	}
	
	_data.emplace(it.base(), system, priority);
}

void SystemQueue::Remove(ISystem* system)
{
	_data.erase(std::remove_if(_data.begin(), _data.end(), 
		[system](QueueEntry e) { return e.system == system; }), _data.end());
}

std::vector<SystemQueue::QueueEntry>::iterator SystemQueue::begin()
{
	return _data.begin();
}

std::vector<SystemQueue::QueueEntry>::iterator SystemQueue::end()
{
	return _data.end();
}

SystemQueue::QueueEntry::QueueEntry(ISystem* system, const int priority) :
	system(system),
	priority(priority)
{}
