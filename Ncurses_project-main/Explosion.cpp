#include "Explosion.hpp"
#include "Timer.hpp"


void Explosion::update() {
	timer->update();
	if (timer->wait())
		hp_ = 0;
	Dynamic_Entity::update();
}


void Explosion::handle_collision(COLLISION t, int k) {
	if (t == COLLISION::OBSTACLE && (prev_shape_[0] == '#' || prev_shape_[0] == 'Q')) {
		hp_ = 0;
		prev_shape_[0] = ' ';
	} else {
		Dynamic_Entity::handle_collision(t, k);
		hp_ = 0;
	}
}


Explosion::Explosion(Location* spawn, Entity* spawner)
: Dynamic_Entity{ &explosion_shape, spawn, COLLISION::EXPLOSION, 1 }, ref{ spawner },
timer{ new Timer{sec/8} }
{ timer->start(); }


Explosion::~Explosion() {
	delete timer;
}