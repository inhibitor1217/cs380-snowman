#include "UIToggler.hpp"

void UIToggler::onClick()
{
	_selected = !_selected;
	std::cout << "Toggler onClick: " << _index << std::endl;
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