#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#define GLM_ENABLE_EXPERIMENTAL


// standard includes
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) {OutputDebugStringA(_msg); std::abort(); glfwTerminate();}
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Font includes
#define generic GenericFromFreeTypeLibrary
#include <ft2build.h>
#include FT_FREETYPE_H
#undef generic

#include "Resolution.h"
#include "Singleton.h"

using namespace std;


#endif // STANDARD_INCLUDES_H