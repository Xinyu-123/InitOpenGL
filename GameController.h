#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "SkyBox.h"
#include "Camera.h"

class GameController : public Singleton<GameController>
{
public:
	// Constructors / Destructors
	GameController();
	virtual ~GameController();

	// Methods
	void Initalize();
	void RunGame();

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	//Mesh m_meshBox;
	//Mesh m_meshLight;
	Camera m_camera;
	Shader m_shaderSkybox;
	vector<Mesh> m_meshBoxes;

	Shader m_shaderFont;

	SkyBox m_skybox;
	GLuint m_vao;

};

#endif //GAME_CONTROLLER_H

