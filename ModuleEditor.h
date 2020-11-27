#pragma once
#include "Module.h"
#include "SDL.h"
#include "Console.h"
class ModuleEditor : public Module
{

public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status Update();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	bool IsMenuHovered() const {
		return isMenuHovered;
	};

private:
	bool isMenuHovered = false;
	char* dropped_file;
	SDL_Event event;
	bool* p_open;

public:
	Console* cmd = nullptr;
};