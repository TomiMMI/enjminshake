#pragma once

#include "Entity.hpp"
#include "C.hpp"
#include <imgui-SFML.h>

Entity::Entity(float x, float y,std::string textpath) {
	if (!this->texture.loadFromFile(textpath)) {
		printf("Texture :", textpath, "could not be loaded.");
	}
	else {
		this->sprite = sf::Sprite(texture);
	}
	this->setCoordinates(x, y);
}
Entity::Entity() {
	if (!this->texture.loadFromFile("res/images.jpg")) {
		printf("Texture :", "res/images.jpg", "could not be loaded.");
	}
	else {
		this->sprite = sf::Sprite(texture);
	}
	this->setCoordinates(200, 200);
};
void Entity::setCoordinates(float x, float y) {
	this->xx = x;
	this->yy = y;
	this->cx = (int)x / C::GRID_SIZE;
	this->cy = (int)y / C::GRID_SIZE;
	this->xr = (xx - cx * 16) / C::GRID_SIZE;
	this->yr = (yy - cy * 16) / C::GRID_SIZE;
	this->sprite.setPosition(x, y);
}
void Entity::Update(double dt) {
	this->xx += 10 * dt;
	this->sprite.setPosition(xx, yy);
};