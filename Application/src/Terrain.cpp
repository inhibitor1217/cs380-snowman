#include "Terrain.hpp"

Terrain::Terrain(Geometry geometry)
{
	// Generate Terrain Mesh
	_mesh = new Engine::Mesh();
	geometry.GenerateTerrainMesh(_mesh);

	// Create Terrain Material
	_material = new TerrainMaterial();
	reinterpret_cast<TerrainMaterial *>(_material)->CreateMaterial();

	// Assemble as RenderObject
	Engine::RenderObject(_mesh, _material);

	SetScale(glm::vec3(10.0f, 10.0f, 1.0f));
}