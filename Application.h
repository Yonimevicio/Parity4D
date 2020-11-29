#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRender;
class ModuleProgram;
class ModuleCamera;
class ModuleEditor;
class ModuleTexture;
class ModuleDebugDraw;
class ModuleModel;

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
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleDebugDraw* debdraw = nullptr;
	ModuleModel* model = nullptr;

private:
	float delta_time = 0.0f;
	unsigned previous_time = 0;
	std::list<Module*> modules;

};

extern Application* App;
