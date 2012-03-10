#include "game.h"
#include <cstdlib>
#include <ctime>

int main(void)
{
	sf::RenderWindow app(sf::VideoMode(1024, 768), "shmup by Adrien GARIN - http://shenzi.alwaysdata.net", sf::Style::Close);

	app.EnableVerticalSync(true);
	app.EnableKeyRepeat(true);
	app.ShowMouseCursor(false);

	std::srand(static_cast<unsigned int>(std::time(0)));

	Game game(&app);

	while (app.IsOpen())
	{
		game.logic();
		game.show();
	}

	return 0;
}







