#pragma once

#include <vector>
#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Mesh.hpp>

class Geometry
{
private:

protected:
	Geometry *parent;
	std::vector<Geometry *> children;
public:
	Geometry();
	~Geometry();
	void Quad(Engine::Mesh* mesh, int a_a, int a_b, int a_c, int a_d);
	glm::vec3 ComputeNormal(glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c);
	void GenerateTriangle(Engine::Mesh* mesh);
	void GenerateLine(Engine::Mesh* mesh);
	void GenerateStar(Engine::Mesh* mesh);
	void GenerateSquare(Engine::Mesh *mesh);

	void GenerateCube(Engine::Mesh* mesh);
	void GenerateIcosphere(Engine::Mesh *mesh, int resolution_level);
	void GenerateCylinder(Engine::Mesh *mesh, int polygon);
	void GenerateCylinder(Engine::Mesh *mesh, int polygon, float top_radius, float bottom_radius);
	void GenerateCone(Engine::Mesh *mesh, int polygon);
};

