#include "Mesh.h"

#include "Math/Projection/Projection.h"


void Mesh::Draw(const RendererInfo& info)
{
	std::vector<Vector2D> projectedVertices(vertices.size());

	for (size_t i = 0; i < vertices.size(); ++i)
	{
		projectedVertices[i] =  Project(vertices[i].Position, info.width, info.height);
	}
}
