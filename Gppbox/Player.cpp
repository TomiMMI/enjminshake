#pragma once

#include "Player.hpp"
#include "Game.hpp"
#include "C.hpp"

#include <iostream>

Player::Player(float x, float y, std::string textpath) : Entity(x, y, textpath) {
}

Player::Player(float x, float y) : Entity(x,y){

}

Player::Player() {

}

void Player::MoveX(int x) {
	this->XMovementValue= x;
}
void Player::Jump() {
	if (isOnGround) {
		dy += -25;
		isOnGround = false;
	}
}

void Player::Update(double dt) {
	this->dx += XMovementValue * speed;
	this->xr += this->dx * dt;

		while (xr > 1) {
			if (Game::Instance->isWall(cx + 1, cy)) {
				this->xr = 0.9;
				this->dx = 0;
				break;
			}
			else {
				this->cx++;
				this->xr -= 1.0;
			}
		}


		while (xr <= 0) {
			if (Game::Instance->isWall(cx - 1, cy)) {
				this->xr = 0.1;
				this->dx = 0;
				break;
			}
			else {
				this->cx--;
				this->xr += 1;
			}
		}

	this->dy += 45.0f * dt;
	this->yr += this->dy * dt;

		while (yr < 0) {
			if (Game::Instance->isWall(cx, cy - 1)) {
				this->yr = 0.7;
				this->dy = 0;
				break;
			}
			else {
				this->cy--;
				this->yr += 1.0;
			}
		}


		while (yr >= 1) {
			if (Game::Instance->isWall(cx, cy + 1)) {
				this->yr = 0.7;
				this->dy = 0;
				break;
			}
			else {
				this->cy++;
				this->yr -= 1.0;
			}
		}

		if (xr > 0.9 && Game::Instance->isWall(cx + 1, cy)) {
			xr = 0.9;
			dx = 0;
		}
		else if (xr < 0.1 && Game::Instance->isWall(cx - 1, cy)) {
			xr = 0.1;
			dx = 0;
		}
		if (yr < 0.1 && Game::Instance->isWall(cx, cy - 1)) {
			yr = 0.1;
			dy = 0;
		}
		else if (yr > 0.9 && Game::Instance->isWall(cx , cy + 1)) {
			yr = 0.9;
			isOnGround = true;
			dy = 0;
		}
		if (debug) std::cout << "Player position | cx : " << cx << " xr : " << xr << " | cy :" << cy << " yr : " << yr << endl;
	dx *= 0.97;
	XMovementValue = 0;
	setCoordinates(cx, xr, cy, yr);
		}
