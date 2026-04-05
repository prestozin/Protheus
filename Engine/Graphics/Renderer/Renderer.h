#pragma once
#include <cstdint>


struct RendererInfo
{
    int width, height;
};





void InitRenderer(int width, int height);
void ShutdownRenderer();

RendererInfo GetRendererInfo();

void Clear(uint32_t color);

void SetPixel(int x, int y, uint32_t color);

uint32_t* GetFramebuffer();

void DrawLine(int x1, int y1, int x2, int y2, uint32_t color);

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);

void DrawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, uint32_t color);

float EdgeFunction(int Vec1X, int Vec1Y, int Vec2X, int Vec2Y, int Px, int Py);

void DrawFilledTriangle(Vertex v1, Vertex v2, Vertex v3);

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