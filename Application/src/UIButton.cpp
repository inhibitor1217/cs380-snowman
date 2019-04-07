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