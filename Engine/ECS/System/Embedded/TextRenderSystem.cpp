#include "TextRenderSystem.h"

#include <GLFW/glfw3.h>

#include "../../../Scene.h"
#include "../../Component/Embedded/Text.h"
#include "../../Entity/Entity.h"

void TextRenderSystem::Run()
{
	auto texts = Scene::GetComponentManager().FindAllComponents<Text>();

	Text* text = nullptr;

	while (texts.Next(text))
	{
		if (!text->enabled)
			continue;
		
		const auto transform = text->GetEntity()->transform;

		glLoadIdentity();
		glRasterPos2d(transform.position.x, transform.position.y);
		glColor3f(text->color.red, text->color.green, text->color.blue);
		glCallLists((int)text->value.size(), GL_UNSIGNED_BYTE, text->value.c_str());
	}
}
