#include "Clothes.hpp"

Clothes::Clothes(Geometry geometry, Engine::Material *material)
{
	// Generate Meshes for Hat
	Engine::Mesh *hatMesh = new Engine::Mesh();
	geometry.GenerateCylinder(hatMesh, 32, 0.8f, 0.6f);
	Engine::Mesh *cylinderMesh = new Engine::Mesh();
	geometry.GenerateCylinder(cylinderMesh, 32);
	Engine::Mesh *coneMesh = new Engine::Mesh();
	geometry.GenerateCone(coneMesh, 32);

	hat.root = new Engine::RenderObject(nullptr, nullptr);
	hat.body = new Engine::RenderObject(hatMesh, material);
	hat.body->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	hat.body->AddParent(hat.root);
	hat.ribbon = new Engine::RenderObject(cylinderMesh, material);
	hat.ribbon->SetScale(glm::vec3(0.4f, 0.4f, 0.1f));
	hat.ribbon->AddParent(hat.root);
	hat.bottom = new Engine::RenderObject(cylinderMesh, material);
	hat.bottom->SetScale(glm::vec3(0.6f, 0.6f, 0.025f));
	hat.bottom->SetPosition(glm::vec3(0.0f, 0.0f, -0.5f));
	hat.bottom->AddParent(hat.root);

	carrotNose.root = new Engine::RenderObject(coneMesh, material);
	carrotNose.root->SetScale(glm::vec3(0.07f, 0.07f, 0.4f));
}

Clothes::~Clothes()
{

}

void Clothes::RenderHat(Engine::Camera *camera, DefaultMaterial *material)
{
	material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	hat.body->Render(camera);
	material->UpdateColor(glm::vec4(0.9f, 0.2f, 0.0f, 1.0f));
	hat.ribbon->Render(camera);
	material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	hat.bottom->Render(camera);
}

void Clothes::RenderCarrotNose(Engine::Camera *camera, DefaultMaterial *material)
{
	material->UpdateColor(glm::vec4(0xFB / 255.0f, 0x88 / 255.0f, 0x31 / 255.0f, 1.0f));
	carrotNose.root->Render(camera);
}