#pragma once

#include <random>

class Random
{
public:
	Random() = delete;
	
	static int Next();
	static int Next(int from, int to);
	static float Next(float from, float to);

private:
	static std::random_device					_rd;
	static std::mt19937							_mt;
	static std::uniform_int_distribution<int>	_dist;
};
