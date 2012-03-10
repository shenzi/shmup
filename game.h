#ifndef GAME_H
#define GAME_H

#include <list>
#include "logic.h"
#include "aircraft.h"
#include <SFML/Audio.hpp>

class Game
{
public:
	Game(sf::RenderWindow*);
	~Game();

	void logic(void);
	void show(void);

private:
	sf::RenderWindow* m_app;
	bool m_hit; 
	bool m_keys_states[sf::Keyboard::KeyCount];
	bool m_gameover;
	int m_nb_missile;
	int m_hp;
	sf::Sprite m_map, m_background_gameover;
	sf::Texture m_texture_map, m_texture_gameover;
	sf::Clock m_clock, m_clock_hit, m_clock_enemy_moves, m_clock_enemy_bullets;
	sf::Event m_event;
	sf::Uint32 m_time_last_bullet;
	sf::Sprite* m_J1;
	ResourcesManager* m_resources;
	sf::Text m_hp_text, m_missile_text, m_gameover_text;
	sf::Music m_theme;

	std::list<sf::Sprite> m_friendly_bullets;
	std::list<sf::Sprite> m_enemy_bullets;
	std::vector<Aircraft> m_aircrafts;

	void initMapAndAircrafts(void);
	void eventsHandling(void);
	void showHUD(void);
	void showBullets(void);
	void newGame(void);
};

#endif










