#include "logic.h"
#include <cstdlib>

void collide(std::list<sf::Sprite>& friendly_bullets, std::vector<Aircraft>& aircrafts, int* nb_missile)
{
	for (std::list<sf::Sprite>::iterator i = friendly_bullets.begin(); i != friendly_bullets.end(); ++i)
	{
		(*i).Move(0, -8);

		for (std::vector<Aircraft>::iterator j = aircrafts.begin(); j != aircrafts.end(); ++j)
		{
			if (AABB((*j).GetPosition(), (*j).GetSubRect(), (*i).GetPosition(), (*i).GetTextureRect()))
			{
				(*j).hit((*i).GetTextureRect().Width);

				i = friendly_bullets.erase(i);

				if ((*j).hp() <= 0)
				{
					j = aircrafts.erase(j);
					*nb_missile += 5;
				}

				if (j == aircrafts.end())
					break;

				if (i == friendly_bullets.end())
					break;
			}
		}

		if (i == friendly_bullets.end())
			break;
	}
}

bool collide(std::list<sf::Sprite>& enemy_bullets, sf::Sprite* j1)
{
	for (std::list<sf::Sprite>::iterator i = enemy_bullets.begin(); i != enemy_bullets.end(); ++i)
	{
		(*i).Move(0, 6);

			if (AABB(j1->GetPosition(), j1->GetTextureRect(), (*i).GetPosition(), (*i).GetTextureRect()))
			{
				enemy_bullets.erase(i);
				return true;
			}
	}

	return false;
}

bool AABB(const sf::Vector2f pos_a, const sf::IntRect size_a, const sf::Vector2f pos_b, const sf::IntRect size_b)
{
	if ((pos_a.x >= pos_b.x + size_b.Width)
		|| (pos_a.x + size_a.Width <= pos_b.x)
		|| (pos_a.y + size_a.Height <= pos_b.y)
		|| (pos_a.y >= pos_b.y + size_b.Height))
	{
		return false;
	}

	return true;
}

bool isInsideScreen(const sf::Vector2f pos, sf::RenderWindow* app)
{
	if (pos.x >= app->GetWidth() || pos.y >= app->GetHeight() || pos.y <= 0)
		return false;

	return true;
}

void AI(std::list<sf::Sprite>& enemy_bullets, std::vector<Aircraft>& aircrafts, sf::Sprite* j1, ResourcesManager* resources, sf::Clock& clock_bullets, sf::Clock& clock_move)
{
	for (std::vector<Aircraft>::iterator i = aircrafts.begin(); i != aircrafts.end(); ++i)
	{
		sf::Uint32 time_bullets = clock_bullets.GetElapsedTime().AsMilliseconds();
		sf::Uint32 time_moves = clock_move.GetElapsedTime().AsMilliseconds();

		if ((*i).GetPosition().x >= j1->GetPosition().x && (*i).GetPosition().x <= (j1->GetPosition().x + j1->GetTextureRect().Width) && time_bullets > 200)
		{
			clock_bullets.Restart();
			addEnemyBullet(WEAPON_MOB1, i, enemy_bullets, resources);
		}

		if (time_moves > 1000)
		{
			clock_move.Restart();

			int nx = rand() % 21;
			int ny = rand() % 21;

			if (nx % 2 == 0)
				(*i).inverseVX();

			if (ny % 2 == 0)
				(*i).inverseVY();
		}

		if ((*i).GetPosition().x <= 0 || (*i).GetPosition().x + (*i).GetSubRect().Width > 1024)
			(*i).inverseVX();

		if ((*i).GetPosition().y <= 0 || (*i).GetPosition().y + (*i).GetSubRect().Height > 275)
			(*i).inverseVY();

		(*i).move();
	}
}

void addFriendlyBullet(int weapon_type, sf::Sprite* j1, std::list<sf::Sprite>& friendly_bullets, ResourcesManager* resources)
{
	sf::Sprite spr = *resources->getSprite(weapon_type);
	spr.SetPosition(j1->GetPosition().x + (j1->GetTextureRect().Width / 2 - spr.GetTextureRect().Width / 2), j1->GetPosition().y);
	friendly_bullets.push_back(spr);
}

void addEnemyBullet(int weapon_type, std::vector<Aircraft>::const_iterator i, std::list<sf::Sprite>& enemy_bullets, ResourcesManager* resources)
{
	sf::Sprite spr = *resources->getSprite(weapon_type);
	spr.SetPosition((*i).GetPosition().x + ((*i).GetSubRect().Width / 2 - spr.GetTextureRect().Width / 2), (*i).GetPosition().y);
	enemy_bullets.push_back(spr);
}


