#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"
GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = {};
	m_shaderFont = {};
	m_camera = {};
	/*m_meshBox = {};
	m_meshLight = {};*/
	m_meshBoxes.clear();
}

GameController::~GameController()
{
}

void GameController::Initalize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT((glewInit() == GLEW_OK), "Failed to initalize GLEW");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
	
	srand(time(0));

	m_camera = Camera(WindowController::GetInstance().GetResolution());

}

void GameController::RunGame()
{
	//InitOpenGL::ToolWindow^ window = gcnew InitOpenGL::ToolWindow();
	//window->Show();
	//System::Windows::Forms::Application::Run(window);
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("SkyBox.vertexshader", "SkyBox.fragmentshader");

#pragma region CreateMeshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "Assets/Models/teapot.obj");
	m.SetPosition({ 0.5f, 0.0f, 1.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.01f, 0.01f, 0.01f });
	Mesh::Lights.push_back(m);
	
	//Mesh teapot = Mesh();
	//teapot.Create(&m_shaderDiffuse, "Assets/Models/teapot.obj");
	//teapot.SetCameraPosition(m_camera.GetPosition());
	//teapot.SetPosition({ 0.0f, 0.0f, 1.0f });
	//teapot.SetScale({ 0.01f, 0.01f, 0.01f });
	//m_meshBoxes.push_back(teapot);

	//Mesh box = Mesh();
	//box.Create(&m_shaderDiffuse, "Assets/Models/box.obj");
	//box.SetCameraPosition(m_camera.GetPosition());
	//box.SetPosition({ 0.25f, 0.25f, 0.25f });
	//box.SetScale({ 0.1f, 0.1f, 0.1f });
	////m_meshBoxes.push_back(box);

	//Mesh wall = Mesh();
	//wall.Create(&m_shaderDiffuse, "Assets/Models/Wall.obj");
	//wall.SetCameraPosition(m_camera.GetPosition());
	//wall.SetPosition({ 0.0f, 0.0f, 1.0f });
	//wall.SetScale({ 0.05f, 0.05f, 0.05f });
	//m_meshBoxes.push_back(wall);

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "Assets/Models/Fighter.obj");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	fighter.SetScale({ 0.001f, 0.001f, 0.001f });
	m_meshBoxes.push_back(fighter);

	/*SkyBox skybox = SkyBox();
	skybox.Create(&m_shaderSkybox, "Assets/Models/Skybox.obj",
		{
			"Assets/Textures/Skybox/right.jpg",
			"Assets/Textures/Skybox/left.jpg",
			"Assets/Textures/Skybox/top.jpg",
			"Assets/Textures/Skybox/bottom.jpg",
			"Assets/Textures/Skybox/front.jpg",
			"Assets/Textures/Skybox/back.jpg",
		});*/
	//Mesh plane = Mesh();
	//plane.Create(&m_shaderDiffuse, "Assets/Models/Plane.obj");
	//plane.SetCameraPosition(m_camera.GetPosition());
	//plane.SetPosition({ 0, 0, 0 });
	//plane.SetScale({ 0.05f, 0.05f, 0.05f });
	//m_meshBoxes.push_back(plane);
	//
	//Mesh window = Mesh();
	//window.Create(&m_shaderDiffuse, "Assets/Models/Window.obj");
	//window.SetCameraPosition(m_camera.GetPosition());
	//window.SetPosition({ 0, 0, 1.0f });
	//
	//window.SetScale({ 0.05f, 0.05f, 0.05f });
	//m_meshBoxes.push_back(window);


#pragma endregion CreateMeshes
	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 500);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do {
		/*System::Windows::Forms::Application::DoEvents();*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//m_camera.Rotate();
		//glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
		//skybox.Render(m_camera.GetProjection() * view);

		for (size_t i = 0; i < m_meshBoxes.size(); ++i)
		{
			m_meshBoxes[i].Render(m_camera.GetProjection() * m_camera.GetView());
		}		
		for (size_t i = 0; i < Mesh::Lights.size(); ++i)
		{
			Mesh::Lights[i].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		f.RenderText("Testing text", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });

		//m_meshBox.Render(m_camera.GetProjection() * m_camera.GetView());
		/*m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView());*/
		glfwSwapBuffers(win);
		glfwPollEvents();
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(win) == 0);

	//m_meshLight.Cleanup();
	//m_meshBox.Cleanup();

	for (size_t i = 0; i < m_meshBoxes.size(); ++i)
	{
		m_meshBoxes[i].Cleanup();
	}
	for (size_t i = 0; i < Mesh::Lights.size(); ++i)
	{
		Mesh::Lights[i].Cleanup();
	}
	//m_skybox.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderSkybox.Cleanup();
}
