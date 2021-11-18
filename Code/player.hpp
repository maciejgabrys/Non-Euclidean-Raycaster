#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "main.hpp"
#include "node.hpp"

struct Position
{
	Node* node;
	std::complex<double> offset;
	double angle;
};

class Player
{
private:
	Position position;
public:
	Player(Position position);
	void setPosition(Position new_position);
	Position getPosition();
	void rotate(double angle_offset);
	void move(Direction direction, double distance);
	~Player();
};

#endif /* PLAYER_HPP_ */
