#include <SDL.h>
//#include <glad/glad.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl.h>

#include <implot.h>

#include <thread>
#include <chrono>
#include <iostream>

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cerr << "error initializing sdl\n";
		return 1;
	}

	// Use OpenGL 3.3 core
	// TODO: use any?
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// hide main window :)
	auto* win = SDL_CreateWindow("RealTimeImPlot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
	if (!win) {
		std::cerr << "error opening window\n";
		return 1;
	}

	auto* gl_context = SDL_GL_CreateContext(win);
	if (!gl_context) {
		std::cerr << "error creating gl context\n";
		return 1;
	}

#if 0
	// only if you need direct opengl access
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "error loading gl (glad)\n";
		return 1;
	}
#endif

	if (SDL_GL_MakeCurrent(win, gl_context)) {
		std::cerr << "error making gl context current\n";
		return 1;
	}

	// setup imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplSDL2_InitForOpenGL(win, gl_context);
	ImGui_ImplOpenGL3_Init();

	// style
	{
		ImGui::StyleColorsDark();
		auto& style = ImGui::GetStyle();
		style.WindowRounding = 2.f;
	}

	// main loop
	bool run = true;
	while (run) {
		// process events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				run = false;
				break;
			} else {
				ImGui_ImplSDL2_ProcessEvent(&event);
			}
		}

		// imgui new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(win);
		ImGui::NewFrame();

		// ======== imgui guis go here ========

		ImGui::ShowDemoWindow(&run);

		// ======== render (end frame) ========
		ImGui::Render();

		// we dont use the main window :)
		//glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//SDL_GL_SwapWindow(win);

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000/144));
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}

