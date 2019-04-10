#pragma once

#include "TerrainMaterial.hpp"
#include "Geometry.hpp"
#include "Mesh.hpp"
#include "RenderObject.hpp"

#include "PerVertexColorMaterial.hpp"

class Terrain : public Engine::RenderObject
{

public:
	Terrain(Geometry geometry);
};