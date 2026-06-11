#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
// #include <stdio.h>
// #include <stdbool.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "SDL3 Input Test (Scancode + Keys)",
        800, 600,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {

        // IMPORTANT: update event state
        SDL_PumpEvents();

        // keyboard state (for holding keys)
        const bool* keys = SDL_GetKeyboardState(NULL);

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            // KEY DOWN TEST
            else if (event.type == SDL_EVENT_KEY_DOWN) {

                SDL_Log("KEY DOWN -> key=%s | scancode=%s",
                    SDL_GetKeyName(event.key.key),
                    SDL_GetScancodeName(event.key.scancode)
                );

                // special test cases
                if (event.key.scancode == SDL_SCANCODE_SPACE) {
                    SDL_Log("SPACE pressed!");
                }
            }

            // KEY UP TEST
            else if (event.type == SDL_EVENT_KEY_UP) {
                SDL_Log("KEY UP -> scancode=%s",
                    SDL_GetScancodeName(event.key.scancode)
                );
            }
        }

        // HOLD TEST (real-time input)
        if (keys[SDL_SCANCODE_W]) SDL_Log("Holding W");
        if (keys[SDL_SCANCODE_A]) SDL_Log("Holding A");
        if (keys[SDL_SCANCODE_S]) SDL_Log("Holding S");
        if (keys[SDL_SCANCODE_D]) SDL_Log("Holding D");

        // render loop (empty visual)
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}