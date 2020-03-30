#include "MeshRenderSystem.h"

#include <wtypes.h>
#include <GL/gl.h>

#include "../../../Scene.h"
#include "../../Component/Embedded/Mesh.h"
#include "../../Entity/Entity.h"
#include "../../../Math.h"
#include "../../../Types/Color.h"

void MeshRenderSystem::Run()
{
	auto meshes = Scene::GetComponentManager().FindAllComponents<Mesh>();

	Mesh* mesh = nullptr;

	while (meshes.Next(mesh))
	{
		if (mesh->enabled)
			Render(*mesh, mesh->GetEntity()->transform);
	}
}

void MeshRenderSystem::Render(const Mesh& mesh, const Transform& transform)
{
	glLoadIdentity();
	glTranslatef(transform.position.x, transform.position.y, 0.f);
	glRotatef(Math::RadToDegree(transform.angle), 0.f, 0.f, 1.f);

	glRotatef(-90.f, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	glColor3f(mesh._color.red, mesh._color.green, mesh._color.blue);

	for (auto&& triangle : mesh._triangles)
	{
		glVertex2f(triangle.x, triangle.y);
	}

	glEnd();

	glLineWidth(2.f);
	glBegin(GL_LINE_LOOP);
	glColor3f(mesh._color.red, mesh._color.green, mesh._color.blue);

	for (auto&& line : mesh._lines)
	{
		glVertex2f(line.x, line.y);
	}

	glEnd();

	
}