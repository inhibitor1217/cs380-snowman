#pragma once

#include "UISelectableObject.hpp"

class UIToggler : public UISelectableObject
{
private:
	glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 _selected_color = glm::vec3(0.3f, 0.3f, 0.3f);
	glm::vec3 _pressed_color = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 _hover_color = glm::vec3(0.6f, 0.6f, 0.6f);

	bool _selected = false;
public:
	UIToggler(Engine::Mesh *mesh, Engine::Material *material) :
		UISelectableObject(mesh, material), Engine::RenderObject(mesh, material) {}
	~UIToggler() {}

	void onClick() override;

	void SetColor(glm::vec3 color) { _color = color; }
	void SetSelectedColor(glm::vec3 color) { _selected_color = color; }
	void SetPressedColor(glm::vec3 color) { _pressed_color = color; }
	void SetHoverColor(glm::vec3 color) { _hover_color = color; }
	void SetSelected(bool selected) { _selected = selected; }

	glm::vec3 GetColor() { return _color; }
	glm::vec3 GetSelectedColor() { return _selected_color; }
	glm::vec3 GetPressedColor() { return _pressed_color; }
	glm::vec3 GetHoverColor() { return _hover_color; }
	bool GetSelected() { return _selected; }

	glm::vec3 GetRenderColor();
};