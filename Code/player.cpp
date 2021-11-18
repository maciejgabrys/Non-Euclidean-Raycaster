#include "player.hpp"

Player::Player(Position position) :
	position(position)
{
}

void Player::setPosition(Position new_position)
{
	if (new_position.node == nullptr) {
		throw std::runtime_error("[" __FUNCTION__ "] New node was nullptr.");
	}
	if (new_position.offset.real() < 0.0 || new_position.offset.real() > 1.0 || new_position.offset.imag() < 0.0 || new_position.offset.imag() > 1.0) {
		throw std::runtime_error("[" __FUNCTION__ "] Position out of range.");
	}
	position = new_position;
}

Position Player::getPosition()
{
	return position;
}

void Player::rotate(double angle_offset)
{
	position.angle += angle_offset;
	position.angle = fmod(position.angle + 2.0 * M_PI, 2.0 * M_PI);
}

void Player::move(Direction direction, double distance)
{
	double angle_offset;
	switch (direction)
	{
	case Direction::right:
		angle_offset = -M_PI_2;
		break;
	case Direction::up:
		angle_offset = 0.0;
		break;
	case Direction::left:
		angle_offset = M_PI_2;
		break;
	case Direction::down:
		angle_offset = M_PI;
		break;
	}

	std::complex<double> new_position = position.offset + std::polar(distance, position.angle + angle_offset);

	// TODO: make player slide along walls when touching them
	Node* neighbour = nullptr;
	if (new_position.real() < 0.0) {
		neighbour = position.node->getNeighbour(Direction::left);
		new_position.real(fmod(new_position.real() + 1.0, 1.0));
		new_position.imag(position.offset.imag());
	} else if (new_position.real() > 1.0) {
		neighbour = position.node->getNeighbour(Direction::right);
		new_position.real(fmod(new_position.real() + 1.0, 1.0));
		new_position.imag(position.offset.imag());
	} else if (new_position.imag() < 0.0) {
		neighbour = position.node->getNeighbour(Direction::down);
		new_position.real(position.offset.real());
		new_position.imag(fmod(new_position.imag() + 1.0, 1.0));
	} else if (new_position.imag() > 1.0) {
		neighbour = position.node->getNeighbour(Direction::up);
		new_position.real(position.offset.real());
		new_position.imag(fmod(new_position.imag() + 1.0, 1.0));
	} else {
		position.offset = new_position;
	}
	if (neighbour != nullptr && !neighbour->isWall()) {
		position.node = neighbour;
		position.offset = new_position;
	}


}

Player::~Player()
{
}
