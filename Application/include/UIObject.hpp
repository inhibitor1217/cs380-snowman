#pragma once

#include <Mesh.hpp>
#include <Material.hpp>
#include <RenderObject.hpp>

class UIObject: virtual public Engine::RenderObject
{
public:
	UIObject(Engine::Mesh *mesh, Engine::Material *material);
	~UIObject();
};

