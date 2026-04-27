#pragma once

#include <vector>
#include <array>

#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Vertex/Vertex.h"



struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<std::array<int, 2>> edges;

	void Draw(const RendererInfo& info);
};