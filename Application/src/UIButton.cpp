#include "UIButton.hpp"

void UIButton::onPress()
{
	std::cout << "Button onPress: " << _index << std::endl;
	_pressed = true;
}

void UIButton::onRelease()
{
	std::cout << "Button onRelease: " << _index << std::endl;
	_pressed = false;
}

void UIButton::onEnter()
{
	std::cout << "Button onEnter: " << _index << std::endl;
	_hover = true;
}

void UIButton::onExit()
{
	std::cout << "Button onExit: " << _index << std::endl;
	_hover = false;
}

void UIButton::onClick()
{
	std::cout << "Button onClick: " << _index << std::endl;
}