#pragma once

#include "UISelectableObject.hpp"

class UIButton : public UISelectableObject
{
public:
	UIButton(Engine::Mesh *mesh, Engine::Material *material): 
		UISelectableObject(mesh, material), Engine::RenderObject(mesh, material) {}
	~UIButton() {}
};