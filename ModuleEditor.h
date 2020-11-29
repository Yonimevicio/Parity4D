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
	bool ViewportEventsEnabled() const {
		return is_viewport_focus;
	};

	void SetViewPortFocus(bool focus) {
		is_viewport_focus = focus;
	};

private:
	bool is_menu_hovered = false;
	bool is_viewport_focus = false;
	char* dropped_file;
	SDL_Event event;

public:
	Console* cmd = nullptr;
};