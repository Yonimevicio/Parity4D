#include "MicroTimer.h"
#include "SDL.h"
//void MicroTimer::Start() {
//	current_time = SDL_GetPerformanceCounter();
//	last_time = SDL_GetPerformanceCounter();
//	counting = true;
//};
//unsigned int MicroTimer::Read() {
//	if (counting) current_time = SDL_GetPerformanceCounter();
//
//	return current_time - last_time / SDL_GetPerformanceFrequency();
//};
//unsigned int MicroTimer::Stop() {
//	current_time = SDL_GetPerformanceCounter();
//	counting = false;
//};