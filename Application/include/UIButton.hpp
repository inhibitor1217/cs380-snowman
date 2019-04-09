#pragma once

#include "UISelectableObject.hpp"

class UIButton : public UISelectableObject
{
private:
	bool _pressed = false;
	bool _hover = false;

	glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 _pressed_color = glm::vec3(0.6f, 0.6f, 0.6f);
	glm::vec3 _hover_color = glm::vec3(0.8f, 0.8f, 0.8f);

public:
	UIButton(Engine::Mesh *mesh, Engine::Material *material): 
		UISelectableObject(mesh, material), Engine::RenderObject(mesh, material) {}
	~UIButton() {}

	void onPress() override;
	void onRelease() override;
	void onClick() override;
	void onEnter() override;
	void onExit() override;

	void SetColor(glm::vec3 color) { _color = color; }
	void SetPressedColor(glm::vec3 color) { _pressed_color = color; }
	void SetHoverColor(glm::vec3 color) { _hover_color = color; }

	glm::vec3 GetColor() { return _color; }
	glm::vec3 GetPressedColor() { return _pressed_color; }
	glm::vec3 GetHoverColor() { return _hover_color; }

	glm::vec3 GetRenderColor();
};