#include "Graphics/Renderer/Renderer.h"
#include "Math/Projection/Projection.h"
#include <Math/Transform/Transform.h>
#include "SDL3/SDL.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    InitRenderer(800, 600); 

    SDL_Window* window = SDL_CreateWindow("Protheus", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800,600);

    float deltaTime = 0.016f;
    float angle = 0.0f;
    bool running = true;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }


        Clear(0xFF000000);


		RendererInfo info = GetRendererInfo();

		DrawCircle(128, 100, { 400, 300 });

        SDL_UpdateTexture(texture, NULL, GetFramebuffer(), 800 * sizeof(uint32_t));

        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    ShutdownRenderer();

    return 0;
}