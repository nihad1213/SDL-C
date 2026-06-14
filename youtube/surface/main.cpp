#include <SDL3/SDL.h>
#include <string>

struct SDLApplication {
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    bool mRunning = true;

    SDLApplication(const char* title) {
        SDL_Init(SDL_INIT_VIDEO);

        mWindow = SDL_CreateWindow(
            title,
            800,
            600,
            SDL_WINDOW_RESIZABLE
        );

        mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    }

    ~SDLApplication() {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Tick() {
        Input();
        Update();
        Render();
    }

    void Input() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                mRunning = false;
            }
        }
    }

    void Update() {
        // Game logic goes here
    }

    void Render() {
        SDL_SetRenderDrawColor(mRenderer, 30, 30, 30, 255);

        SDL_RenderClear(mRenderer);

        // Draw a rectangle
        SDL_FRect rect = {
            300.0f,
            200.0f,
            200.0f,
            100.0f
        };

        SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
        SDL_RenderFillRect(mRenderer, &rect);

        SDL_RenderPresent(mRenderer);
    }

    void MainLoop() {
        Uint64 fps = 0;
        Uint64 lastTime = SDL_GetTicks();
        while (mRunning) {
            Uint64 currentTick = SDL_GetTicks();

            Tick();
            SDL_Delay(60);
            fps++;

            if (currentTick - lastTime >= 1000) {
                std::string title = "FPS: " + std::to_string(fps);
                SDL_SetWindowTitle(mWindow, title.c_str());

                fps = 0;
                lastTime = currentTick;
            }
        }
    }
};

int main() {
    SDLApplication app("SDL3 Window");
    app.MainLoop();
    return 0;
}