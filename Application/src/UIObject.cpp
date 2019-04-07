#include "UIObject.hpp"

extern bool uiRootObjectInitialized;
extern Engine::RenderObject *g_UIRootObject;

UIObject::UIObject(Engine::Mesh *mesh, Engine::Material *material) : Engine::RenderObject(mesh, material)
{
	if (!uiRootObjectInitialized)
		throw std::exception();
	AddParent(g_UIRootObject);
}


UIObject::~UIObject()
{
}
