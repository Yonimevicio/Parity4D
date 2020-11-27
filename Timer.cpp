#include "Timer.h"
#include "SDL.h"

void Timer::Start() {
	current_time = SDL_GetTicks();
	last_time = SDL_GetTicks();
	counting = true;
}
unsigned int Timer::Read() {
	if (counting) current_time = SDL_GetTicks();
	return current_time - last_time;
}
void Timer::Stop() {
	current_time = SDL_GetTicks();
	counting = false;
}