#pragma once

#include "UISelectableObject.hpp"

class UIButton : public UISelectableObject
{
private:
	bool _pressed = false;
	bool _hover = false;

public:
	UIButton(Engine::Mesh *mesh, Engine::Material *material): 
		UISelectableObject(mesh, material), Engine::RenderObject(mesh, material) {}
	~UIButton() {}

	void onPress() override;
	void onRelease() override;
	void onClick() override;
	void onEnter() override;
	void onExit() override;
};