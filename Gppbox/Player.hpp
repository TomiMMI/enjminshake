#pragma once

#include "Entity.hpp"

class Player : public Entity {

private:
	int XMovementValue;

	float speed = 0.7;

public:
	bool debug = false;
	bool isOnGround = false;
	Player(float x, float y, std::string textpath);
	Player(float x, float y);
	Player();
	void MoveX(int x);
	void Jump();
	void Update(double dt);

};