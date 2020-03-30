#include "SystemQueue.h"

#include <algorithm> 

void SystemQueue::Add(ISystem* system, int priority)
{
	const auto it = std::find_if(_data.begin(), _data.end(), 
		[system](QueueEntry e) { return e.system == system; });

	if (it != _data.end())
	{
		throw std::runtime_error("The System already exist in queue");
	}

	_data.emplace_back(system, priority);

	const auto bound = std::upper_bound(_data.rbegin() + 1, _data.rend(), priority);

	if (bound != _data.rend())
	{
		std::rotate(_data.rbegin(), _data.rbegin() + 1, bound);
	}
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

bool operator< (const int priority, const SystemQueue::QueueEntry& right)
{
	return priority < right.priority;
}
