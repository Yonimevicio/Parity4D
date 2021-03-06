#pragma once
#include "Module.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include "ModuleModel.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(int width, int height);

	void SetFOV(float h_fov);
	void SetAspectRatio(float aspect_ratio);
	void SetPlaneDistances(float near_plane, float far_plane);
	void SetPosition(float x, float y, float z);
	void SetPosition(vec vec3);
	void SetOrientation(float x, float y, float z);
	void Translate(vec translation);
	void Rotate(float3x3 rotationMatrix);
	void LookAt(float x, float y, float z);
	void Focus(ModuleModel* model);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();

private:
	Frustum frustum;
	float movement_speed = 4.0f;
	float rotation_speed = 90.0f;
};