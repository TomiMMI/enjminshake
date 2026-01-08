#pragma once
#include "SFML/Graphics.hpp"

class Entity {

public:
	sf::Texture texture;
	sf::Sprite sprite;

	int cx;
	int cy;
	float xr;
	float yr;

	float xx;
	float yy;

	float dx;
	float dy;

	Entity(float x, float y, std::string textpath);
	Entity();

	void setCoordinates(float x, float y);

	virtual void Update(double dt);
};