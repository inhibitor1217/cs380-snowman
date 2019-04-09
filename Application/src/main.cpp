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
#include <UIObject.hpp>
#include <UISelectableObject.hpp>
#include <UIButton.hpp>
#include <UIToggler.hpp>

#define _USE_MATH_DEFINES

GLFWwindow* g_window;
float g_window_width = 1920.0f;
float g_window_height = 1440.0f;
int g_framebuffer_width = 1920;
int g_framebuffer_height = 1440;

/* Static variables for handling camera rotation. */
static bool mode_drag = false;
static float camera_distance = 7.5f;
static float ui_distance = 1.0f;

/* Static variables for tracking cursor position. */
static bool cursor_initialized = false;
static float cursor_x = 0.0f, cursor_y = 0.0f, cursor_prev_x = 0.0f, cursor_prev_y = 0.0f;

/* Sensitivity of mouse dragging. */
constexpr float DRAG_SPEED = 0.002f;

/* Static variables for controlling UI picking system. */
static int press_target = 0;
static int hover_target = 0;

/* Global pointer to the UI root object. */
bool uiRootObjectInitialized = false;
Engine::RenderObject *g_UIRootObject = nullptr;

/* Global map containing all render objects with indices. */
std::map<int, Engine::RenderObject *> g_renderObjects;

// TODO: Fill up GLFW mouse button callback function
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
				if (g_renderObjects[press_target])
					g_renderObjects[press_target]->onPress();

			}
			else if (a_action == GLFW_RELEASE)
			{
				if (g_renderObjects[press_target])
					g_renderObjects[press_target]->onRelease();
				if (target == press_target && g_renderObjects[press_target])
					g_renderObjects[press_target]->onClick();
				press_target = 0;
			}
		}
	}
}

// TODO: Fill up GLFW cursor position callback function
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
			if (g_renderObjects[hover_target])
				g_renderObjects[hover_target]->onExit();
			if (g_renderObjects[new_target])
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
        default:
            break;
        }
    }
}


int main(int argc, char** argv)
{
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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

    glfwSetInputMode(g_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(g_window, MouseButtonCallback);
    glfwSetCursorPosCallback(g_window, CursorPosCallback);
    glfwSetKeyCallback(g_window, KeyboardCallback);

    // Initialize framebuffer object and picking textures
    pickingInitialize(g_framebuffer_width, g_framebuffer_width);

	g_renderObjects = std::map<int, Engine::RenderObject *>();

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
	Engine::Mesh *cubeMesh = new Engine::Mesh();
	geometry.GenerateCube(cubeMesh);

	DefaultMaterial *material = new DefaultMaterial();
	material->CreateMaterial();
	PickingMaterial *pickingMaterial = new PickingMaterial();
	pickingMaterial->CreateMaterial();

	Engine::RenderObject *renderObject = new Engine::RenderObject(cubeMesh, material);

	// Create UI objects
	UIButton *btn1 = new UIButton(squareMesh, material);
	btn1->SetIndex(1);
	btn1->SetPickingMat(pickingMaterial);
	btn1->SetPosition(glm::vec3(-0.1f, -0.5f, camera_distance - ui_distance));
	btn1->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	
	UIToggler *btn2 = new UIToggler(squareMesh, material);
	btn2->SetIndex(2);
	btn2->SetPickingMat(pickingMaterial);
	btn2->SetPosition(glm::vec3(0.1f, -0.5f, camera_distance - ui_distance));
	btn2->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	
    float prev_time = 0;

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

		/* Handle camera rotation when drag mode is enabled.
		 * We can do it in a clever way: instead of adusting both rotation and position of the camera,
		 * we can attach a dummy look-at object at the selected object,
		 * and parent the camera's transform to the dummy object.
		 * Then, by controlling the rotation of the dummy object, the camera's position and rotation are adjusted. */
		if (cursor_initialized && mode_drag)
		{
			cameraTargetObject->SetOrientation(
				glm::rotate(cameraTargetObject->GetOrientation(), -DRAG_SPEED * input_cursor_x, glm::vec3(0.0f, 1.0f, 0.0f))
			);
			cameraTargetObject->SetOrientation(
				glm::rotate(cameraTargetObject->GetOrientation(), -DRAG_SPEED * input_cursor_y, glm::vec3(1.0f, 0.0f, 0.0f))
			);
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
		glClearColor((GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f);

		// Clear frame buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Regular objects
		material->UpdateEnableLighting(true);
		material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		renderObject->Render(main_camera);

		// Render UIs
		material->UpdateEnableLighting(false);
		material->UpdateColor(glm::vec4(btn1->GetRenderColor(), 1.0f));
		btn1->Render(main_camera);
		material->UpdateColor(glm::vec4(btn2->GetRenderColor(), 1.0f));
		btn2->Render(main_camera);
		
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

    glfwTerminate();
    return 0;

}