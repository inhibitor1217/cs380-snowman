#include "Clothes.hpp"

constexpr float PI = 3.1415926f;

Clothes::Clothes(Geometry geometry, Engine::Material *material)
{
	// Generate Meshes for Hat
	Engine::Mesh *hatMesh = new Engine::Mesh();
	geometry.GenerateCylinder(hatMesh, 32, 0.8f, 0.6f);
	Engine::Mesh *cylinderMesh = new Engine::Mesh();
	geometry.GenerateCylinder(cylinderMesh, 32);
	Engine::Mesh *coneMesh = new Engine::Mesh();
	geometry.GenerateCone(coneMesh, 32);
	Engine::Mesh *scarfMesh = new Engine::Mesh();
	geometry.GenerateCylinder(scarfMesh, 32, 0.9f, 1.1f);
	Engine::Mesh *squareMesh = new Engine::Mesh();
	geometry.GenerateSquare(squareMesh);
	Engine::Mesh *cubeMesh = new Engine::Mesh();
	geometry.GenerateCube(cubeMesh);

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

	hat_icon.root = new Engine::RenderObject(nullptr, nullptr);
	hat_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));
	hat_icon.body = new Engine::RenderObject(hatMesh, material);
	hat_icon.body->SetScale(glm::vec3(0.025f, 0.025f, 0.025f));
	hat_icon.body->AddParent(hat_icon.root);
	hat_icon.ribbon = new Engine::RenderObject(cylinderMesh, material);
	hat_icon.ribbon->SetScale(glm::vec3(0.02f, 0.02f, 0.005f));
	hat_icon.ribbon->AddParent(hat_icon.root);
	hat_icon.bottom = new Engine::RenderObject(cylinderMesh, material);
	hat_icon.bottom->SetScale(glm::vec3(0.03f, 0.03f, 0.0012f));
	hat_icon.bottom->SetPosition(glm::vec3(0.0f, 0.0f, -0.025f));
	hat_icon.bottom->AddParent(hat_icon.root);

	carrot.root = new Engine::RenderObject(coneMesh, material);
	carrot.root->SetScale(glm::vec3(0.07f, 0.07f, 0.4f));

	carrot_icon.root = new Engine::RenderObject(coneMesh, material);
	carrot_icon.root->SetScale(glm::vec3(0.012f, 0.012f, 0.07f));
	carrot_icon.root->SetPosition(glm::vec3(0.0f, -0.02f, 0.01f));
	carrot_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.3f * PI, glm::vec3(1.0f, 0.5f, -0.5f)
	));

	scarf.root = new Engine::RenderObject(nullptr, nullptr);
	scarf.body = new Engine::RenderObject(scarfMesh, material);
	scarf.body->AddParent(scarf.root);
	scarf.body->SetScale(glm::vec3(0.6f, 0.6f, 0.4f));
	scarf.branch1 = new Engine::RenderObject(squareMesh, material);
	scarf.branch1->AddParent(scarf.root);
	scarf.branch1->SetScale(glm::vec3(0.4f, 0.8f, 1.0f));
	scarf.branch1->SetPosition(glm::vec3(0.4f, -0.6f, -0.08f));
	scarf.branch1->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.0f, glm::vec3(1.0f, 0.3f, 0.6f)
	));
	scarf.edge1 = new Engine::RenderObject(squareMesh, material);
	scarf.edge1->AddParent(scarf.branch1);
	scarf.edge1->SetScale(glm::vec3(0.45f, 0.2f, 1.0f));
	scarf.edge1->SetPosition(glm::vec3(0.0f, -0.4f, 0.01f));
	scarf.branch2 = new Engine::RenderObject(squareMesh, material);
	scarf.branch2->AddParent(scarf.root);
	scarf.branch2->SetScale(glm::vec3(0.4f, 0.4f, 1.0f));
	scarf.branch2->SetPosition(glm::vec3(0.2f, -0.68f, -0.1f));
	scarf.branch2->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.0f, glm::vec3(1.0f, 0.4f, 0.3f)
	));
	scarf.edge2 = new Engine::RenderObject(squareMesh, material);
	scarf.edge2->AddParent(scarf.branch2);
	scarf.edge2->SetScale(glm::vec3(0.45f, 0.2f, 1.0f));
	scarf.edge2->SetPosition(glm::vec3(0.0f, -0.2f, 0.01f));

	green_scarf_icon.root = new Engine::RenderObject(nullptr, nullptr);
	green_scarf_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.3f * PI, glm::vec3(1.0f, 0.0f, 0.3f)
	));
	green_scarf_icon.body = new Engine::RenderObject(scarfMesh, material);
	green_scarf_icon.body->AddParent(green_scarf_icon.root);
	green_scarf_icon.body->SetScale(glm::vec3(0.03f, 0.03f, 0.01f));
	green_scarf_icon.branch1 = new Engine::RenderObject(squareMesh, material);
	green_scarf_icon.branch1->AddParent(green_scarf_icon.root);
	green_scarf_icon.branch1->SetScale(glm::vec3(0.02f, 0.04f, 0.05f));
	green_scarf_icon.branch1->SetPosition(glm::vec3(0.02f, -0.03f, -0.004f));
	green_scarf_icon.branch1->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.0f, glm::vec3(1.0f, 0.3f, 0.6f)
	));
	green_scarf_icon.edge1 = new Engine::RenderObject(squareMesh, material);
	green_scarf_icon.edge1->AddParent(green_scarf_icon.branch1);
	green_scarf_icon.edge1->SetScale(glm::vec3(0.022f, 0.01f, 0.05f));
	green_scarf_icon.edge1->SetPosition(glm::vec3(0.0f, -0.02f, 0.001f));
	green_scarf_icon.branch2 = new Engine::RenderObject(squareMesh, material);
	green_scarf_icon.branch2->AddParent(green_scarf_icon.root);
	green_scarf_icon.branch2->SetScale(glm::vec3(0.02f, 0.02f, 0.05f));
	green_scarf_icon.branch2->SetPosition(glm::vec3(0.01f, -0.034f, -0.005f));
	green_scarf_icon.branch2->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.0f, glm::vec3(1.0f, 0.4f, 0.3f)
	));
	green_scarf_icon.edge2 = new Engine::RenderObject(squareMesh, material);
	green_scarf_icon.edge2->AddParent(green_scarf_icon.branch2);
	green_scarf_icon.edge2->SetScale(glm::vec3(0.022f, 0.01f, 0.05f));
	green_scarf_icon.edge2->SetPosition(glm::vec3(0.0f, -0.01f, 0.001f));

	red_scarf_icon.root = new Engine::RenderObject(nullptr, nullptr);
	red_scarf_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.3f * PI, glm::vec3(1.0f, 0.0f, 0.3f)
	));
	red_scarf_icon.body = new Engine::RenderObject(scarfMesh, material);
	red_scarf_icon.body->AddParent(red_scarf_icon.root);
	red_scarf_icon.body->SetScale(glm::vec3(0.03f, 0.03f, 0.01f));
	red_scarf_icon.branch1 = new Engine::RenderObject(squareMesh, material);
	red_scarf_icon.branch1->AddParent(red_scarf_icon.root);
	red_scarf_icon.branch1->SetScale(glm::vec3(0.02f, 0.04f, 0.05f));
	red_scarf_icon.branch1->SetPosition(glm::vec3(0.02f, -0.03f, -0.004f));
	red_scarf_icon.branch1->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.0f, glm::vec3(1.0f, 0.3f, 0.6f)
	));
	red_scarf_icon.edge1 = new Engine::RenderObject(squareMesh, material);
	red_scarf_icon.edge1->AddParent(red_scarf_icon.branch1);
	red_scarf_icon.edge1->SetScale(glm::vec3(0.022f, 0.01f, 0.05f));
	red_scarf_icon.edge1->SetPosition(glm::vec3(0.0f, -0.02f, 0.001f));
	red_scarf_icon.branch2 = new Engine::RenderObject(squareMesh, material);
	red_scarf_icon.branch2->AddParent(red_scarf_icon.root);
	red_scarf_icon.branch2->SetScale(glm::vec3(0.02f, 0.02f, 0.05f));
	red_scarf_icon.branch2->SetPosition(glm::vec3(0.01f, -0.034f, -0.005f));
	red_scarf_icon.branch2->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.0f, glm::vec3(1.0f, 0.4f, 0.3f)
	));
	red_scarf_icon.edge2 = new Engine::RenderObject(squareMesh, material);
	red_scarf_icon.edge2->AddParent(red_scarf_icon.branch2);
	red_scarf_icon.edge2->SetScale(glm::vec3(0.022f, 0.01f, 0.05f));
	red_scarf_icon.edge2->SetPosition(glm::vec3(0.0f, -0.01f, 0.001f));

	glove_left.root = new Engine::RenderObject(nullptr, nullptr);
	glove_left.hand = new Engine::RenderObject(cubeMesh, material);
	glove_left.hand->AddParent(glove_left.root);
	glove_left.hand->SetScale(glm::vec3(0.1f, 0.05f, 0.2f));
	glove_left.wrist = new Engine::RenderObject(cubeMesh, material);
	glove_left.wrist->AddParent(glove_left.root);
	glove_left.wrist->SetScale(glm::vec3(0.11f, 0.06f, 0.06f));
	glove_left.wrist->SetPosition(glm::vec3(0.0f, 0.0f, -0.15f));
	glove_left.thumb = new Engine::RenderObject(cubeMesh, material);
	glove_left.thumb->AddParent(glove_left.root);
	glove_left.thumb->SetScale(glm::vec3(0.05f, 0.048f, 0.1f));
	glove_left.thumb->SetPosition(glm::vec3(-0.1f, 0.0f, -0.05f));
	glove_left.thumb->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -1.2f, glm::vec3(0.0f, 1.0f, 0.0f)
	));

	glove_right.root = new Engine::RenderObject(nullptr, nullptr);
	glove_right.hand = new Engine::RenderObject(cubeMesh, material);
	glove_right.hand->AddParent(glove_right.root);
	glove_right.hand->SetScale(glm::vec3(0.1f, 0.05f, 0.2f));
	glove_right.wrist = new Engine::RenderObject(cubeMesh, material);
	glove_right.wrist->AddParent(glove_right.root);
	glove_right.wrist->SetScale(glm::vec3(0.11f, 0.06f, 0.06f));
	glove_right.wrist->SetPosition(glm::vec3(0.0f, 0.0f, -0.15f));
	glove_right.thumb = new Engine::RenderObject(cubeMesh, material);
	glove_right.thumb->AddParent(glove_right.root);
	glove_right.thumb->SetScale(glm::vec3(0.05f, 0.048f, 0.1f));
	glove_right.thumb->SetPosition(glm::vec3(0.1f, 0.0f, -0.05f));
	glove_right.thumb->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.2f, glm::vec3(0.0f, 1.0f, 0.0f)
	));

	green_glove_icon.root = new Engine::RenderObject(nullptr, nullptr);
	green_glove_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(1.0f, 0.0f, 0.3f)
	));
	green_glove_icon.root->SetPosition(glm::vec3(0.0f, 0.0f, 0.01f));
	green_glove_icon.hand = new Engine::RenderObject(cubeMesh, material);
	green_glove_icon.hand->AddParent(green_glove_icon.root);
	green_glove_icon.hand->SetScale(glm::vec3(0.015f, 0.0075f, 0.03f));
	green_glove_icon.wrist = new Engine::RenderObject(cubeMesh, material);
	green_glove_icon.wrist->AddParent(green_glove_icon.root);
	green_glove_icon.wrist->SetScale(glm::vec3(0.016f, 0.009f, 0.009f));
	green_glove_icon.wrist->SetPosition(glm::vec3(0.0f, 0.0f, -0.023f));
	green_glove_icon.thumb = new Engine::RenderObject(cubeMesh, material);
	green_glove_icon.thumb->AddParent(green_glove_icon.root);
	green_glove_icon.thumb->SetScale(glm::vec3(0.0075f, 0.0075f, 0.015f));
	green_glove_icon.thumb->SetPosition(glm::vec3(-0.015f, 0.0f, -0.0075f));
	green_glove_icon.thumb->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -1.2f, glm::vec3(0.0f, 1.0f, 0.0f)
	));

	red_glove_icon.root = new Engine::RenderObject(nullptr, nullptr);
	red_glove_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(1.0f, 0.0f, 0.3f)
	));
	red_glove_icon.root->SetPosition(glm::vec3(0.0f, 0.0f, 0.01f));
	red_glove_icon.hand = new Engine::RenderObject(cubeMesh, material);
	red_glove_icon.hand->AddParent(red_glove_icon.root);
	red_glove_icon.hand->SetScale(glm::vec3(0.015f, 0.0075f, 0.03f));
	red_glove_icon.wrist = new Engine::RenderObject(cubeMesh, material);
	red_glove_icon.wrist->AddParent(red_glove_icon.root);
	red_glove_icon.wrist->SetScale(glm::vec3(0.016f, 0.009f, 0.009f));
	red_glove_icon.wrist->SetPosition(glm::vec3(0.0f, 0.0f, -0.023f));
	red_glove_icon.thumb = new Engine::RenderObject(cubeMesh, material);
	red_glove_icon.thumb->AddParent(red_glove_icon.root);
	red_glove_icon.thumb->SetScale(glm::vec3(0.0075f, 0.0075f, 0.015f));
	red_glove_icon.thumb->SetPosition(glm::vec3(-0.015f, 0.0f, -0.0075f));
	red_glove_icon.thumb->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -1.2f, glm::vec3(0.0f, 1.0f, 0.0f)
	));
}

void Clothes::RenderObject(Engine::Camera *camera, DefaultMaterial *material, int index)
{
	switch (index)
	{
	case 6:
		material->UpdateColor(glm::vec4(0x14 / 255.0f, 0x6B / 255.0f, 0x3A / 255.0f, 1.0f));
		glove_left.hand->Render(camera);
		glove_left.thumb->Render(camera);
		glove_right.hand->Render(camera);
		glove_right.thumb->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		glove_left.wrist->Render(camera);
		glove_right.wrist->Render(camera);
		break;
	case 7:
		material->UpdateColor(glm::vec4(0xE5 / 255.0f, 0x00 / 255.0f, 0x22 / 255.0f, 1.0f));
		glove_left.hand->Render(camera);
		glove_left.thumb->Render(camera);
		glove_right.hand->Render(camera);
		glove_right.thumb->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		glove_left.wrist->Render(camera);
		glove_right.wrist->Render(camera);
		break;
	case 12:
		material->UpdateColor(glm::vec4(0x14 / 255.0f, 0x6B / 255.0f, 0x3A / 255.0f, 1.0f));
		scarf.body->Render(camera);
		scarf.branch1->Render(camera);
		scarf.branch2->Render(camera);
		material->UpdateColor(glm::vec4(0xFF/ 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		scarf.edge1->Render(camera);
		scarf.edge2->Render(camera);
		break;
	case 13:
		material->UpdateColor(glm::vec4(0xE5 / 255.0f, 0x00 / 255.0f, 0x22 / 255.0f, 1.0f));
		scarf.body->Render(camera);
		scarf.branch1->Render(camera);
		scarf.branch2->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xBF / 255.0f, 0x00 / 255.0f, 1.0f));
		scarf.edge1->Render(camera);
		scarf.edge2->Render(camera);
	case 15:
		material->UpdateColor(glm::vec4(0xFB / 255.0f, 0x88 / 255.0f, 0x31 / 255.0f, 1.0f));
		carrot.root->Render(camera);
		break;
	case 21:
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat.body->Render(camera);
		material->UpdateColor(glm::vec4(0.9f, 0.2f, 0.0f, 1.0f));
		hat.ribbon->Render(camera);
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat.bottom->Render(camera);
		break;
	default:
		break;
	}
}

void Clothes::RenderUIObject(Engine::Camera *camera, DefaultMaterial *material, int index)
{
	switch (index)
	{
	case 6:
		material->UpdateColor(glm::vec4(0x14 / 255.0f, 0x6B / 255.0f, 0x3A / 255.0f, 1.0f));
		green_glove_icon.hand->Render(camera);
		green_glove_icon.thumb->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		green_glove_icon.wrist->Render(camera);
	case 7:
		material->UpdateColor(glm::vec4(0xE5 / 255.0f, 0x00 / 255.0f, 0x22 / 255.0f, 1.0f));
		red_glove_icon.hand->Render(camera);
		red_glove_icon.thumb->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		red_glove_icon.wrist->Render(camera);

	case 12:
		material->UpdateColor(glm::vec4(0x14 / 255.0f, 0x6B / 255.0f, 0x3A / 255.0f, 1.0f));
		green_scarf_icon.body->Render(camera);
		green_scarf_icon.branch1->Render(camera);
		green_scarf_icon.branch2->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		green_scarf_icon.edge1->Render(camera);
		green_scarf_icon.edge2->Render(camera);
		break;
	case 13:
		material->UpdateColor(glm::vec4(0xE5 / 255.0f, 0x00 / 255.0f, 0x22 / 255.0f, 1.0f));
		red_scarf_icon.body->Render(camera);
		red_scarf_icon.branch1->Render(camera);
		red_scarf_icon.branch2->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xBF / 255.0f, 0x00 / 255.0f, 1.0f));
		red_scarf_icon.edge1->Render(camera);
		red_scarf_icon.edge2->Render(camera);
		break;
	case 15:
		material->UpdateColor(glm::vec4(0xFB / 255.0f, 0x88 / 255.0f, 0x31 / 255.0f, 1.0f));
		carrot_icon.root->Render(camera);
	case 21:
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat_icon.body->Render(camera);
		material->UpdateColor(glm::vec4(0.9f, 0.2f, 0.0f, 1.0f));
		hat_icon.ribbon->Render(camera);
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat_icon.bottom->Render(camera);
		break;
	default:
		break;
	}
}