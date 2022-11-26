#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <cstdio>
#include <iostream>


class Timer{
	public:
		Timer(std::string name = "{}"): m_Name(name){
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~Timer(){
			Stop();
		}

		void Stop(){
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
			auto duration = end - start;
			auto ms = duration * .001;
			auto s = ms * .001;
			std::cout << m_Name << "\nTime: " << duration << " us, " << ms << " ms, " << s << " s\n";
		}

	private:
		std::string m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

#endif