#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = {};
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
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

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
	

	for (size_t i = 0; i < 4; ++i)
	{
		Mesh m = Mesh();
		m.Create(&m_shaderColor);
		m.SetPosition({ 0.5f + (float)i / 10.0f, 0.0f, -0.5f });
		m.SetColor({ glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f) });
		m.SetScale({ 0.1f, 0.1f, 0.1f });
		Mesh::Lights.push_back(m);
	}



	for (int i = 0; i < 10; ++i)
	{
		for (size_t j = 0; j < 10; ++j)
		{
			Mesh box = Mesh();
			box.Create(&m_shaderDiffuse);
			box.SetCameraPosition(m_camera.GetPosition());
			box.SetScale({ 0.1f, 0.1f, 0.1f });
			// box.SetPosition({ glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f) });
		
			box.SetPosition({ 0.0f, -0.5f + (float)j / 10.0f, -0.2f + (float)i / 10.0f });
			m_meshBoxes.push_back(box);
		}
	}

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do {
		/*System::Windows::Forms::Application::DoEvents();*/

		//GLint loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderRedChannel");
		//glUniform1i(loc, (int)InitOpenGL::ToolWindow::RenderRedChannel);

		//loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderGreenChannel");
		//glUniform1i(loc, (int)InitOpenGL::ToolWindow::RenderGreenChannel);
		//
		//loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderBlueChannel");
		//glUniform1i(loc, (int)InitOpenGL::ToolWindow::RenderBlueChannel);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (size_t i = 0; i < m_meshBoxes.size(); ++i)
		{
			m_meshBoxes[i].Render(m_camera.GetProjection() * m_camera.GetView());
		}		
		for (size_t i = 0; i < Mesh::Lights.size(); ++i)
		{
			Mesh::Lights[i].Render(m_camera.GetProjection() * m_camera.GetView());
		}

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
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
}
