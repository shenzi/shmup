#include "aircraft.h"

Aircraft::Aircraft(ResourcesManager* resources) : m_hp(100), m_hit(false), m_vx(3), m_vy(2)
{
	m_resources = resources;
	m_type = MOB1;
	m_spr = *m_resources->getSprite(m_type);
}

Aircraft::~Aircraft()
{

}

void Aircraft::SetPosition(float x, float y)
{
	m_spr.SetPosition(x, y);
}

void Aircraft::setType(int aircraft_type)
{
	m_type = aircraft_type;
}

const sf::Vector2f& Aircraft::GetPosition(void) const
{
	return m_spr.GetPosition();
}

const sf::IntRect& Aircraft::GetSubRect(void) const
{
	return m_spr.GetTextureRect();
}

void Aircraft::draw(sf::RenderWindow* app)
{
	sf::Sprite xplode = *(m_resources->getSprite(XPLODE1));
	xplode.SetPosition(m_spr.GetPosition());

	app->Draw(m_spr);

	m_time = m_clock.GetElapsedTime().AsMilliseconds();
	if (m_hit)
	{
		app->Draw(xplode);

		if (m_time > 100)
			m_hit = false;
	}
}

void Aircraft::hit(int weapon)
{
	m_clock.Restart();

	if (weapon > 24)
		m_hp -= 20;

	else
		m_hp -= 10;

	m_hit = true;
}

int Aircraft::hp(void) const
{
	return m_hp;
}

void Aircraft::move(void)
{
	m_spr.Move(m_vx, m_vy);
}

int Aircraft::vx(void) const
{
	return m_vx;
}

int Aircraft::vy(void) const
{
	return m_vy;
}

void Aircraft::inverseVX(void)
{
	m_vx *= -1;
}

void Aircraft::inverseVY(void)
{
	m_vy *= -1;
}


