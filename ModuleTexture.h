#pragma once
#include "Module.h"
#include <string>
#include <map>
class ModuleTexture : public Module {

public:
	ModuleTexture();
	~ModuleTexture();
	
	bool Init();
	bool CleanUp();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	unsigned int LoadTexture(const std::string path);

private:
	std::map<std::string, unsigned int> textureMap;
	bool texture_is_load;

public:

	bool TextureIsLoad() {
		return texture_is_load;
	}
};