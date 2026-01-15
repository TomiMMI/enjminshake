#pragma once
#include "SFML/Graphics.hpp"

class Entity {

public:
	sf::Texture texture;
	sf::RectangleShape sprite;

	int cx;
	int cy;
	float xr;
	float yr;

	float xx;
	float yy;

	float dx;
	float dy;

	Entity(float x, float y, std::string textpath);
	Entity(float x, float y);
	Entity();

	void setCoordinates(float x, float y);
	void setCoordinates(int cx, float xr, int cy, float xy);

	virtual void Update(double dt);
};