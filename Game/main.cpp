#include "Graphics/Renderer/Renderer.h"
#include "Math/Projection/Projection.h"
#include "SDL3/SDL.h"


int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    InitRenderer(800, 600); 

    SDL_Window* window = SDL_CreateWindow("Protheus", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800,600);



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

        Vector3D cube[8] =
        {
            {-1, -1, 3},
            { 1, -1, 3},
            { 1,  1, 3},
            {-1,  1, 3},

            {-1, -1, 5},
            { 1, -1, 5},
            { 1,  1, 5},
            {-1,  1, 5}
        };

        int edges[12][2] =
        {
            {0,1}, {1,2}, {2,3}, {3,0}, // frente
            {4,5}, {5,6}, {6,7}, {7,4}, // trás
            {0,4}, {1,5}, {2,6}, {3,7}  // liga frente ↔ trás
        };

        Vector2D projected[8];

        for (int i = 0; i < 8; i++)
        {
            projected[i] = Project(cube[i], info.width, info.height);
        }

        for (int i = 0; i < 12; i++)
        {
            int a = edges[i][0];
            int b = edges[i][1];

            DrawLine(
                (int)projected[a].x, (int)projected[a].y,
                (int)projected[b].x, (int)projected[b].y,
                0xFFFFFFFF
            );
        }

        SDL_UpdateTexture(texture, NULL, GetFramebuffer(), 800 * sizeof(uint32_t));

        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    ShutdownRenderer();

    return 0;
}