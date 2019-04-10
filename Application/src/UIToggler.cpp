#include "UIToggler.hpp"

void UIToggler::onClick()
{
	_selected = !_selected;
}

glm::vec3 UIToggler::GetRenderColor()
{
	if (_pressed)
		return _pressed_color;
	if (_hover)
		return _hover_color;
	if (_selected)
		return _selected_color;
	return _color;
}