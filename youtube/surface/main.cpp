#include <SDL3/SDL.h>
#include <string>

struct SDLApplication {
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    SDL_Texture* mTexture = nullptr;
    bool mRunning = true;

    SDLApplication(const char* title) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("SDL_Init failed: %s", SDL_GetError());
            return;
        }

        mWindow = SDL_CreateWindow(
            title,
            800,
            600,
            SDL_WINDOW_RESIZABLE
        );

        if (!mWindow) {
            SDL_Log("Window creation failed: %s", SDL_GetError());
            return;
        }

        mRenderer = SDL_CreateRenderer(mWindow, nullptr);

        if (!mRenderer) {
            SDL_Log("Renderer creation failed: %s", SDL_GetError());
            return;
        }

        SDL_Surface* surface = SDL_LoadBMP("test.bmp");

        if (!surface) {
            SDL_Log("Failed to load test.bmp: %s", SDL_GetError());
            return;
        }

        mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
        SDL_DestroySurface(surface);

        if (!mTexture) {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
        }
    }

    ~SDLApplication() {
        if (mTexture)
            SDL_DestroyTexture(mTexture);

        if (mRenderer)
            SDL_DestroyRenderer(mRenderer);

        if (mWindow)
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
    }

    void Render() {
        SDL_RenderClear(mRenderer);

        if (mTexture) {
            SDL_RenderTexture(
                mRenderer,
                mTexture,
                nullptr,
                nullptr 
            );
        }

        SDL_RenderPresent(mRenderer);
    }

    void MainLoop() {
        Uint64 fps = 0;
        Uint64 lastTime = SDL_GetTicks();

        while (mRunning) {
            Uint64 currentTick = SDL_GetTicks();

            Tick();

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