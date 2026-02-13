/// <Summary>
/// BLEAK VISION - BUAS ASSIGNMENT PROJECT
/// Micha³ Rapciak
/// Estimated Time:
/// Time Spent:
/// 06/02/2026 - 7 Hours
/// 07/02/2026 - 6 hours
/// 09/02/2026 - 7 hours
/// 10/02/2026 - 12 hours
/// 11/02/2026 - 8 hours
/// 12/02/2026 - 14 hours
/// 13/02/2026 - 3 hours
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-s-d.lib") 
#pragma comment(lib,"sfml-audio-s-d.lib") 
#pragma comment(lib,"sfml-system-s-d.lib") 
#pragma comment(lib,"sfml-window-s-d.lib") 
#pragma comment(lib,"sfml-network-s-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics-s.lib") 
#pragma comment(lib,"sfml-audio-s.lib") 
#pragma comment(lib,"sfml-system-s.lib")
#pragma comment(lib,"sfml-window-s.lib") 
#pragma comment(lib,"sfml-network-s.lib") 
#endif 

#include "Game.h"

int main() // Entry Point to "Game", if 1 = success
{
	Game game;
	game.run();

	return 1;
}