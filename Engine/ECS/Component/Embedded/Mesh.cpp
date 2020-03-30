#include "Mesh.h"

#include "../../../Types/Color.h"
#include "../../../Types/Vector2.h"

Mesh::Mesh(Entity* entity) :
	Component(entity),
	_color(Color4::LIGHT_BLUE),
	_triangles({}),
	_lines({})
{}

void Mesh::SetColor(Color4 color)
{
	_color = color;
}

void Mesh::SetTriangles(std::vector<Vector2>&& triangles)
{
	_triangles = triangles;
}

void Mesh::SetLines(std::vector<Vector2>&& lines)
{
	_lines = lines;
}