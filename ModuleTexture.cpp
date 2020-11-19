#include "ModuleTexture.h"
#include "Devil/include/il.h"
#include "GL/glew.h"

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

unsigned int ModuleTexture::LoadTexture(const std::string path) {

	if (textureMap[path] != NULL) return textureMap[path];

	unsigned int image_id; 
	unsigned int texture_id;
	ilGenImages(1, &image_id);
	ilBindImage(image_id);
	texture_is_load = ilLoadImage(path.c_str());
	
	if (texture_is_load) {
		texture_is_load = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (!texture_is_load) return false;
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
	}
	else return false;

	return texture_id;
}
bool ModuleTexture::Init()
{
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	return true;
}

update_status ModuleTexture::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp(unsigned int texture)
{
	glDeleteTextures(1, &texture);
	std::map<std::string,unsigned int>::iterator it;
	for (it = textureMap.begin(); it != textureMap.end(); it++) 
	{
		if (it->second == texture) {
			textureMap.erase(it);
			break;
		}
	}
	return true;
}
