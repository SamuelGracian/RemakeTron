#include "TronGame.h"

int main()
{
	Tron_Game& tron = Tron_Game::GetInstance();
	tron.Run_Game();

	return 0;
}