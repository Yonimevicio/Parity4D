#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_sdl.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
bool ModuleEditor::Init() 
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();
	return true;
}
bool ModuleEditor::CleanUp() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}
update_status ModuleEditor::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
	//ImGui_ImplSDL2_ProcessEvent(&event);
	
	ImGui::NewFrame();
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	ImGui::Render();
	return UPDATE_CONTINUE;
}

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}