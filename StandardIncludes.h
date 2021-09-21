#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

// standard includes
#include <vector>
#include <string>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) {OutputDebugStringA(_msg); std::abort(); glfwTerminate();}
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Singleton.h"

using namespace std;


#endif // STANDARD_INCLUDES_H