#pragma once

#include "Entity.hpp"

class Player : public Entity {

private:
	int XMovementValue;
	float maxDx = 200;
	float maxDy = 200;

	float speed = 0.7;

public:
	bool isOnGround = false;
	Player(float x, float y, std::string textpath);
	Player();
	void MoveX(int x);
	void Jump();
	void Update(double dt);

};