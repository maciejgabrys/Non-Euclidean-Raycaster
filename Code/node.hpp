#ifndef NODE_HPP_
#define NODE_HPP_

#include "main.hpp"
#include "texture.hpp"

enum class Direction
{
	right = 0,
	up = 1,
	left = 2,
	down = 3
};

class Node
{
private:
	bool wall;
	Texture* texture;
	Node* neighbours[4];
public:
	Node(bool wall, Texture* texture = nullptr);
	void removeNeighbour(Direction direction);
	void addNeighbour(Direction direction, Node* neighbour);
	Node* getNeighbour(Direction direction);
	bool isWall();
	Texture* getTexture();
	std::pair<Node*, double> castRay(std::complex<double> start, double angle, double distance_so_far, double* tx_offset);
	virtual ~Node() = 0;
};

class Floor : public Node
{
public:
	Floor() : Node(false, nullptr) {}
	~Floor() {}
};

class RedWall : public Node
{
public:
	RedWall() : Node(true, &red_wall_texture) {}
	~RedWall() {}
};

class BlueWall : public Node
{
public:
	BlueWall() : Node(true, &blue_wall_texture) {}
	~BlueWall() {}
};

class GreenWall : public Node
{
public:
	GreenWall() : Node(true, &green_wall_texture) {}
	~GreenWall() {}
};

class YellowWall : public Node
{
public:
	YellowWall() : Node(true, &yellow_wall_texture) {}
	~YellowWall() {}
};

#endif /* NODE_HPP_ */
