#include "UIButton.hpp"

void UIButton::onPress()
{
	_pressed = true;
}

void UIButton::onRelease()
{
	_pressed = false;
}

void UIButton::onEnter()
{
	_hover = true;
}

void UIButton::onExit()
{
	_hover = false;
}

void UIButton::onClick()
{
	std::cout << "Button onClick: " << _index << std::endl;
}

glm::vec3 UIButton::GetRenderColor()
{
	if (_pressed)
		return _pressed_color;
	if (_hover)
		return _hover_color;
	return _color;
}