#include "Random.h"

std::random_device					Random::_rd;
std::mt19937						Random::_mt(_rd());
std::uniform_int_distribution<int>	Random::_dist;

int Random::Next()
{
	return _dist(_mt);
}

int Random::Next(const int from, const int to)
{
	return (Next() % to) + from;
}

float Random::Next(const float from, const float to)
{
	//TODO make it faster
	return (float)Next((int)(from * 100), (int)(to * 100)) / 100;
}