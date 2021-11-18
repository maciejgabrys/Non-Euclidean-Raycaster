#include "node.hpp"

const double render_distance = 64.0;

Node::Node(bool wall, Texture* texture) :
	wall(wall),
	texture(texture),
	neighbours{ nullptr, nullptr, nullptr, nullptr }
{
}

void Node::removeNeighbour(Direction direction)
{
	neighbours[(size_t)direction] = nullptr;
}

void Node::addNeighbour(Direction direction, Node* neighbour)
{
	neighbours[(size_t)direction] = neighbour;
}

Node* Node::getNeighbour(Direction direction)
{
	return neighbours[(size_t)direction];
}

bool Node::isWall()
{
	return wall;
}

Texture* Node::getTexture()
{
	return texture;
}

std::pair<Node*, double> Node::castRay(std::complex<double> start, double angle, double distance_so_far, double* tx_offset)
{
	if (wall) {
		// Ray has hit the wall.
		if (start.real() == 0.0) *tx_offset = 1.0 - start.imag();
		if (start.real() == 1.0) *tx_offset = start.imag();
		if (start.imag() == 0.0) *tx_offset = start.real();
		if (start.imag() == 1.0) *tx_offset = 1.0 - start.real();
		return { this, distance_so_far };
	} else { 
		// Ray is going thru this node.
		double fi1 = fmod(std::arg((1.0 + 1.0i) - start) + 2.0 * M_PI, 2.0 * M_PI);
		double fi2 = fmod(std::arg((0.0 + 1.0i) - start) + 2.0 * M_PI, 2.0 * M_PI);
		double fi3 = fmod(std::arg((0.0 + 0.0i) - start) + 2.0 * M_PI, 2.0 * M_PI);
		double fi4 = fmod(std::arg((1.0 + 0.0i) - start) + 2.0 * M_PI, 2.0 * M_PI);

		std::complex<double> new_start;
		double d = 0.0;
		Node* neighbour = nullptr;

		if (angle >= fi1 && angle <= fi2) {
			// Up:
			double h = 1.0 - start.imag();
			double e = h / tan(angle);
			d = h / sin(angle);
			new_start = std::complex<double>(start.real() + e, 0.0);
			neighbour = getNeighbour(Direction::up);
		} else if (angle >= fi2 && angle <= fi3) {
			// Left:
			double h = start.real();
			double e = h * tan(angle);
			d = -(h / cos(angle));
			new_start = std::complex<double>(1.0, start.imag() - e);
			neighbour = getNeighbour(Direction::left);
		} else if (angle >= fi3 && angle <= fi4) {
			// Down:
			double h = start.imag();
			double e = h / tan(angle);
			d = -(h / sin(angle));
			new_start = std::complex<double>(start.real() - e, 1.0);
			neighbour = getNeighbour(Direction::down);
		} else {
			// Right:
			double h = 1.0 - start.real();
			double e = h * tan(angle);
			d = h / cos(angle);
			new_start = std::complex<double>(0.0, start.imag() + e);
			neighbour = getNeighbour(Direction::right);
		}

		double new_distance_so_far = distance_so_far + d;

		if (neighbour == nullptr || new_distance_so_far > render_distance) {
			return { nullptr, -1.0 };
		} else {
			return neighbour->castRay(new_start, angle, new_distance_so_far, tx_offset);
		}

	}
}

Node::~Node()
{
}
