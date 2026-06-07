#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>



int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Detect Key Press", 800, 600, SDL_WINDOW_RESIZABLE);

    SDL_Event event;

    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                break; 
            }
        }
    }

    SDL_Quit();

    return 0;
}