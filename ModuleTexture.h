#pragma once
#include "Module.h"
#include <string>
#include <map>
class ModuleTexture : public Module {

public:
	ModuleTexture();
	~ModuleTexture();
	
	bool Init();
	bool CleanUp(unsigned int texture);
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	unsigned int LoadTexture(const std::string path, const std::string fullpath);
private:
	std::map<std::string, unsigned int> textureMap;
	bool texture_is_load;

public:
	const unsigned int GetFirstTexture() {
			return textureMap.begin()->second;
	}
	const std::string GetFirstTextureSource() {
		return  textureMap.begin()->first;
	};
	const bool TextureIsLoad() {
		return texture_is_load;
	}
};