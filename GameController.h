#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"

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
	Mesh m_mesh;
	Shader m_shader;
};

#endif //GAME_CONTROLLER_H

