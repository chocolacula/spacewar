#pragma once

#include <vector>

#include "../../../Types/Color.h"
#include "../../System/Embedded/MeshRenderSystem.h"
#include "../Component.h"

struct Vector2;
struct Color4;
struct Transform;

class Mesh final : public Component
{
public:
	Mesh(Entity* entity);

	void SetColor(Color4 color);
	void SetTriangles(std::vector<Vector2>&& triangles);
	void SetLines(std::vector<Vector2>&& lines);

private:
	Color4 _color;
	std::vector<Vector2> _triangles;
	std::vector<Vector2> _lines;

	friend class MeshRenderSystem;
};