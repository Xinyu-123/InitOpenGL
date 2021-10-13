#include "GameController.h"


int main(void) {

	GameController::GetInstance().Initalize();
	GameController::GetInstance().RunGame();
 
	// Questions for week 6?
	// * Binding the texture and the OpenGl State Machine
	// * How to not hard code the File Extensions
	// * How the Fragment shader output values get interpreted
	// * winding order of the index buffer, and is that graphics api specific?
}