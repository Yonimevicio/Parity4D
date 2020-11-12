#pragma once
#include "Module.h"

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
};