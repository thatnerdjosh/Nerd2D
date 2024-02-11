#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cout << "Error SDL2 Initialization : " << SDL_GetError();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "Error window creation";
        return 3;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Error renderer creation";
        return 4;
    }

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Initialize the previous and current time
    Uint32 previousTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = 0;

    bool show_demo_window = true;

    while (true) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui::NewFrame();
        if(show_demo_window) {
            ImGui::ShowDemoWindow();
        }

        // Update current time and calculate delta time
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - previousTime) / 1000.0f; // Convert milliseconds to seconds
        // Use deltaTime here for any time-based updates, e.g., movement, animations
        // Example: position += speed * deltaTime;

        // Update previous time for the next frame
        previousTime = currentTime;

        ImGui::Render();
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
        SDL_Delay(16.667);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}
