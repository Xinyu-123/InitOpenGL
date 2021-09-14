#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Mesh.h"
#include "WindowController.h"

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
};

#endif //GAME_CONTROLLER_H

