#pragma once
#include "Module.h"
#include "Assimp/include/assimp/scene.h"
#include "Assimp/include/assimp/material.h";
#include <vector>;
class Model : public Module
{
public:
	void Model::Load(const char* file_name);
	void Model::LoadMaterials(const aiScene* scene);
private:
	std::vector<unsigned int> materials;
};

