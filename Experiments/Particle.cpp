#include "Particle.hpp"

void Particle::s_nope(Particle* lthis, double dt)
{
	
}

Particle::Particle() {
	el = RectangleShape(Vector2f(8, 8));
	el.setOrigin(-4, -4);
	el.setFillColor(sf::Color(0xff0000ff));
	life = Dice::randF() * 6.0f + 2.0f * 6.0f;
	bhv = s_nope;
	el.rotate(1);
}
