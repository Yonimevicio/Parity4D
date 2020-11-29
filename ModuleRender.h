#pragma once
#include "Module.h"


class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	int GetTexture() { return texture; }
	void RenderViewport(int width, int height);

public:
	void* context;

private:
	unsigned int fbo = 0;
	unsigned int texture = 0;
	unsigned int rbo = 0;

};

