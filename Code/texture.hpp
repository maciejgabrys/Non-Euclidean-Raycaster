#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "main.hpp"

class Texture
{
public:
	const int width;
	const int height;
	sf::Color** data;
	Texture(int width, int height);
	Texture(int width, int height, std::initializer_list<std::initializer_list<uint32_t>> pixels);
	~Texture();
};

extern Texture red_wall_texture;
extern Texture blue_wall_texture;
extern Texture green_wall_texture;
extern Texture yellow_wall_texture;

#endif /* TEXTURE_HPP_ */
