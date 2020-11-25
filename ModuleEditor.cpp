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
bool show_drag_and_drop = false;

ModuleEditor::ModuleEditor()
{
}
ModuleEditor::~ModuleEditor()
{
}

void ModuleEditor::DragAndDrop() 
{
		SDL_PollEvent(&event);
			switch (event.type) {
			case (SDL_DROPFILE): {      // In case if dropped file
				dropped_file = event.drop.file;
				// Shows directory of dropped file
				SDL_ShowSimpleMessageBox(
					SDL_MESSAGEBOX_INFORMATION,
					"File dropped on window",
					dropped_file,
					App->window->window
				);
				SDL_free(dropped_file);    // Free dropped_filedir memory
				break;
		}
	}

}

bool ModuleEditor::Init() 
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init();
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	return true;
}

void ShowMainMenu() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Drag model", "m")) {
				show_drag_and_drop = !show_drag_and_drop;
			}

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
void ShowDragAndDrop() {
	ImGui::Begin("Drag and drop");
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))	// we use an external source (i.e. not ImGui-created)
	{
		// replace "FILES" with whatever identifier you want - possibly dependant upon what type of files are being dragged
		// you can specify a payload here with parameter 2 and the sizeof(parameter) for parameter 3.
		// I store the payload within a vector of strings within the application itself so don't need it.
		ImGui::SetDragDropPayload("FBX", nullptr, 0);
		ImGui::BeginTooltip();
		ImGui::Text("FILES");
		ImGui::EndTooltip();
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FBX"))
		{
			int a = payload->DataSize;
		}
		// Set payload to carry the index of our item (could be anything)

		//ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));

		// Display preview (could be anything, e.g. when dragging an image we could decide to display
		// the filename and a small preview of the image, etc.)

		ImGui::EndDragDropTarget();
	}
	ImGui::End();
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

update_status ModuleEditor::PreUpdate()
{
	return UPDATE_CONTINUE;
}
update_status ModuleEditor::Update()
{
	DragAndDrop();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	//ImGui::ShowUserGuide();
	ShowMainMenu();
	if (show_stats) ShowStats();
	if (show_properties) ShowProperties();
	if (show_drag_and_drop) ShowDragAndDrop();

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
