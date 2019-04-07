#pragma once

#include <Mesh.hpp>
#include <Material.hpp>
#include "UIObject.hpp"
#include "PickableObject.hpp"

class UISelectableObject: public UIObject, public PickableObject
{
public:
	UISelectableObject(Engine::Mesh *mesh, Engine::Material *material): 
		UIObject(mesh, material), PickableObject(mesh, material), Engine::RenderObject(mesh, material) {}
	~UISelectableObject() {}
};
