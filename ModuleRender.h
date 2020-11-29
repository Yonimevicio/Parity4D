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
	void RenderVBO(unsigned vbo, unsigned program);

private:
	unsigned int triangle = 0;
	unsigned int lenna = 0;
	unsigned int house = 0;
	unsigned int house_text = 0;
	unsigned int fbo;
	unsigned int texture;
	unsigned int rbo;

};

