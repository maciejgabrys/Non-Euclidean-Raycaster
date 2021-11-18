#include "renderer.hpp"

const double fov_deg = 70.0;
const double fov_rad = fov_deg / 180.0 * M_PI;
const double depth = (double)scr_width / 2.0 / tan(fov_rad / 2.0);

const sf::Color color_ceiling(0xC3DBDBFF);
const sf::Color color_floor(0x98BB77FF);

void render(sf::Image& image, Player* player)
{
	// Draw ceiling and floor:
	for (int x = 0; x < scr_width; x++) {
		for (int y = 0; y < scr_height / 2; y++) {
			image.setPixel(x, y, color_ceiling);
		}
		for (int y = scr_height / 2; y < scr_height; y++) {
			image.setPixel(x, y, color_floor);
		}
	}

	Position pos = player->getPosition();

	// Draw walls:

	for (int x = 0; x < scr_width; x++) {

		double tan_val = (double)(scr_width / 2 - x) / depth;
		double ray_angle_offset = atan(tan_val);

		double ray_angle = fmod(pos.angle + ray_angle_offset + 2.0 * M_PI, 2.0 * M_PI);

		double tx_offset;
		std::pair<Node*, double> ray = pos.node->castRay(pos.offset, ray_angle, 0.0, &tx_offset);
		Node* wall = ray.first;
		double distance = ray.second;

		distance *= cos(ray_angle_offset); // remove fish eye effect

		if (wall == nullptr || wall->getTexture() == nullptr) {
			// Ray length exceeded render distance (or wall has no texture).
			continue;
		}
		double original_wall_height = ((double)scr_height / distance);
		int screen_wall_height = ((int)original_wall_height > scr_height) ? scr_height : (int)original_wall_height;
		for (int y = scr_height / 2 - screen_wall_height / 2; y < scr_height / 2 + screen_wall_height / 2; y++) {
			double ty = ((double)((double)y + 0.5 - (double)scr_height / 2) / original_wall_height) + 0.5;
			double tx = tx_offset;
			sf::Color color = wall->getTexture()->data[(size_t)(ty * wall->getTexture()->height)][(size_t)(tx * wall->getTexture()->width)];
			image.setPixel(x, y, color);
		}

	}




}


