#include "renderer.hpp"
#include "SDL3/SDL.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    InitRenderer(800, 600); 

    SDL_Window* window = SDL_CreateWindow("Protheus", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800,600);

    Vertex v1 = { {100,100}, {1,0,0} }; // red
    Vertex v2 = { {400,100}, {0,1,0} }; // green
    Vertex v3 = { {250,400}, {0,0,1} }; // blue



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

        DrawFilledTriangle(v1, v2, v3);

        SDL_UpdateTexture(texture, NULL, GetFramebuffer(), 800 * sizeof(uint32_t));

        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    ShutdownRenderer();

    return 0;
}