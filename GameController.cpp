#include "GameController.h"

GameController::GameController()
{
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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

}

void GameController::RunGame()
{
	m_mesh = Mesh();
	m_mesh.Create();

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do {
		glClear(GL_COLOR_BUFFER_BIT);
		m_mesh.Render();
		glfwSwapBuffers(win);
		glfwPollEvents();
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(win) == 0);
}
