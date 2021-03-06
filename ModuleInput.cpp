#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"
#include "ModuleModel.h"
#include "IMGUI/imgui_impl_sdl.h"
ModuleInput::ModuleInput()
{
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * NUM_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}
update_status ModuleInput::PreUpdate()
{
	SDL_Event event;
	int mouse_x;
	int mouse_y;

	mouse_motion = { 0, 0 };
	mouse_wheel_motion = 0;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	mouse.x = mouse_x;
	mouse.y = mouse_y;
	mouse_motion.x = 0;
	mouse_motion.y = 0;

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < NUM_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if (mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			return UPDATE_STOP;
		case SDL_DROPFILE:
			//App->model->CleanUp();
			App->model->Load(event.drop.file);

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				App->camera->WindowResized(event.window.data1, event.window.data2);
				break;
			}
			break;

		case SDL_MOUSEMOTION:
			mouse_motion.x += event.motion.xrel;
			mouse_motion.y += event.motion.yrel;
			break;

		case SDL_MOUSEWHEEL:
			if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
			{
				mouse_wheel_motion = event.wheel.x;
			}
			else
			{
				mouse_wheel_motion = event.wheel.y;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[event.button.button - 1] = KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[event.button.button - 1] = KEY_UP;
			break;
		}
	}

	if (GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleInput::Update()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Exit SDL input");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
