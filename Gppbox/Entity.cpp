#pragma once

#include "Entity.hpp"
#include "C.hpp"
#include <imgui-SFML.h>

Entity::Entity(float x, float y,std::string textpath) {
	this->sprite = sf::RectangleShape(sf::Vector2f(C::GRID_SIZE, C::GRID_SIZE * 2));

	if (!this->texture.loadFromFile(textpath)) {
		printf("Texture :", textpath, "could not be loaded.");
	}
	else {
		this->sprite.setTexture(&texture);
	}
	this->sprite.setOrigin(0, texture.getSize().y);
	this->setCoordinates(x, y);
}

Entity::Entity() {
	this->sprite = sf::RectangleShape(sf::Vector2f(C::GRID_SIZE, C::GRID_SIZE * 2));

	if (!this->texture.loadFromFile("res/player.png")) {
		printf("Texture :", "res/player.png", "could not be loaded.");
	}
	else {
		this->sprite.setTexture(&texture);
	}
	this->sprite.setOrigin(0, sprite.getSize().y);
	this->setCoordinates(200, 200);
};
Entity::Entity(float x, float y) {
	this->sprite = sf::RectangleShape(sf::Vector2f(C::GRID_SIZE, C::GRID_SIZE * 2));

	if (!this->texture.loadFromFile("res/player.png")) {
		printf("Texture :", "res/player.png", "could not be loaded.");
	}
	else {
		this->sprite.setTexture(&texture);
	}
	this->sprite.setOrigin(0, sprite.getSize().y);
	this->setCoordinates(x, y);

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

void Entity::setCoordinates(int cx, float xr, int cy, float yr) {
	this->xx = (cx  + xr) * (float)C::GRID_SIZE;
	this->yy = (cy  + yr) * (float)C::GRID_SIZE;
	this->sprite.setPosition(xx, yy);}

void Entity::Update(double dt) {
};