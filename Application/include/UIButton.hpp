#pragma once

#include "UISelectableObject.hpp"

class UIButton : public UISelectableObject
{
private:
	glm::vec3 _pressed_color = glm::vec3(0.6f, 0.6f, 0.6f);
	glm::vec3 _hover_color = glm::vec3(0.8f, 0.8f, 0.8f);

public:
	UIButton(Engine::Mesh *mesh, Engine::Material *material): 
		UISelectableObject(mesh, material), Engine::RenderObject(mesh, material) {}
	~UIButton() {}

	void onClick() override;

	void SetPressedColor(glm::vec3 color) { _pressed_color = color; }
	void SetHoverColor(glm::vec3 color) { _hover_color = color; }

	glm::vec3 GetPressedColor() { return _pressed_color; }
	glm::vec3 GetHoverColor() { return _hover_color; }

	glm::vec3 GetRenderColor() override;
};