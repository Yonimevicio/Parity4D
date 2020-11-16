#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleCamera;
class ModuleEditor;
class ModuleTexture;
class ModuleDebugDraw;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	float GetDeltaTime();
public:
	ModuleRender* renderer = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* renderer_ex = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleDebugDraw* debdraw = nullptr;

private:
	float delta_time = 0.0f;
	unsigned previous_time = 0;
	std::list<Module*> modules;

};

extern Application* App;
