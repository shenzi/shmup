#include "game.h"
#include <sstream>

Game::Game(sf::RenderWindow* app) : m_app(app), m_nb_missile(10), m_hp(100), m_hit(false), m_gameover(false)
{
	for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
		m_keys_states[i] = false;

	m_theme.OpenFromFile("resources/sounds/the_stage_is_set.ogg");
	m_theme.Play();
	m_theme.SetLoop(true);

	m_clock_enemy_moves.Restart();
	m_clock_enemy_bullets.Restart();
	m_resources = new ResourcesManager;
	m_hp_text.SetCharacterSize(18);
	m_missile_text.SetCharacterSize(18);
	m_gameover_text.SetCharacterSize(18);
	m_gameover_text.SetPosition(20, 20);
	m_gameover_text.SetString("NEW GAME : [ENTER]");
	m_texture_gameover.LoadFromFile("resources/gameover.jpg");
	m_background_gameover.SetTexture(m_texture_gameover);
	m_background_gameover.SetPosition(m_app->GetWidth()/2 - m_background_gameover.GetTextureRect().Width/2, m_app->GetHeight()/2 - m_background_gameover.GetTextureRect().Height/2);

	this->initMapAndAircrafts();
}

Game::~Game()
{
	delete m_resources;
}

void Game::newGame(void)
{
	m_gameover = false;
	m_hp = 100;
	m_nb_missile = 10;

	m_enemy_bullets.clear();
	m_friendly_bullets.clear();
	m_aircrafts.clear();
	m_aircrafts.resize(2, m_resources);

	for (int i = 0; i < 2; ++i)
	{
		m_aircrafts[i].setType(MOB1);
		m_aircrafts[i].SetPosition((m_app->GetWidth() / 4)*i+50, 10);
	}

	m_J1->SetPosition(m_app->GetWidth() / 2 - (m_J1->GetTextureRect().Width / 2), m_app->GetHeight() - m_J1->GetTextureRect().Height - 15);
}

void Game::initMapAndAircrafts(void)
{
	m_texture_map.LoadFromFile("resources/map.jpg");
	m_map.SetTexture(m_texture_map);

	m_J1 = m_resources->getSprite(J1);
	m_J1->SetPosition(m_app->GetWidth() / 2 - (m_J1->GetTextureRect().Width / 2), m_app->GetHeight() - m_J1->GetTextureRect().Height - 15);

	m_aircrafts.resize(2, m_resources);

	for (int i = 0; i < 2; ++i)
	{
		m_aircrafts[i].setType(MOB1);
		m_aircrafts[i].SetPosition((m_app->GetWidth() / 4)*i+50, 10);
	}
}

void Game::eventsHandling(void)
{
	while (m_app->PollEvent(m_event))
	{
		if (m_event.Type == m_event.KeyPressed)
		{
			m_keys_states[m_event.Key.Code] = true;
		}

		if (m_event.Type == m_event.KeyReleased)
		{
			m_keys_states[m_event.Key.Code] = false;
		}
	}

	if (m_event.Key.Code == sf::Keyboard::Escape)
		m_app->Close();

	if (m_event.Type == m_event.Closed)
		m_app->Close();

	if (!m_gameover)
	{
		if (m_keys_states[sf::Keyboard::Z])
		{
			if (m_J1->GetPosition().y >= m_J1->GetTextureRect().Height + 35)
				m_J1->Move(0, -6);
		}

		if (m_keys_states[sf::Keyboard::S])
		{
			if (m_J1->GetPosition().y <= m_app->GetHeight() - m_J1->GetTextureRect().Height)
				m_J1->Move(0, 6);
		}

		if (m_keys_states[sf::Keyboard::Q])
		{
			if (m_J1->GetPosition().x >= 0)
				m_J1->Move(-6, 0);
		}

		if (m_keys_states[sf::Keyboard::D])
		{
			if (m_J1->GetPosition().x + m_J1->GetTextureRect().Width <= m_app->GetWidth())
				m_J1->Move(6, 0);
		}

		if (m_keys_states[sf::Keyboard::Up] || m_keys_states[sf::Keyboard::Down])
		{
			m_time_last_bullet = m_clock.GetElapsedTime().AsMilliseconds();

			if (m_time_last_bullet >= 100)
			{
				if (m_keys_states[sf::Keyboard::Down] && m_nb_missile > 0)
				{
					addFriendlyBullet(MISSILE2, m_J1, m_friendly_bullets, m_resources);
					--m_nb_missile;
				}

				if (m_keys_states[sf::Keyboard::Up])
					addFriendlyBullet(WEAPON1, m_J1, m_friendly_bullets, m_resources);

				m_clock.Restart();
			}
		}
	}

	if (m_keys_states[sf::Keyboard::Return] && m_gameover)
		newGame();
}

void Game::logic(void)
{
	eventsHandling();

	if (!m_gameover)
	{
		if (m_aircrafts.empty())
		{
			int n = (rand() % 4) + 1;

			m_aircrafts.resize(n, m_resources);

			for (int i = 0; i < n; ++i)
			{
				m_aircrafts[i].setType(MOB1);
				m_aircrafts[i].SetPosition((m_app->GetWidth() / 4)*i+50, 10);
			}
		}

		collide(m_friendly_bullets, m_aircrafts, &m_nb_missile);
		AI(m_enemy_bullets, m_aircrafts, m_J1, m_resources, m_clock_enemy_bullets, m_clock_enemy_moves);

		if (collide(m_enemy_bullets, m_J1))
		{
			m_hit = true;
			m_clock_hit.Restart();
			m_hp -= 10;
		}
	}

	if (m_hp <= 0)
		m_gameover = true;
}

void Game::show(void)
{
	m_app->Clear();

	if (!m_gameover)
	{
		m_app->Draw(m_map);

		for (int i = 0; i < m_aircrafts.size(); ++i)
			m_aircrafts[i].draw(m_app);

		showBullets();
		showHUD();

		float time_hit = m_clock_hit.GetElapsedTime().AsMilliseconds();
		if (m_hit)
		{
			sf::Sprite xplode = *(m_resources->getSprite(XPLODE1));
			xplode.SetPosition(m_J1->GetPosition());
			m_app->Draw(xplode);

			if (time_hit > 100)
				m_hit = false;
		}

		m_app->Draw(*m_J1);
	}

	else
	{
		m_app->Draw(m_background_gameover);
		m_app->Draw(m_gameover_text);
	}

	m_app->Display();
}

void Game::showBullets(void)
{
	for (std::list<sf::Sprite>::iterator i = m_friendly_bullets.begin(); i != m_friendly_bullets.end(); ++i)
	{
		if (isInsideScreen((*i).GetPosition(), m_app))
			m_app->Draw(*i);

		else
			i = m_friendly_bullets.erase(i);

		if (i == m_friendly_bullets.end())
			break;
	}

	for (std::list<sf::Sprite>::iterator i = m_enemy_bullets.begin(); i != m_enemy_bullets.end(); ++i)
	{
		if (isInsideScreen((*i).GetPosition(), m_app))
			m_app->Draw(*i);

		else
			i = m_enemy_bullets.erase(i);

		if (i == m_enemy_bullets.end())
			break;
	}
}

void Game::showHUD(void)
{
	std::ostringstream oss1, oss2;
	sf::String s1, s2;

	oss1 << m_nb_missile;
	oss2 << m_hp;
	s1 = "AVAILABLE MISSILES : " + oss1.str();
	m_missile_text.SetString(s1);
	m_missile_text.SetPosition(10, m_app->GetHeight() - m_hp_text.GetGlobalBounds().Height - 10);
	s2 = "HP (" + oss2.str() + ")";
	m_hp_text.SetString(s2);
	m_hp_text.SetPosition(m_app->GetWidth() - m_hp_text.GetGlobalBounds().Width - 10, m_app->GetHeight() - m_hp_text.GetGlobalBounds().Height - 10);

	m_app->Draw(m_hp_text);
	m_app->Draw(m_missile_text);
}








