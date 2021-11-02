#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
GameController::GameController()
{
	m_shader = {};
	m_camera = {};
	m_mesh = {};
}

GameController::~GameController()
{
}

void GameController::Initalize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT((glewInit() == GLEW_OK), "Failed to initalize GLEW");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	//InitOpenGL::ToolWindow^ window = gcnew InitOpenGL::ToolWindow();
	//window->Show();
	//System::Windows::Forms::Application::Run(window);
	m_shader = Shader();
	m_shader.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_mesh = Mesh();
	m_mesh.Create(&m_shader);


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
		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(win);
		glfwPollEvents();
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(win) == 0);

	m_mesh.Cleanup();
	m_shader.Cleanup();
}
