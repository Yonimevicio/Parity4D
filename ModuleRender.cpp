#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "MathGeoLib/Geometry/Frustum.h"
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
	glViewport(0, 0, screen_width, screen_height);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	glLineWidth(1.0f); 
	float d = 200.0f;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES); 
	for (float i = -d; i <= d; i += 1.0f) { 
		glVertex3f(i, 0.0f, -d); 
		glVertex3f(i, 0.0f, d); 
		glVertex3f(-d, 0.0f, i); 
		glVertex3f(d, 0.0f, i); }
	glEnd();
	glLineWidth(2.0f); 
	glBegin(GL_LINES);
	// red X
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); 
	glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); 
	glVertex3f(1.0f, -0.1f, 0.0f);
	// green Y
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); 
	glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); 
	glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); 
	glVertex3f(0.0f, 1.05f, 0.0f);
	// blue Z
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); 
	glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); 
	glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); 
	glVertex3f(0.05f, -0.1f, 1.05f);
	glEnd();
	glLineWidth(1.0f);

	Frustum frustum; 
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded); 
	frustum.SetViewPlaneDistances(0.1f, 200.0f); 
	frustum.SetHorizontalFovAndAspectRatio(0.01745 * 90.0f, 1.3f);
	frustum.SetPos(float3(0, 1, -2)); 
	frustum.SetFront(float3::unitZ); 
	frustum.SetUp(float3::unitY); 
	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed();
	float4x4 view = frustum.ViewMatrix();
	view.Transpose();
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*projectionGL.v);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*view.v);

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

