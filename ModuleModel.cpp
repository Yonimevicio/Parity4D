#include "ModuleModel.h"
#include "Application.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "ModuleTexture.h"

void ModuleModel::Load(const char* file_name) {
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);    
	if (scene) {        
		LoadMaterials(scene);
		LoadMeshes(scene);    
	}else{        
		LOG("Error loading %s: %s", file_name, aiGetErrorString());
	}

}
void ModuleModel::LoadMaterials(const aiScene* scene) {
	aiString file;    
	materials.reserve(scene->mNumMaterials);    
	for (unsigned i = 0; i < scene->mNumMaterials; ++i) { 
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) { 
			materials.push_back(App->texture->LoadTexture(file.data)); 
		} 
	} 
}

void ModuleModel::LoadMeshes(const aiScene* scene) {
	aiString file;
	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		ModuleMesh mesh;
		mesh.Load(scene->mMeshes[i]);
		meshes.push_back(mesh);
	}
}
bool ModuleModel::CleanUp()
{
	// clean meshes
	for (ModuleMesh& mesh : meshes)
	{
		mesh.CleanUp();
	}
	meshes.clear();

	// clean materials
	for (unsigned material : materials)
	{
		App->texture->CleanUp(material);
	}
	materials.clear();
	return true;
}

void ModuleModel::Draw() const
{
	for (const ModuleMesh& mesh : meshes)
	{
		mesh.Draw(materials);
	}
}