#ifndef LOGIC_H
#define LOGIC_H

#include <list>

#include "aircraft.h"

void collide(std::list<sf::Sprite>&, std::vector<Aircraft>&, int*);
bool collide(std::list<sf::Sprite>&, sf::Sprite*);
bool AABB(const sf::Vector2f, const sf::IntRect, const sf::Vector2f, const sf::IntRect);
void AI(std::list<sf::Sprite>&, std::vector<Aircraft>&, sf::Sprite*, ResourcesManager*, sf::Clock&, sf::Clock&);
void addFriendlyBullet(int, sf::Sprite*, std::list<sf::Sprite>&, ResourcesManager*);
void addEnemyBullet(int, std::vector<Aircraft>::const_iterator, std::list<sf::Sprite>&, ResourcesManager*);
bool isInsideScreen(const sf::Vector2f, sf::RenderWindow*);

#endif



