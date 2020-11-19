#pragma once
#include "Module.h"
#include <vector>

struct aiMesh;
class ModuleMesh : public Module
{
public:
	void Load(const aiMesh* mesh);
	void Draw(const std::vector<unsigned int>& materials) const;
	bool CleanUp();

public:
	unsigned vao = 0;
	unsigned vbo = 0;
	unsigned ebo = 0;

	unsigned num_vertices = 0;
	unsigned num_index = 0;
	unsigned material_index = 0;

};

