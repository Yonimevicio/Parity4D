#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_sdl.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModuleTexture.h"
#include "SDL.h"
#include "GL/glew.h"
bool show_stats = false;
bool show_properties = false;
bool show_console = false;
bool show_viewport = false;
ImVec4 orange = ImVec4(1.00, 0.65, 0.00, 1.0f);
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
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	
	return true;
}
std::string GetCaps() {
	std::string caps = "";
	if (SDL_Has3DNow) caps += "3D, ";
	if (SDL_HasAVX) caps += "AVX, ";
	if (SDL_HasAVX2) caps += "AVX2, ";
	if (SDL_HasAltiVec) caps += "AltiVec, ";
	if (SDL_HasMMX) caps += "MMX, ";
	if (SDL_HasRDTSC) caps += "RDTSC, ";
	if (SDL_HasSSE) caps += "SSE, ";
	if (SDL_HasSSE2) caps += "SSE2, ";
	if (SDL_HasSSE3) caps += "SSE3, ";
	if (SDL_HasSSE41) caps += "SSE41, ";
	if (SDL_HasSSE42) caps += "SSE42, ";
	if (caps.length() > 1) caps = caps.substr(0, caps.length() - 2);
	return caps;
}
void ShowMainMenu() {
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("ViewPort", NULL, &show_viewport)) {}
			if (ImGui::MenuItem("Stats", NULL, &show_stats)) {}
			if (ImGui::MenuItem("Properties", NULL, &show_properties)) {}
			if (ImGui::MenuItem("Console", NULL, &show_console)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About"))
		{
			ImGui::Text("Pairity6D");
			ImGui::Text("A powerful game development tool developed in Barcelona");
			ImGui::Text("Author: Cristian Ferrer Galan");
			ImGui::Text("The goal of this engine is to double unity3d in everything");
			ImGui::Text("");
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}
void ShowMainWindow(int width, int height) {
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	if (ImGui::Begin("Main Window", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | 
		ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
		ImGui::SetWindowSize(ImVec2(width, height));
		ShowMainMenu();
		static ImGuiID dockspaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(width-10, height-30), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);
	}
	ImGui::End();
}
void ShowStats() {

	if(ImGui::Begin("Stats")){
		if (ImGui::CollapsingHeader("Hardware"))
		{
			SDL_version sdlv; 
			SDL_GetVersion(&sdlv);
			ImGui::Text("SDL version: "); ImGui::SameLine();
			ImGui::TextColored(orange, "%d.%d.%d", sdlv.major, sdlv.minor, sdlv.patch);
			ImGui::Separator();

			ImGui::Text("CPUs: "); ImGui::SameLine();
			ImGui::TextColored(orange,"%d (Cache %d kb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
			ImGui::Text("System ram: "); ImGui::SameLine();
			ImGui::TextColored(orange, "%.1f Gb", SDL_GetSystemRAM() / 1024.0);
			ImGui::Text("Caps: "); ImGui::SameLine();
			ImGui::TextColored(orange, "% s", GetCaps().c_str());
			ImGui::Separator();

			ImGui::Text("GPU: "); ImGui::SameLine();
			ImGui::TextColored(orange, "%s", glGetString(GL_VENDOR));
			ImGui::Text("Brand: "); ImGui::SameLine();
			ImGui::TextColored(orange, "%s", glGetString(GL_RENDERER));
		}
	}
	ImGui::End();
}
void ShowViewport() {
	if (ImGui::Begin("Viewport",0)) { 
		App->editor->SetViewPortFocus(ImGui::IsWindowFocused());
		static ImVec2 win_size = ImGui::GetWindowSize();
		App->renderer->RenderViewport(win_size.x, win_size.y);
		ImGui::GetWindowDrawList()->AddImage(
			(void*)(intptr_t)App->renderer->GetTexture(),
			ImGui::GetCursorScreenPos(),
			ImVec2(ImGui::GetCursorScreenPos().x + win_size.x, 
				   ImGui::GetCursorScreenPos().y + win_size.y),
			ImVec2(0,1), ImVec2(1,0)
		);
		ImVec2 win_size2 = ImGui::GetWindowSize();
		if (win_size2.x != win_size.x || win_size2.y != win_size.y) {
			App->camera->WindowResized(win_size2.x, win_size2.y);
			win_size = ImGui::GetWindowSize();
		}
	}
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

	if (ImGui::CollapsingHeader("Texture")) {
		ImGui::Text("Texture: ");
		std::string text_src = App->texture->GetFirstTextureSource(); ImGui::SameLine();
		ImGui::TextColored(orange, "%s", text_src.c_str());
		ImGui::Image((void*)(intptr_t)App->texture->GetFirstTexture(), ImVec2(256, 256));
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
	int w = App->window->screen_surface->w;
	int h = App->window->screen_surface->h;
	ShowMainWindow(w,h);
	//ImGui::ShowDemoWindow();
	if (show_stats) ShowStats();
	if (show_properties) ShowProperties();
	if (show_console) cmd->Draw("Terminal", 0);
	if (show_viewport) ShowViewport();

	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	is_menu_hovered = io.WantCaptureMouse || io.WantCaptureKeyboard;
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
