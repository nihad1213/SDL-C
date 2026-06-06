#include <SDL3/SDL.h>

int main() {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed!");
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Hello World", 800, 600, 
        SDL_WINDOW_RESIZABLE);

    SDL_Delay(50000);
    SDL_Quit();

    return 0;
}