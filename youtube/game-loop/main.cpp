#include <SDL3/SDL.h>

struct SDLApplication {
    SDL_Window* mWindow;
    bool mRunning = true;

    SDLApplication(const char* title) {
        SDL_Init(SDL_INIT_VIDEO);
        mWindow = SDL_CreateWindow(title, 320, 240, SDL_WINDOW_RESIZABLE);
    }

    ~SDLApplication() {
        SDL_Quit();
    }

    void Tick() {
        Input();
        Update();
        Render();
    }

    void Input() {

    }

    void Update() {

    }

    void Render() [
        
    ]
};

int main() {
    
    return 0;
}