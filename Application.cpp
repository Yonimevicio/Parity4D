#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"
#include "ModuleTexture.h"
#include "ModuleModel.h"
using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(texture = new ModuleTexture());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(debdraw = new ModuleDebugDraw());
	modules.push_back(model = new ModuleModel());
	
	
	 
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;
	previous_time = SDL_GetTicks();
	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();
	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Start();
	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	unsigned time_now = SDL_GetTicks();
	if (SDL_TICKS_PASSED(time_now, previous_time))
	{
		delta_time = (time_now - previous_time) / 1000.0f;

		for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->PreUpdate();

		for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->Update();

		for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->PostUpdate();
	}
	previous_time = time_now;
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
float Application::GetDeltaTime()
{
	return delta_time;
}