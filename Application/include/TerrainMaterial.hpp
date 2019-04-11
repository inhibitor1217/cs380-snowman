#pragma once

#include "Material.hpp"

class TerrainMaterial : public Engine::Material
{
public:
	void CreateMaterial();
	void UpdateGlobalColor(glm::vec4 color);
};