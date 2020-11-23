#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_sdl.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderExercise.h"

bool show_stats = false;
bool show_properties = false;

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init() 
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer_ex->context);
	ImGui_ImplOpenGL3_Init();
	return true;
}

update_status ModuleEditor::PreUpdate()
{
	return UPDATE_CONTINUE;
}

void ShowMainMenu() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Stats", "I")) {
				show_stats = !show_stats;
			}
			if (ImGui::MenuItem("Properties", "P")) {
				show_properties = !show_properties;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
void ShowStats() {
	ImGui::Begin("Stats");
	
	ImGui::End();
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
