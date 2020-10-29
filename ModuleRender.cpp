#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);  // depth buffer 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); //stencil buffer 8 bits

	SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();

	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Depth test
	glEnable(GL_CULL_FACE);  //	Cull backward faces
	glFrontFace(GL_CCW);     //	Will be counter clockwise

	return true;
}

update_status ModuleRender::PreUpdate()
{
	int screen_width, screen_height;
	SDL_GetWindowSize(App->window->window, &screen_width, &screen_height);

	glClearColor(0.1f, 0.5f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");
	SDL_GL_DeleteContext(App->window->window);
	//Destroy window

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
}

