#include "main.hpp"
#include "node.hpp"
#include "player.hpp"
#include "renderer.hpp"

Player* temporaryMapLoader();

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(scr_width * scr_scale, scr_height * scr_scale), "Rejkaster");
	window.setVerticalSyncEnabled(true);

	sf::Image image;
	image.create(scr_width, scr_height);
	sf::Texture texture;
	texture.create(scr_width, scr_height);
	texture.update(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition({ 0.0, 0.0 });
	sprite.setScale({ scr_scale, scr_scale });

	Player* player = temporaryMapLoader();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		double rotate = 0.0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			rotate += 0.04;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			rotate -= 0.04;
		}
		player->rotate(rotate);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player->move(Direction::up, 0.05);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player->move(Direction::down, 0.05);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player->move(Direction::left, 0.05);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player->move(Direction::right, 0.05);
		}

		window.clear();
		render(image, player);
		texture.update(image);
		window.draw(sprite);
		window.display();
	}

	return 0;
}

Player* temporaryMapLoader()
{
	std::vector<std::string> txt = {
//    0+ 0123456789
//   10+           0123456789
//   20+                     0123456789
		"..............x...............", // 0
		"..............x...............", // 1
		"..............x.BBBBBBBBBBBBB.", // 2
		"......RRR.....x.B...........B.", // 3
		"......RRR.....x.B...........B.", // 4
		"......R.R.....x.B..Y..Y..Y..B.", // 5
		"..............x.B...........B.", // 6
		"..............x.B...........B.", // 7
		"..............x.B..Y.....Y..B.", // 8
		"..............x.B...........B.", // 9
		"...GGG.GGG....x.B...........B.", // 10
		"...GG...GG....x.BBBBBB.BBBBBB.", // 11
		"...G.....G....x...............", // 12
		"...GGGGGGG....x...............", // 13
		"..............x...............", // 14
		"..............x..............."  // 15
	};

	std::vector<std::vector<Node*>> map(16);
	for (int h = 0; h <= 15; h++) {
		map[h].resize(30, nullptr);
	}

	for (int h = 0; h <= 15; h++) {
		for (int w = 0; w <= 29; w++) {
			switch (txt[h][w]) {
			case '.':
			case 'x':
				map[h][w] = new Floor;
				break;
			case 'R':
				map[h][w] = new RedWall;
				break;
			case 'B':
				map[h][w] = new BlueWall;
				break;
			case 'G':
				map[h][w] = new GreenWall;
				break;
			case 'Y':
				map[h][w] = new YellowWall;
				break;
			}
		}
	}

	for (int h = 0; h <= 15; h++) {
		for (int w = 0; w <= 29; w++) {
			if (txt[h][w] == '.') {
				if (h > 0 && txt[h - 1][w] != 'x') map[h][w]->addNeighbour(Direction::up, map[h - 1][w]);
				if (h < 15 && txt[h + 1][w] != 'x') map[h][w]->addNeighbour(Direction::down, map[h + 1][w]);
				if (w > 0 && txt[h][w - 1] != 'x') map[h][w]->addNeighbour(Direction::left, map[h][w - 1]);
				if (w < 29 && txt[h][w + 1] != 'x') map[h][w]->addNeighbour(Direction::right, map[h][w + 1]);
			}
		}
	}

	map[5][7]->removeNeighbour(Direction::up);
	map[5][7]->addNeighbour(Direction::up, map[11][22]);

	map[11][22]->removeNeighbour(Direction::down);
	map[11][22]->addNeighbour(Direction::down, map[5][7]);

	map[12][4]->removeNeighbour(Direction::left);
	map[12][4]->addNeighbour(Direction::left, map[12][8]);

	map[12][8]->removeNeighbour(Direction::right);
	map[12][8]->addNeighbour(Direction::right, map[12][4]);

	Position pos;
	pos.node = map[8][4];
	pos.offset = 0.5 + 0.5i;
	pos.angle = 0.9;
	Player* player = new Player(pos);

	return player;
}
