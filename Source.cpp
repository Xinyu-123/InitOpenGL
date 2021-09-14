#include "GameController.h"

int main(void) {
	GameController::GetInstance().Initalize();
	GameController::GetInstance().RunGame();
}