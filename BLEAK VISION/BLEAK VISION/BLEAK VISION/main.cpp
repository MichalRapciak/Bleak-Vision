/// <Summary>
/// BLEAK VISION - BUAS ASSIGNMENT PROJECT
/// Micha³ Rapciak
/// Estimated Time:
/// Time Spent:
/// 06/02/2026 - 7 Hours
/// 07/02/2026 - 6 hours
/// 09/02/2026 - 7 hours
/// 10/02/2026 - 12 hours
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include "Game.h"

int main() // Entry Point to "Game", if 1 = success
{
	Game game;
	game.run();

	return 1;
}