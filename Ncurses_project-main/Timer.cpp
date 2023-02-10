#include "Timer.hpp"

Timer::Timer(const int time, bool start)
: time{ time }, current{ 0 }, active{ start }
{}

void Timer::update() {
	if (active && current < time) 
		current++;
}

bool Timer::wait() {
	if (current >= time) {
		current = 0;
		return true;
	} return false;
}

void Timer::start() {
	active = true;
}

void Timer::stop() {
	active = false;
	current = 0;
}

bool Timer::hasStarted() const {
	return active;
}

int Timer::currentTime() const {
	return current;
}