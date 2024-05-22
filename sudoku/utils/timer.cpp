#include "timer.h"
#include <stdio.h>
#include <chrono>

int timer(int start_clock)
{
	static std::chrono::system_clock::time_point start;
	static std::chrono::system_clock::time_point end;

	if (start_clock)
	{
		start = std::chrono::system_clock::now();
		return -1;
	}
	else
	{
		end = std::chrono::system_clock::now();
		auto elapsed =
			std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		return elapsed.count();
	}
}