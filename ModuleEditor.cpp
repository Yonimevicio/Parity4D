#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_sdl.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include <string>
#include "SDL.h"

bool show_stats = false;
bool show_properties = false;
bool show_console = false;

ModuleEditor::ModuleEditor()
{
	cmd = new Console();
}
ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init() 
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	
	return true;
}

void ShowMainMenu() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Stats", "I")) {
				show_stats = !show_stats;
			}
			if (ImGui::MenuItem("Properties", "P")) {
				show_properties = !show_properties;
			}
			if (ImGui::MenuItem("Console", "P")) {
				show_console = !show_console;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About"))
		{
			ImGui::Text("Pairity6D");
			ImGui::Text("A powerful game development tool developed in Barcelona");
			ImGui::Text("The goal of this engine is to double unity3d in everything");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
void ShowStats() {
	if(ImGui::Begin("Stats")){
		char  buff[256] = {};
		if (ImGui::InputText("pruebas", buff, 256)) {

		}
		ImGui::End();
	}
}
void ShowProperties() 
{
	ImGui::Begin("Properties");

	if(ImGui::CollapsingHeader("Transformation"))
	{
		static ImVec4 size1(100.0f, 100.0f,100.0f, 100.0f);
		static ImVec4 size2(100.0f, 100.0f, 100.0f, 100.0f);
		static ImVec4 size3(100.0f, 100.0f, 100.0f, 100.0f);

		ImGui::DragFloat3("position", (float*)&size1, 0.5f, -200.0f, 200.0f, "%.3f");
		ImGui::DragFloat3("rotate", (float*)&size2, 0.5f, -180.0f, 180.0f, "%.3f");
		ImGui::DragFloat3("scale", (float*)&size3, 0.5f, -100.0f, 100.0f, "%.3f");
	}

	if (ImGui::CollapsingHeader("Geometry"))
	{
		static ImVec4 size1(100.0f, 100.0f, 100.0f, 100.0f);
		static ImVec4 size2(100.0f, 100.0f, 100.0f, 100.0f);
		static ImVec4 size3(100.0f, 100.0f, 100.0f, 100.0f);

		ImGui::DragFloat3("position", (float*)&size1, 0.5f, -200.0f, 200.0f, "%.3f");
		ImGui::DragFloat3("rotate", (float*)&size2, 0.5f, -180.0f, 180.0f, "%.3f");
		ImGui::DragFloat3("scale", (float*)&size3, 0.5f, -100.0f, 100.0f, "%.3f");
	}

	if (ImGui::CollapsingHeader("Texture"))
	{
		
	}

	ImGui::End();

}

update_status ModuleEditor::PreUpdate()
{
	return UPDATE_CONTINUE;
}
update_status ModuleEditor::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	//ImGui::ShowUserGuide();
	ShowMainMenu();
	if (show_stats) ShowStats();
	if (show_properties) ShowProperties();
	if (show_console) cmd->Draw("Terminal", p_open);
	
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	isMenuHovered = io.WantCaptureMouse || io.WantCaptureKeyboard;
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return UPDATE_CONTINUE;
}
update_status ModuleEditor::PostUpdate()
{
	ImGui::Render();
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}
