#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <cstdio>
#include <iostream>

class Timer{
	public:
		Timer(std::string name = "{}"): m_Name(name) {
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		};
		~Timer();
		void Stop();

	private:
		std::string m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

#endif