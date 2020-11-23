#pragma once
#include "Module.h"
#include "Assimp/include/assimp/scene.h"
#include "Assimp/include/assimp/material.h";
#include "ModuleMesh.h"
#include <vector>;
class ModuleModel : public Module
{
public:
	void Load(const char* file_path);
	void LoadMaterials(const aiScene* scene, const char* file_path);
	void LoadMeshes(const aiScene* scene);
	bool CleanUp();
	void Draw() const;
private:
	std::vector<unsigned int> materials;
	std::vector<ModuleMesh> meshes;
};

