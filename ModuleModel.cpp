#include "ModuleModel.h"
#include "Application.h"
#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "ModuleTexture.h"
#include "MathGeoLib/Geometry/Sphere.h"

void myCallback(const char* msg, char* userData) {
	if (msg) LOG("Assimp Message: %s", msg);
}
ModuleModel::ModuleModel(){
	struct aiLogStream stream;
	stream.callback = myCallback;
	aiAttachLogStream(&stream);
}

void ModuleModel::Load(const char* file_path) {

	std::string filepath = file_path;
	std::string ext = filepath.substr(filepath.find_last_of(".")+1);
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (ext == "fbx" || ext == "FBX"){
		CleanUp();
		LoadMaterials(scene, file_path);
		LoadMeshes(scene);
		first_texture_source = file_path;
	}else if (ext == "png" || ext == "PNG" || ext == "jpg" || ext == "JPG" || ext == "dds" || ext == "DDS") {
		CleanUpOnlyTextures();
		materials.push_back(App->texture->LoadTexture(file_path, file_path));
		first_texture_source = file_path;
	}
	else {
		LOG("Error loading %s: %s", file_path, aiGetErrorString());
	}

}
void ModuleModel::LoadMaterials(const aiScene* scene, const char* file_path) {
	aiString file;    
	materials.reserve(scene->mNumMaterials);    
	for (unsigned i = 0; i < scene->mNumMaterials; ++i) { 
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) { 
			materials.push_back(App->texture->LoadTexture(file.data, file_path)); 
		}
	} 
}
void ModuleModel::LoadMeshes(const aiScene* scene) {
	aiString file;
	num_vertices = 0;
	std::vector<vec> vertices;

	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		ModuleMesh mesh;
		mesh.Load(scene->mMeshes[i]);
		meshes.push_back(mesh);
		num_vertices += scene->mMeshes[i]->mNumVertices;
		for (int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
		{
			const aiVector3D& ai_vertex = scene->mMeshes[i]->mVertices[j];
			vertices.push_back(vec(ai_vertex.x, ai_vertex.y, ai_vertex.z));
		}
	}
	min_sphere = Sphere::OptimalEnclosingSphere(vertices.data(), vertices.size());
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
bool ModuleModel::CleanUpOnlyTextures() {
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