#include "ModuleProgram.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "GL/glew.h"
#include "SDL.h"
#include "MathGeoLib/Math/float4x4.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleModel.h"
#include "Globals.h"

static void __stdcall OurOpenGLErrorFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	const char* tmp_source = "", * tmp_type = "", * tmp_severity = "";
	switch (source) {
	case GL_DEBUG_SOURCE_API: tmp_source = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: tmp_source = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: tmp_source = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: tmp_source = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION: tmp_source = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER: tmp_source = "Other"; break;
	};
	switch (type) {
	case GL_DEBUG_TYPE_ERROR: tmp_type = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: tmp_type = "Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: tmp_type = "Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY: tmp_type = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: tmp_type = "Performance"; break;
	case GL_DEBUG_TYPE_MARKER: tmp_type = "Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP: tmp_type = "Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP: tmp_type = "Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER: tmp_type = "Other"; break;
	};
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH: tmp_severity = "high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: tmp_severity = "medium"; break;
	case GL_DEBUG_SEVERITY_LOW: tmp_severity = "low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: tmp_severity = "notification"; break;
	};
	LOG("<Source:%s> <Type:%s> <Severity:%s> <ID:%d> <Message:%s>\n", tmp_source, tmp_type, tmp_severity, id, message);
}
ModuleRender::ModuleRender()
{
}
ModuleRender::~ModuleRender()
{
}
static unsigned CreateTriangleVBO()
{
	float vtx_data[] = { 
		-1.0f, -1.0f, 0.0f,	// <- v0 pos  
		0.0f, 0.0f,         // <- v0 texcoord

		1.0f, -1.0f, 0.0f,	// <- v1 pos  
		1.0f, 0.0f,         // <- v1 texcoord

		-1.0f,  1.0f, 0.0f,	// <- v2 pos  
		0.0f, 1.0f,         // <- v2 texcoord

		-1.0f,  1.0f, 0.0f,	// <- v2 pos  
		0.0f, 1.0f,         // <- v2 texcoord

		1.0f, -1.0f, 0.0f,	// <- v1 pos  
		1.0f, 0.0f,         // <- v1 texcoord 

		1.0f, 1.0f, 0.0f,	// <- v3 pos  
		1.0f, 1.0f          // <- v3 texcoord

	};
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return vbo;
}

bool ModuleRender::Start() {
	//lenna = App->texture->LoadTexture("./Assets/Models/lenna.png");
	App->model->Load("./Assets/Models/BakerHouse.fbx");
	//App->model->Load("./Assets/Models/enemy_low.fbx");
	return true;
}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired versi on
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	context = SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_TEXTURE_2D);

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(&OurOpenGLErrorFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
#endif

	return true;
}

void ModuleRender::RenderVBO(unsigned vbo, unsigned program) {

	float4x4 model = float4x4::identity;
	float4x4 view = App->camera->GetViewMatrix();
	float4x4 proj = App->camera->GetProjectionMatrix();

	App->debdraw->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);
	App->model->Draw();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex    
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &proj[0][0]);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lenna);
	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);
	// 1 triangle to draw = 3 vertices 
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
update_status ModuleRender::PreUpdate()
{
	GLsizei screen_width, screen_height;
	SDL_GetWindowSize(App->window->window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}


update_status ModuleRender::Update()
{
	float4x4 model = float4x4::identity;
	float4x4 view = App->camera->GetViewMatrix();
	float4x4 proj = App->camera->GetProjectionMatrix();

	App->debdraw->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);
	App->model->Draw();
	
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	return false;
}




static void DestroyVBO(unsigned vbo)
{
	glDeleteBuffers(1, &vbo);
}


