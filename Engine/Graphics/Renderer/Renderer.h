#pragma once
#include "Graphics/Vertex/Vertex.h"
#include "Math/Vectors/Vector2D.h"
#include <cstdint>


struct RendererInfo
{
    int width, height;
};


void InitRenderer(int width, int height);
void ShutdownRenderer();

RendererInfo GetRendererInfo();

void Clear(uint32_t color);

void SetPixel(Vector2D position, uint32_t color);

uint32_t* GetFramebuffer();

void DrawLine(Vector2D Vertice1, Vector2D Vertice2, uint32_t color);

void DrawFilledTriangle(Vertex v1, Vertex v2, Vertex v3);

void DrawCircle(uint32_t vertices, float radius, Vector2D center);

inline float Clamp(float value)
{
    if (value < 0) return 0;
    if (value > 1) return 1;
    return value;
}

inline Color ToColor(uint32_t c)
{
    Color result;
    result.r = ((c >> 16) & 0xFF) / 255.0f;
    result.g = ((c >> 8) & 0xFF) / 255.0f;
    result.b = (c & 0xFF) / 255.0f;
    return result;
}

inline uint32_t ToUint32(Color c)
{
    uint8_t r = (uint8_t)(Clamp(c.r) * 255.0f);
    uint8_t g = (uint8_t)(Clamp(c.g) * 255.0f);
    uint8_t b = (uint8_t)(Clamp(c.b) * 255.0f);

    return (255 << 24) | (r << 16) | (g << 8) | b;
}