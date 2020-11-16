#pragma once
#include "Module.h"


class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

private:
	void RenderVBO(unsigned vbo, unsigned program);
private:
	void* context;
	unsigned int triangle = 0;
	unsigned int lenna = 0;

};

