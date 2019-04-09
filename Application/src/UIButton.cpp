#include "UIButton.hpp"

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