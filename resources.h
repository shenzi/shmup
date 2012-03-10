#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>
#include <SFML/Graphics.hpp>

enum
{
	J1, BOSS1, BOSS2, BOSS3, BOSS4, MOB1, MOB2, MOB3, MOB4,
	WEAPON1, WEAPON2, WEAPON3, WEAPON4, WEAPON_MOB1, WEAPON_MOB2, WEAPON_MOB3, WEAPON_MOB4,
	MISSILE1, MISSILE2, MISSILE3, MISSILE4,
	XPLODE1, XPLODE2, XPLODE3, XPLODE4,
	BONUS_ARMOR, BONUS_AMMUNITION_MISSILE, TEXTURE_SIZE
};

class ResourcesManager
{
public:
	ResourcesManager();
	~ResourcesManager();

	sf::Texture* getTexture(int);
	sf::Sprite* getSprite(int);

private:
	std::vector<sf::Texture> m_textures;
	std::vector<sf::Sprite> m_sprites;

	void loadTextures(void);
};

#endif




