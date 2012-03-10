#include "resources.h"

ResourcesManager::ResourcesManager()
{
	this->loadTextures();

	m_sprites.resize(TEXTURE_SIZE);

	for (int i = 0; i < (TEXTURE_SIZE - 1); ++i)
		m_sprites[i].SetTexture(m_textures[i]);
}

ResourcesManager::~ResourcesManager()
{

}

void ResourcesManager::loadTextures(void)
{
	std::vector<sf::Image> tmp_images;
	tmp_images.resize(TEXTURE_SIZE);
	m_textures.resize(TEXTURE_SIZE);

	tmp_images[J1].LoadFromFile("resources/aircrafts/J1.bmp");
	tmp_images[BOSS1].LoadFromFile("resources/aircrafts/BOSS1.PNG");
	tmp_images[BOSS2].LoadFromFile("resources/aircrafts/BOSS2.PNG");
	tmp_images[BOSS3].LoadFromFile("resources/aircrafts/BOSS3.PNG");
	tmp_images[BOSS4].LoadFromFile("resources/aircrafts/BOSS4.PNG");
	tmp_images[MOB1].LoadFromFile("resources/aircrafts/MOB1.png");
	tmp_images[MOB2].LoadFromFile("resources/aircrafts/MOB2.png");
	tmp_images[MOB3].LoadFromFile("resources/aircrafts/MOB3.png");
	tmp_images[MOB4].LoadFromFile("resources/aircrafts/MOB4.png");
	tmp_images[WEAPON1].LoadFromFile("resources/bullets/WEAPON1.png");
	tmp_images[WEAPON2].LoadFromFile("resources/bullets/WEAPON2.png");
	tmp_images[WEAPON3].LoadFromFile("resources/bullets/WEAPON3.png");
	tmp_images[WEAPON4].LoadFromFile("resources/bullets/WEAPON4.png");
	tmp_images[WEAPON_MOB1].LoadFromFile("resources/bullets/WEAPON_MOB1.png");
	tmp_images[WEAPON_MOB2].LoadFromFile("resources/bullets/WEAPON_MOB2.png");
	tmp_images[WEAPON_MOB3].LoadFromFile("resources/bullets/WEAPON_MOB3.png");
	tmp_images[WEAPON_MOB4].LoadFromFile("resources/bullets/WEAPON_MOB4.png");
	tmp_images[MISSILE1].LoadFromFile("resources/bullets/MISSILE1.png");
	tmp_images[MISSILE2].LoadFromFile("resources/bullets/MISSILE2.png");
	tmp_images[MISSILE3].LoadFromFile("resources/bullets/MISSILE3.png");
	tmp_images[MISSILE4].LoadFromFile("resources/bullets/MISSILE4.png");
	tmp_images[XPLODE1].LoadFromFile("resources/fx/XPLODE1.png");
	tmp_images[XPLODE2].LoadFromFile("resources/fx/XPLODE2.png");
	tmp_images[XPLODE3].LoadFromFile("resources/fx/XPLODE3.png");
	tmp_images[XPLODE4].LoadFromFile("resources/fx/XPLODE4.png");
	tmp_images[BONUS_ARMOR].LoadFromFile("resources/items/armor.png");
	tmp_images[BONUS_AMMUNITION_MISSILE].LoadFromFile("resources/items/ammunition.png");

	// transparency J1
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 50; j < 180; ++j)
		{
			tmp_images[MOB1].CreateMaskFromColor(sf::Color(i, j, j));
			tmp_images[J1].CreateMaskFromColor(sf::Color(i, j, j));
		}
	}

	tmp_images[MISSILE2].CreateMaskFromColor(sf::Color(0, 0, 0));
	tmp_images[XPLODE1].CreateMaskFromColor(sf::Color(255, 255, 255));

	for (int i = 0; i <= (TEXTURE_SIZE - 1); ++i)
		m_textures[i].LoadFromImage(tmp_images[i]);
}

sf::Texture* ResourcesManager::getTexture(int index)
{
	return &m_textures[index];
}

sf::Sprite* ResourcesManager::getSprite(int index)
{
	return &m_sprites[index];
}





