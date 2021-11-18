#include "texture.hpp"

Texture::Texture(int width, int height) :
	width(width),
	height(height)
{
	data = new sf::Color*[height];
	for (int i = 0; i < height; i++) {
		data[i] = new sf::Color[width];
	}
}

Texture::Texture(int width, int height, std::initializer_list<std::initializer_list<uint32_t>> pixels) :
	Texture::Texture(width, height)
{
	int y = 0;
	for (auto row : pixels) {
		int x = 0;
		for (uint32_t color : row) {
			data[y][x] = sf::Color(color);
			x++;
		}
		y++;
	}
}

Texture::~Texture()
{
	for (int i = 0; i < height; i++) {
		delete[] data[i];
	}
	delete[] data;
}

static const uint32_t K1 = 0x800000FF;
static const uint32_t W1 = 0xFFE6CCFF;
static const uint32_t R1 = 0xCC3300FF;

static const uint32_t K2 = 0x003399FF;
static const uint32_t W2 = 0xC6D9ECFF;
static const uint32_t R2 = 0x0066CCFF;

static const uint32_t K3 = 0x008000FF;
static const uint32_t W3 = 0xE6FFCCFF;
static const uint32_t R3 = 0x33CC00FF;

static const uint32_t K4 = 0xCCA300FF;
static const uint32_t W4 = 0xFFFF99FF;
static const uint32_t R4 = 0xFFDB4DFF;

Texture red_wall_texture(9, 10, {
	{ K1, K1, K1, K1, K1, K1, K1, K1, K1 },
	{ R1, R1, R1, R1, R1, R1, W1, R1, R1 },
	{ R1, R1, R1, R1, R1, R1, W1, R1, R1 },
	{ W1, W1, W1, W1, W1, W1, W1, W1, W1 },
	{ R1, R1, W1, R1, R1, R1, R1, R1, R1 },
	{ R1, R1, W1, R1, R1, R1, R1, R1, R1 },
	{ W1, W1, W1, W1, W1, W1, W1, W1, W1 },
	{ R1, R1, R1, R1, R1, R1, W1, R1, R1 },
	{ R1, R1, R1, R1, R1, R1, W1, R1, R1 },
	{ K1, K1, K1, K1, K1, K1, K1, K1, K1 }
});

Texture blue_wall_texture(9, 10, {
	{ K2, K2, K2, K2, K2, K2, K2, K2, K2 },
	{ R2, R2, R2, R2, R2, R2, W2, R2, R2 },
	{ R2, R2, R2, R2, R2, R2, W2, R2, R2 },
	{ W2, W2, W2, W2, W2, W2, W2, W2, W2 },
	{ R2, R2, W2, R2, R2, R2, R2, R2, R2 },
	{ R2, R2, W2, R2, R2, R2, R2, R2, R2 },
	{ W2, W2, W2, W2, W2, W2, W2, W2, W2 },
	{ R2, R2, R2, R2, R2, R2, W2, R2, R2 },
	{ R2, R2, R2, R2, R2, R2, W2, R2, R2 },
	{ K2, K2, K2, K2, K2, K2, K2, K2, K2 }
});

Texture green_wall_texture(9, 10, {
	{ K3, K3, K3, K3, K3, K3, K3, K3, K3 },
	{ R3, R3, R3, R3, R3, R3, W3, R3, R3 },
	{ R3, R3, R3, R3, R3, R3, W3, R3, R3 },
	{ W3, W3, W3, W3, W3, W3, W3, W3, W3 },
	{ R3, R3, W3, R3, R3, R3, R3, R3, R3 },
	{ R3, R3, W3, R3, R3, R3, R3, R3, R3 },
	{ W3, W3, W3, W3, W3, W3, W3, W3, W3 },
	{ R3, R3, R3, R3, R3, R3, W3, R3, R3 },
	{ R3, R3, R3, R3, R3, R3, W3, R3, R3 },
	{ K3, K3, K3, K3, K3, K3, K3, K3, K3 }
});

Texture yellow_wall_texture(9, 10, {
	{ K4, K4, K4, K4, K4, K4, K4, K4, K4 },
	{ R4, R4, R4, R4, R4, R4, W4, R4, R4 },
	{ R4, R4, R4, R4, R4, R4, W4, R4, R4 },
	{ W4, W4, W4, W4, W4, W4, W4, W4, W4 },
	{ R4, R4, W4, R4, R4, R4, R4, R4, R4 },
	{ R4, R4, W4, R4, R4, R4, R4, R4, R4 },
	{ W4, W4, W4, W4, W4, W4, W4, W4, W4 },
	{ R4, R4, R4, R4, R4, R4, W4, R4, R4 },
	{ R4, R4, R4, R4, R4, R4, W4, R4, R4 },
	{ K4, K4, K4, K4, K4, K4, K4, K4, K4 }
});
