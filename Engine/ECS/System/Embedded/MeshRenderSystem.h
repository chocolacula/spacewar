#pragma once

#include "../ISystem.h"

class Mesh;
struct Transform;

class MeshRenderSystem final : ISystem
{
public:
	void Run() override;

private:
	void Render(const Mesh& mesh, const Transform& transform);
};
