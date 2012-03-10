#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "resources.h"

class Aircraft
{
public:
	Aircraft(ResourcesManager*);
	~Aircraft();

	void setType(int);
	void SetPosition(float, float);
	const sf::Vector2f& GetPosition(void) const;
	const sf::IntRect& GetSubRect(void) const;

	void draw(sf::RenderWindow*);
	void hit(int);
	int hp(void) const;
	void move(void);
	int vx(void) const;
	int vy(void) const;
	void inverseVX(void);
	void inverseVY(void);

private:
	sf::Sprite m_spr;
	ResourcesManager* m_resources;
	int m_type;
	int m_hp;
	bool m_hit;
	sf::Clock m_clock;
	sf::Uint32 m_time;
	int m_vx;
	int m_vy;
};

#endif

