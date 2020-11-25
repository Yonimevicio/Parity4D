#pragma once
#include "Module.h"
#include "Assimp/include/assimp/scene.h"
#include "Assimp/include/assimp/material.h";
#include "ModuleMesh.h"
#include <vector>;
#include "MathGeoLib/Geometry/Sphere.h"

class ModuleModel : public Module
{
public:
	void Load(const char* file_path);
	void LoadMaterials(const aiScene* scene, const char* file_path);
	void LoadMeshes(const aiScene* scene);
	bool CleanUp();
	void Draw() const;

public:
	Sphere min_sphere;

private:
	std::vector<unsigned int> materials;
	std::vector<ModuleMesh> meshes;
	int num_vertices = 0;
	

public: 
	const int GetNumVertices() { return  num_vertices; };
};

