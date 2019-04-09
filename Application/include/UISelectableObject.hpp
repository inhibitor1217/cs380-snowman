#pragma once

#include <Mesh.hpp>
#include <Material.hpp>
#include "UIObject.hpp"
#include "PickableObject.hpp"

class UISelectableObject: public UIObject, public PickableObject
{
protected:
	bool _pressed = false;
	bool _hover = false;

public:
	UISelectableObject(Engine::Mesh *mesh, Engine::Material *material): 
		UIObject(mesh, material), PickableObject(mesh, material), Engine::RenderObject(mesh, material) {}
	~UISelectableObject() {}

	void onPress() override;
	void onRelease() override;
	void onEnter() override;
	void onExit() override;
};
