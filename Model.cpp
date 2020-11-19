#include "Model.h"
#include "Application.h"
#include "Assimp/include/assimp/scene.h"
#include "Assimp/include/assimp/cimport.h"
#include "Assimp/include/assimp/postprocess.h"
#include "ModuleTexture.h"

void Model::Load(const char* file_name) {
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);    
	if (scene) {        
		// TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);        
		// TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);    
	}else{        
		LOG("Error loading %s: %s", file_name, aiGetErrorString());
	}
}
void Model::LoadMaterials(const aiScene* scene) { 
	aiString file;    
	materials.reserve(scene->mNumMaterials);    
	for (unsigned i = 0; i < scene->mNumMaterials; ++i) { 
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) { 
			materials.push_back(App->texture->LoadTexture(file.data)); 
		} 
	} 
}