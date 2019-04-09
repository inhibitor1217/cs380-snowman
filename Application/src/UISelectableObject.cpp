#include "UISelectableObject.hpp"

void UISelectableObject::onPress()
{
	_pressed = true;
}

void UISelectableObject::onRelease()
{
	_pressed = false;
}

void UISelectableObject::onEnter()
{
	_hover = true;
}

void UISelectableObject::onExit()
{
	_hover = false;
}