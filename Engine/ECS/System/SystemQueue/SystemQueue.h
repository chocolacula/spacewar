#pragma once

#include <vector>

class ISystem;

// sorted in priority order but not common priority queue
class SystemQueue
{
public:
	struct QueueEntry
	{
		ISystem* system;
		int priority;

		QueueEntry(ISystem* system, int priority);	
	};

	void Add(ISystem* system, int priority);
	void Remove(ISystem* system);

	std::vector<QueueEntry>::iterator begin();
	std::vector<QueueEntry>::iterator end();

private:
	std::vector<QueueEntry> _data;
};

bool operator< (int priority, const SystemQueue::QueueEntry& right);
