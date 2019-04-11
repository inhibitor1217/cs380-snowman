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
	Engine::Mesh *sphereMesh = new Engine::Mesh();
	geometry.GenerateIcosphere(sphereMesh, 2);
	Engine::Mesh *earMesh = new Engine::Mesh();
	geometry.GenerateCone(earMesh, 3);
	Engine::Mesh *cylinderWallMesh = new Engine::Mesh();
	geometry.GenerateCylinderWall(cylinderWallMesh, 32, 2.0f, 0.4f, 0.9 * PI);

	hat.root = new Engine::RenderObject(nullptr, nullptr);
	hat.body = new Engine::RenderObject(hatMesh, material);
	hat.body->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	hat.body->SetPosition(glm::vec3(0.0f, 0.0f, 0.5f));
	hat.body->AddParent(hat.root);
	hat.ribbon = new Engine::RenderObject(cylinderMesh, material);
	hat.ribbon->SetScale(glm::vec3(0.4f, 0.4f, 0.1f));
	hat.ribbon->SetPosition(glm::vec3(0.0f, 0.0f, 0.5f));
	hat.ribbon->AddParent(hat.root);
	hat.bottom = new Engine::RenderObject(cylinderMesh, material);
	hat.bottom->SetScale(glm::vec3(0.6f, 0.6f, 0.05f));
	hat.bottom->AddParent(hat.root);

	hat_icon.root = new Engine::RenderObject(nullptr, nullptr);
	hat_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));
	hat_icon.root->SetPosition(glm::vec3(-0.015f, -0.01f, 0.03f));
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

	wizard_hat.root = new Engine::RenderObject(nullptr, nullptr);
	wizard_hat.body = new Engine::RenderObject(coneMesh, material);
	wizard_hat.body->AddParent(wizard_hat.root);
	wizard_hat.body->SetScale(glm::vec3(0.4f, 0.4f, 1.0f));
	wizard_hat.bottom = new Engine::RenderObject(cylinderMesh, material);
	wizard_hat.bottom->AddParent(wizard_hat.root);
	wizard_hat.bottom->SetScale(glm::vec3(0.7f, 0.7f, 0.01f));

	wizard_hat_icon.root = new Engine::RenderObject(nullptr, nullptr);
	wizard_hat_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));
	wizard_hat_icon.root->SetPosition(glm::vec3(-0.015f, -0.025f, 0.03f));
	wizard_hat_icon.body = new Engine::RenderObject(coneMesh, material);
	wizard_hat_icon.body->AddParent(wizard_hat_icon.root);
	wizard_hat_icon.body->SetScale(glm::vec3(0.02f, 0.02f, 0.05f));
	wizard_hat_icon.bottom = new Engine::RenderObject(cylinderMesh, material);
	wizard_hat_icon.bottom->AddParent(wizard_hat_icon.root);
	wizard_hat_icon.bottom->SetScale(glm::vec3(0.035f, 0.035f, 0.0005f));
	
	santa_hat.root = new Engine::RenderObject(nullptr, nullptr);
	santa_hat.bottom = new Engine::RenderObject(scarfMesh, material);
	santa_hat.bottom->AddParent(santa_hat.root);
	santa_hat.bottom->SetScale(glm::vec3(0.5f, 0.5f, 0.15f));
	santa_hat.body = new Engine::RenderObject(coneMesh, material);
	santa_hat.body->AddParent(santa_hat.root);
	santa_hat.body->SetScale(glm::vec3(0.45f, 0.45f, 1.0f));
	santa_hat.body->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.3f, glm::vec3(1.0f, 1.0f, 0.0f)
	));
	santa_hat.end = new Engine::RenderObject(sphereMesh, material);
	santa_hat.end->AddParent(santa_hat.body);
	santa_hat.end->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	santa_hat.end->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	santa_hat_icon.root = new Engine::RenderObject(nullptr, nullptr);
	santa_hat_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));
	santa_hat_icon.root->SetPosition(glm::vec3(-0.015f, -0.025f, 0.02f));
	santa_hat_icon.bottom = new Engine::RenderObject(scarfMesh, material);
	santa_hat_icon.bottom->AddParent(santa_hat_icon.root);
	santa_hat_icon.bottom->SetScale(glm::vec3(0.025f, 0.025f, 0.007f));
	santa_hat_icon.body = new Engine::RenderObject(coneMesh, material);
	santa_hat_icon.body->AddParent(santa_hat_icon.root);
	santa_hat_icon.body->SetScale(glm::vec3(0.022f, 0.022f, 0.05f));
	santa_hat_icon.body->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.3f, glm::vec3(1.0f, 1.0f, 0.0f)
	));
	santa_hat_icon.end = new Engine::RenderObject(sphereMesh, material);
	santa_hat_icon.end->AddParent(santa_hat_icon.body);
	santa_hat_icon.end->SetScale(glm::vec3(0.005f, 0.005f, 0.005f));
	santa_hat_icon.end->SetPosition(glm::vec3(0.0f, 0.0f, 0.05f));

	cat_ear.root = new Engine::RenderObject(nullptr, nullptr);
	cat_ear.root->SetPosition(glm::vec3(0.05f, 0.0f, -0.12f));
	cat_ear.leftEar = new Engine::RenderObject(earMesh, material);
	cat_ear.leftEar->AddParent(cat_ear.root);
	cat_ear.leftEar->SetPosition(glm::vec3(0.4f, 0.0f, 0.0f));
	cat_ear.leftEar->SetOrientation(glm::rotate(
		glm::rotate(
			glm::mat4(1.0f), 0.7f, glm::vec3(0.0f, 1.0f, 0.0f)
		), PI, glm::vec3(0.0f, 0.0f, 1.0f)
	));
	cat_ear.leftEar->SetScale(glm::vec3(0.3f, 0.15f, 0.3f));
	cat_ear.leftInnerEar = new Engine::RenderObject(earMesh, material);
	cat_ear.leftInnerEar->AddParent(cat_ear.leftEar);
	cat_ear.leftInnerEar->SetPosition(glm::vec3(0.0f, 0.05f, 0.0f));
	cat_ear.leftInnerEar->SetScale(glm::vec3(0.2f, 0.1f, 0.2f));
	cat_ear.rightEar = new Engine::RenderObject(earMesh, material);
	cat_ear.rightEar->AddParent(cat_ear.root);
	cat_ear.rightEar->SetPosition(glm::vec3(-0.4f, 0.0f, 0.0f));
	cat_ear.rightEar->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.7f, glm::vec3(0.0f, 1.0f, 0.0f)
	));
	cat_ear.rightEar->SetScale(glm::vec3(0.3f, 0.15f, 0.3f));
	cat_ear.rightInnerEar = new Engine::RenderObject(earMesh, material);
	cat_ear.rightInnerEar->AddParent(cat_ear.rightEar);
	cat_ear.rightInnerEar->SetPosition(glm::vec3(0.0f, -0.05f, 0.0f));
	cat_ear.rightInnerEar->SetScale(glm::vec3(0.2f, 0.1f, 0.2f));

	cat_ear_icon.root = new Engine::RenderObject(nullptr, nullptr);
	cat_ear_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.4f * PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));
	cat_ear_icon.root->SetPosition(glm::vec3(0.0f, 0.0f, 0.005f));
	cat_ear_icon.leftEar = new Engine::RenderObject(earMesh, material);
	cat_ear_icon.leftEar->AddParent(cat_ear_icon.root);
	cat_ear_icon.leftEar->SetPosition(glm::vec3(0.02f, 0.0f, 0.0f));
	cat_ear_icon.leftEar->SetOrientation(glm::rotate(
		glm::rotate(
			glm::mat4(1.0f), 0.7f, glm::vec3(0.0f, 1.0f, 0.0f)
		), PI, glm::vec3(0.0f, 0.0f, 1.0f)
	));
	cat_ear_icon.leftEar->SetScale(glm::vec3(0.02f, 0.01f, 0.02f));
	cat_ear_icon.leftInnerEar = new Engine::RenderObject(earMesh, material);
	cat_ear_icon.leftInnerEar->AddParent(cat_ear_icon.leftEar);
	cat_ear_icon.leftInnerEar->SetPosition(glm::vec3(0.0f, 0.005f, 0.0f));
	cat_ear_icon.leftInnerEar->SetScale(glm::vec3(0.013f, 0.0067f, 0.013f));
	cat_ear_icon.rightEar = new Engine::RenderObject(earMesh, material);
	cat_ear_icon.rightEar->AddParent(cat_ear_icon.root);
	cat_ear_icon.rightEar->SetPosition(glm::vec3(-0.02f, 0.0f, 0.0f));
	cat_ear_icon.rightEar->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.7f, glm::vec3(0.0f, 1.0f, 0.0f)
	));
	cat_ear_icon.rightEar->SetScale(glm::vec3(0.02f, 0.01f, 0.02f));
	cat_ear_icon.rightInnerEar = new Engine::RenderObject(earMesh, material);
	cat_ear_icon.rightInnerEar->AddParent(cat_ear_icon.rightEar);
	cat_ear_icon.rightInnerEar->SetPosition(glm::vec3(0.0f, -0.005f, 0.0f));
	cat_ear_icon.rightInnerEar->SetScale(glm::vec3(0.013f, 0.0067f, 0.013f));

	carrot.root = new Engine::RenderObject(coneMesh, material);
	carrot.root->SetScale(glm::vec3(0.07f, 0.07f, 0.4f));

	carrot_icon.root = new Engine::RenderObject(coneMesh, material);
	carrot_icon.root->SetScale(glm::vec3(0.012f, 0.012f, 0.07f));
	carrot_icon.root->SetPosition(glm::vec3(0.0f, -0.02f, 0.01f));
	carrot_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.3f * PI, glm::vec3(1.0f, 0.5f, -0.5f)
	));

	rudolph.root = new Engine::RenderObject(nullptr, nullptr);
	rudolph.body = new Engine::RenderObject(cylinderMesh, material);
	rudolph.body->AddParent(rudolph.root);
	rudolph.body->SetScale(glm::vec3(0.02f, 0.02f, 0.2f));
	rudolph.body->SetPosition(glm::vec3(0.0f, 0.0f, 0.2f));
	rudolph.end = new Engine::RenderObject(sphereMesh, material);
	rudolph.end->AddParent(rudolph.root);
	rudolph.end->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	rudolph.end->SetPosition(glm::vec3(0.0f, 0.0f, 0.4f));

	rudolph_icon.root = new Engine::RenderObject(nullptr, nullptr);
	rudolph_icon.root->SetPosition(glm::vec3(0.0f, -0.01f, 0.0f));
	rudolph_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.3f * PI, glm::vec3(1.0f, 0.5f, -0.5f)
	));
	rudolph_icon.body = new Engine::RenderObject(cylinderMesh, material);
	rudolph_icon.body->AddParent(rudolph_icon.root);
	rudolph_icon.body->SetScale(glm::vec3(0.002f, 0.002f, 0.02f));
	rudolph_icon.body->SetPosition(glm::vec3(0.0f, 0.0f, 0.02f));
	rudolph_icon.end = new Engine::RenderObject(sphereMesh, material);
	rudolph_icon.end->AddParent(rudolph_icon.root);
	rudolph_icon.end->SetScale(glm::vec3(0.01f, 0.01f, 0.01f));
	rudolph_icon.end->SetPosition(glm::vec3(0.0f, 0.0f, 0.04f));

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

	coat.root = new Engine::RenderObject(nullptr, nullptr);
	coat.upper = new Engine::RenderObject(cylinderWallMesh, material);
	coat.upper->AddParent(coat.root);
	coat.upper->SetPosition(glm::vec3(0.0f, 0.0f, 0.4f));
	coat.upper->SetScale(glm::vec3(0.5f, 0.5f, 0.2f));
	coat.upper->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 0.5f * PI, glm::vec3(0.0f, 0.0f, 1.0f)
	));
	coat.lower = new Engine::RenderObject(cylinderWallMesh, material);
	coat.lower->AddParent(coat.root);
	coat.lower->SetPosition(glm::vec3(0.0f, 0.0f, -0.6f));
	coat.lower->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	coat.lower->SetOrientation(glm::rotate(
		glm::rotate(
			glm::mat4(1.0f), 0.5f * PI, glm::vec3(0.0f, 0.0f, 1.0f)
		), PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));

	coat_icon.root = new Engine::RenderObject(nullptr, nullptr);
	coat_icon.root->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));
	coat_icon.upper = new Engine::RenderObject(cylinderWallMesh, material);
	coat_icon.upper->AddParent(coat_icon.root);
	coat_icon.upper->SetPosition(glm::vec3(0.0f, 0.0f, 0.01f));
	coat_icon.upper->SetScale(glm::vec3(0.012f, 0.012f, 0.005f));
	coat_icon.upper->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -0.5f * PI, glm::vec3(0.0f, 0.0f, 1.0f)
	));
	coat_icon.lower = new Engine::RenderObject(cylinderWallMesh, material);
	coat_icon.lower->AddParent(coat_icon.root);
	coat_icon.lower->SetPosition(glm::vec3(0.0f, 0.0f, -0.015f));
	coat_icon.lower->SetScale(glm::vec3(0.025f, 0.025f, 0.025f));
	coat_icon.lower->SetOrientation(glm::rotate(
		glm::rotate(
			glm::mat4(1.0f), -0.5f * PI, glm::vec3(0.0f, 0.0f, 1.0f)
		), PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));

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
		break;
	case 14:
		material->UpdateColor(glm::vec4(0x63 / 255.0f, 0x2A / 255.0f, 0x6D / 255.0f, 1.0f));
		coat.upper->Render(camera);
		coat.lower->Render(camera);
		break;
	case 15:
		material->UpdateColor(glm::vec4(0xFB / 255.0f, 0x88 / 255.0f, 0x31 / 255.0f, 1.0f));
		carrot.root->Render(camera);
		break;
	case 16:
		material->UpdateColor(glm::vec4(0x60 / 255.0f, 0x41 / 255.0f, 0x2B / 255.0f, 0.1f));
		rudolph.body->Render(camera);
		material->UpdateColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		rudolph.end->Render(camera);
		break;
	case 18:
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		cat_ear.leftEar->Render(camera);
		cat_ear.rightEar->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xB6 / 255.0f, 0xD5 / 255.0f, 1.0f));
		cat_ear.leftInnerEar->Render(camera);
		cat_ear.rightInnerEar->Render(camera);
		break;
	case 21:
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat.body->Render(camera);
		material->UpdateColor(glm::vec4(0.9f, 0.2f, 0.0f, 1.0f));
		hat.ribbon->Render(camera);
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat.bottom->Render(camera);
		break;
	case 22:
		material->UpdateColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		wizard_hat.body->Render(camera);
		wizard_hat.bottom->Render(camera);
		break;
	case 23:
		material->UpdateColor(glm::vec4(0xE5 / 255.0f, 0x00 / 255.0f, 0x22 / 255.0f, 1.0f));
		santa_hat.body->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		santa_hat.bottom->Render(camera);
		santa_hat.end->Render(camera);
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
		break;
	case 7:
		material->UpdateColor(glm::vec4(0xE5 / 255.0f, 0x00 / 255.0f, 0x22 / 255.0f, 1.0f));
		red_glove_icon.hand->Render(camera);
		red_glove_icon.thumb->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		red_glove_icon.wrist->Render(camera);
		break;
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
	case 14:
		material->UpdateColor(glm::vec4(0x63 / 255.0f, 0x2A / 255.0f, 0x6D / 255.0f, 1.0f));
		coat_icon.upper->Render(camera);
		coat_icon.lower->Render(camera);
		break;
	case 15:
		material->UpdateColor(glm::vec4(0xFB / 255.0f, 0x88 / 255.0f, 0x31 / 255.0f, 1.0f));
		carrot_icon.root->Render(camera);
		break;
	case 16:
		material->UpdateColor(glm::vec4(0x60 / 255.0f, 0x41 / 255.0f, 0x2B / 255.0f, 0.1f));
		rudolph_icon.body->Render(camera);
		material->UpdateColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		rudolph_icon.end->Render(camera);
		break;
	case 18:
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		cat_ear_icon.leftEar->Render(camera);
		cat_ear_icon.rightEar->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xB6 / 255.0f, 0xD5 / 255.0f, 1.0f));
		cat_ear_icon.leftInnerEar->Render(camera);
		cat_ear_icon.rightInnerEar->Render(camera);
		break;
	case 21:
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat_icon.body->Render(camera);
		material->UpdateColor(glm::vec4(0.9f, 0.2f, 0.0f, 1.0f));
		hat_icon.ribbon->Render(camera);
		material->UpdateColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		hat_icon.bottom->Render(camera);
		break;
	case 22:
		material->UpdateColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		wizard_hat_icon.body->Render(camera);
		wizard_hat_icon.bottom->Render(camera);
		break;
	case 23:
		material->UpdateColor(glm::vec4(0xE5 / 255.0f, 0x00 / 255.0f, 0x22 / 255.0f, 1.0f));
		santa_hat_icon.body->Render(camera);
		material->UpdateColor(glm::vec4(0xFF / 255.0f, 0xFF / 255.0f, 0xFF / 255.0f, 1.0f));
		santa_hat_icon.bottom->Render(camera);
		santa_hat_icon.end->Render(camera);
		break;
	default:
		break;
	}
}