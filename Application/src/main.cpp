// STL
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <map>

// include opengl extension and application library
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// include Engine
#include <Camera.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <RenderObject.hpp>

// include application headers
#include <DefaultMaterial.hpp>
#include <PickingMaterial.hpp>
#include <LineMaterial.hpp>
#include <Geometry.hpp>
#include <Animation.hpp>
#include <picking.hpp>
#include <PickableObject.hpp>
#include <Snowman.hpp>
#include <Clothes.hpp>
#include <UIObject.hpp>
#include <UISelectableObject.hpp>
#include <UIButton.hpp>
#include <UIToggler.hpp>
#include <Terrain.hpp>

#define _USE_MATH_DEFINES
constexpr float PI = 3.1415926f;

float randf(float min, float max)
{
	return min + (max - min) * (float)rand() / 32768.0f;
}

GLFWwindow* g_window;
float g_window_width = 1024.0f;
float g_window_height = 768.0f;
int g_framebuffer_width = 1024;
int g_framebuffer_height = 768;

/* Static variables for handling camera rotation. */
static bool mode_drag = false;
static float camera_distance = 7.5f;
static float ui_distance = 1.0f;

/* Static variables for tracking cursor position. */
static bool cursor_initialized = false;
static float cursor_x = 0.0f, cursor_y = 0.0f, cursor_prev_x = 0.0f, cursor_prev_y = 0.0f;

/* Static list containing the UI components. */
static std::vector<UIObject *> uiObjects;
static UIToggler *inventoryTogglerObjects[24];
static int inventory_size = 13;
static int inventory_visible[] = { 3, 6, 7, 8, 12, 13, 14, 15, 16, 18, 21, 22, 23 };
static int inventory_conflicts[4][6] = {
	{3, 6, 7, 8},
	{12, 13, 14},
	{15, 16},
	{18, 21, 22, 23}
};

/* Some constants regarding the inventory. */
constexpr int INVENTORY_WIDTH = 3;
constexpr int INVENTORY_HEIGHT = 8;
constexpr float INVENTORY_BLOCK_SIZE = 0.08f;
constexpr float INVENTORY_BLOCK_MARGIN = 0.016f;
constexpr float INVENTORY_POSITION_X = 0.60f;
constexpr float INVENTORY_POSITION_Y = 0.17f;
constexpr float INVENTORY_LAYER_Z = 0.002f;

/* Sensitivity of mouse dragging. */
constexpr float DRAG_SPEED = 0.002f;
static float camera_rot_x = 0.0f;
static float camera_rot_z = 0.0f;

/* Static variables for controlling UI picking system. */
static int press_target = 0;
static int hover_target = 0;

/* Global pointer to the UI root object. */
bool uiRootObjectInitialized = false;
Engine::RenderObject *g_UIRootObject = nullptr;

/* Global map containing all render objects with indices. */
std::map<int, Engine::RenderObject *> g_renderObjects;

/* Static pointer to active animation. */
Animation *activeAnimation;

static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods)
{
	double xpos, ypos;
	glfwGetCursorPos(a_window, &xpos, &ypos);
	xpos = xpos / ((double)g_window_width) * ((double)g_framebuffer_width);
	ypos = ypos / ((double)g_window_height) * ((double)g_framebuffer_height);

	/* Dragging with right mouse button. */
	if (a_button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (a_action == GLFW_PRESS)
			mode_drag = true;
		else if (a_action == GLFW_RELEASE)
			mode_drag = false;
	}

	else if (a_button == GLFW_MOUSE_BUTTON_LEFT)
	{
		/* Manage picking system. */
		if (!mode_drag)
		{
			int target = pick((int)xpos, (int)ypos, g_framebuffer_width, g_framebuffer_height);

			if (a_action == GLFW_PRESS)
			{
				press_target = target;
				if (g_renderObjects.find(press_target) != g_renderObjects.end())
					g_renderObjects[press_target]->onPress();

			}
			else if (a_action == GLFW_RELEASE)
			{
				if (g_renderObjects.find(press_target) != g_renderObjects.end())
					g_renderObjects[press_target]->onRelease();
				if (target == press_target && g_renderObjects.find(press_target) != g_renderObjects.end())
				{
					g_renderObjects[press_target]->onClick();

					/* Handle duplicate selection for accessories */
					for (int i = 0; i < 4; i++)
					{
						std::vector<int> selected;
						for (int j = 0; j < 6; j++)
						{
							if (inventoryTogglerObjects[inventory_conflicts[i][j]]
								&& inventoryTogglerObjects[inventory_conflicts[i][j]]->GetSelected())
								selected.push_back(inventory_conflicts[i][j]);
						}
						if (selected.size() > 1 && std::find(selected.begin(), selected.end(), press_target - 1) != selected.end())
						{
							for (auto index : selected)
								if (index != press_target - 1)
									inventoryTogglerObjects[index]->SetSelected(false);
						}
					}
				}
				press_target = 0;
			}
		}
	}
}

static void CursorPosCallback(GLFWwindow* a_window, double a_xpos, double a_ypos)
{
	cursor_x = static_cast<float>(a_xpos);
	cursor_y = static_cast<float>(a_ypos);

	int new_target = pick((int)a_xpos, (int)a_ypos, g_framebuffer_width, g_framebuffer_height);
	if (new_target != hover_target)
	{
		/* Manage hovering system. */
		if (!mode_drag)
		{
			if (g_renderObjects.find(hover_target) != g_renderObjects.end())
				g_renderObjects[hover_target]->onExit();
			if (g_renderObjects.find(new_target) != g_renderObjects.end())
				g_renderObjects[new_target]->onEnter();
		}
	}
	hover_target = new_target;
}

static void KeyboardCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
{
    if (a_action == GLFW_PRESS)
    {
        switch (a_key)
        {
		// TODO: SELECT ANIMATION BY KEYBOARD INPUT
        default:
            break;
        }
    }
}


int main(int argc, char** argv)
{
	srand(time(NULL));

    // Initialize GLFW library
    if (!glfwInit())
    {
        return -1;
    }

    // Create window and OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    g_window = glfwCreateWindow(g_window_width, g_window_height, "HW2 - Do you want to build a snowman?", NULL, NULL);
    if (!g_window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(g_window);

    // Initialize GLEW library
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK)
    {
        std::cout << "GLEW Error: " << glewGetErrorString(glew_error) << std::endl;
        exit(1);
    }

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glfwSetInputMode(g_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(g_window, MouseButtonCallback);
    glfwSetCursorPosCallback(g_window, CursorPosCallback);
    glfwSetKeyCallback(g_window, KeyboardCallback);

    // Initialize framebuffer object and picking textures
    pickingInitialize(g_framebuffer_width, g_framebuffer_width);

	g_renderObjects = std::map<int, Engine::RenderObject *>();
	uiObjects = std::vector<UIObject *>();

	// Initialize Camera
    Engine::Camera* main_camera = new Engine::Camera();
    main_camera->SetPosition(glm::vec3(0.0f, 0.0f, camera_distance));
	Engine::RenderObject *cameraTargetObject = new Engine::RenderObject(nullptr, nullptr);
	main_camera->AddParent(cameraTargetObject);

	// Initialize UI System
	g_UIRootObject = new Engine::RenderObject(nullptr, nullptr);
	uiRootObjectInitialized = true;
	g_UIRootObject->AddParent(cameraTargetObject);

    Geometry geometry = Geometry();

	Engine::Mesh *squareMesh = new Engine::Mesh();
	geometry.GenerateSquare(squareMesh);

	DefaultMaterial *material = new DefaultMaterial();
	material->CreateMaterial();
	PickingMaterial *pickingMaterial = new PickingMaterial();
	pickingMaterial->CreateMaterial();

	// Temporary terrain
	Terrain *terrain = new Terrain(geometry);

	// Create actual components and attach them to skeleton
	Snowman *snowman = new Snowman(geometry, material);

	// Create customizable clothes
	Clothes *clothes = new Clothes(geometry, material);

	// Set camera focus
	cameraTargetObject->SetPosition(snowman->GetRootObject()->GetPosition());
	cameraTargetObject->SetOrientation(glm::rotate(glm::mat4(1.0f), 0.5f * PI, glm::vec3(1.0f, 0.0f, 0.0f)));
	camera_rot_x = 0.5f * PI;

	// Create UI objects
	UIObject *inventoryWindowObject = new UIObject(squareMesh, material);
	inventoryWindowObject->SetPosition(glm::vec3(INVENTORY_POSITION_X, INVENTORY_POSITION_Y, camera_distance - ui_distance));
	inventoryWindowObject->SetScale(glm::vec3(
		INVENTORY_WIDTH * INVENTORY_BLOCK_SIZE + (INVENTORY_WIDTH + 1) * INVENTORY_BLOCK_MARGIN, 
		INVENTORY_HEIGHT * INVENTORY_BLOCK_SIZE + (INVENTORY_HEIGHT + 1) * INVENTORY_BLOCK_MARGIN,
		1.0f));
	inventoryWindowObject->SetColor(glm::vec3(0.2f, 0.2f, 0.2f));
	uiObjects.push_back(inventoryWindowObject);

	for (int i = 0; i < inventory_size; i++)
	{
		int x = inventory_visible[i] % INVENTORY_WIDTH;
		int y = inventory_visible[i] / INVENTORY_WIDTH;

		UIToggler *inventoryObject = new UIToggler(squareMesh, material);
		inventoryObject->SetPosition(glm::vec3(
			INVENTORY_POSITION_X + ((float)x - 0.5f * (float)(INVENTORY_WIDTH - 1)) * (INVENTORY_BLOCK_SIZE + INVENTORY_BLOCK_MARGIN),
			INVENTORY_POSITION_Y + ((float)y - 0.5f * (float)(INVENTORY_HEIGHT - 1)) * (INVENTORY_BLOCK_SIZE + INVENTORY_BLOCK_MARGIN),
			camera_distance - ui_distance + INVENTORY_LAYER_Z
		));
		inventoryObject->SetScale(glm::vec3(INVENTORY_BLOCK_SIZE, INVENTORY_BLOCK_SIZE, 1.0f));
		inventoryObject->SetIndex(inventory_visible[i] + 1);
		inventoryObject->SetPickingMat(pickingMaterial);
		inventoryObject->SetColor(glm::vec3(0.8f, 0.8f, 0.8f));
		inventoryObject->SetSelectedColor(glm::vec3(1.0f, 1.0f, 0.3f));
		uiObjects.push_back(inventoryObject);
		inventoryTogglerObjects[inventory_visible[i]] = inventoryObject;
	}

	// connect icons with UI togglers
	clothes->wand_icon.root->AddParent(g_renderObjects[4]);
	clothes->green_glove_icon.root->AddParent(g_renderObjects[7]);
	clothes->red_glove_icon.root->AddParent(g_renderObjects[8]);
	clothes->cane_icon.root->AddParent(g_renderObjects[9]);
	clothes->green_scarf_icon.root->AddParent(g_renderObjects[13]);
	clothes->red_scarf_icon.root->AddParent(g_renderObjects[14]);
	clothes->coat_icon.root->AddParent(g_renderObjects[15]);
	clothes->carrot_icon.root->AddParent(g_renderObjects[16]);
	clothes->rudolph_icon.root->AddParent(g_renderObjects[17]);
	clothes->cat_ear_icon.root->AddParent(g_renderObjects[19]);
	clothes->hat_icon.root->AddParent(g_renderObjects[22]);
	clothes->wizard_hat_icon.root->AddParent(g_renderObjects[23]);
	clothes->santa_hat_icon.root->AddParent(g_renderObjects[24]);

	// initialize inventory selection
	snowman->SetHeadAccessory(clothes->hat.root);
	snowman->SetHeadAccessory(clothes->wizard_hat.root);
	snowman->SetHeadAccessory(clothes->santa_hat.root);
	snowman->SetHeadAccessory(clothes->cat_ear.root);
	inventoryTogglerObjects[21]->SetSelected(true);
	snowman->SetNose(clothes->carrot.root);
	snowman->SetNose(clothes->rudolph.root);
	inventoryTogglerObjects[15]->SetSelected(true);
	snowman->SetTorsoAccessory(clothes->scarf.root);
	snowman->SetTorsoAccessory(clothes->coat.root);
	inventoryTogglerObjects[12]->SetSelected(true);
	snowman->SetHandAccessory(clothes->glove_left.root, clothes->glove_right.root);
	snowman->SetHandAccessory(nullptr, clothes->cane.root);
	snowman->SetHandAccessory(nullptr, clothes->wand.root);
	inventoryTogglerObjects[6]->SetSelected(true);

    float prev_time = 0;

	// initialize animation
	Animation::KeyFrame idleKeyFrame;
	idleKeyFrame.torsoJoint = glm::quat_cast(glm::mat4(1.0f));
	idleKeyFrame.headJoint = glm::quat_cast(glm::mat4(1.0f));
	idleKeyFrame.leftShoulder = glm::quat_cast(glm::rotate(
		glm::mat4(1.0f), 1.2f, glm::vec3(0.0f, 1.0f, -0.1f)
	));
	idleKeyFrame.rightShoulder = glm::quat_cast(glm::rotate(
		glm::mat4(1.0f), -1.4f, glm::vec3(0.0f, 1.0f, -0.2f)
	));

	Animation::KeyFrame keyframe = idleKeyFrame;
	
	Animation *anim_1 = new Animation();
	// TODO: ADD MORE ANIMATIONS AND KEYFRAMES

	activeAnimation = nullptr;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(g_window) && glfwGetKey(g_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float total_time = (float)glfwGetTime();
        float elapsed_time = total_time - prev_time;
        prev_time = total_time;

		float input_cursor_x = cursor_x - cursor_prev_x;
		float input_cursor_y = cursor_y - cursor_prev_y;
		cursor_prev_x = cursor_x;
		cursor_prev_y = cursor_y;

		// animate objects
		if (activeAnimation != nullptr)
		{
			activeAnimation->AddTime(elapsed_time);
			activeAnimation->AnimateSnowman(snowman);
		}

		/* Handle camera rotation when drag mode is enabled.
		 * We can do it in a clever way: instead of adusting both rotation and position of the camera,
		 * we can attach a dummy look-at object at the selected object,
		 * and parent the camera's transform to the dummy object.
		 * Then, by controlling the rotation of the dummy object, the camera's position and rotation are adjusted. */
		if (cursor_initialized && mode_drag)
		{
			camera_rot_z += -DRAG_SPEED * input_cursor_x;
			camera_rot_x += -DRAG_SPEED * input_cursor_y;
			if (camera_rot_x > 0.5f * PI)
				camera_rot_x = 0.5f * PI;
			if (camera_rot_x < 0)
				camera_rot_x = 0;

			glm::mat4 orientation = glm::mat4(1.0f);
			orientation = glm::rotate(orientation, camera_rot_z, glm::vec3(0.0f, 0.0f, 1.0f));
			orientation = glm::rotate(orientation, camera_rot_x, glm::vec3(1.0f, 0.0f, 0.0f));

			cameraTargetObject->SetOrientation(orientation);
		}

        // this is for picking the object using mouse interaction
        // binding framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, picking_fbo);
        // Background: RGB = 0x000000 => objectID: 0
        glClearColor((GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render your objects that you want to select using mouse interaction here
		for (auto it : g_renderObjects)
		{
			Engine::RenderObject *obj = it.second;
			if (obj != nullptr)
			{
				obj->RenderPicking(main_camera);
			}
		}
		
        // Drawing object again
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor((GLclampf) 0xBD / 255.0f, (GLclampf) 0xEC / 255.0f, (GLclampf) 0xF3 / 255.0f, (GLclampf) 1.0f);

		// Clear frame buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Regular objects
		material->UpdateEnableLighting(true);
		material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		snowman->Render(main_camera, material);
		for (int index = 0; index < 24; index++)
		{
			if (inventoryTogglerObjects[index]
				&& inventoryTogglerObjects[index]->GetSelected())
				clothes->RenderObject(main_camera, material, index);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		terrain->Render(main_camera);
		glDisable(GL_BLEND);

		// Render UIs
		material->UpdateEnableLighting(false);
		for (auto obj : uiObjects)
		{
			material->UpdateColor(glm::vec4(obj->GetRenderColor(), 1.0f));
			obj->Render(main_camera);
		}
		for (int index = 0; index < 24; index++)
		{
			clothes->RenderUIObject(main_camera, material, index);
		}
		
		/* Swap front and back buffers */
        glfwSwapBuffers(g_window);

        /* Poll for and process events */
        glfwPollEvents();

		cursor_initialized = true;
    }

    // Delete resources
    delete main_camera;
	deletePickingResources();
	
	g_renderObjects.clear();
	uiObjects.clear();

	delete snowman;

    glfwTerminate();
    return 0;

}