#include "Bomb.hpp"
#include "Player.hpp"
#include "Timer.hpp"

void Bomb::update() {
	timer->update();
	if (timer->wait()) 
		explode();
	Dynamic_Entity::update();
}


void Bomb::handle_collision(COLLISION t, int hit_key) {
	Dynamic_Entity::handle_collision(t, hit_key);
}


Bomb::Bomb(Dynamic_Entity* ref)
: Projectile{ &bomb_type, ref->get_direction(), ref, COLLISION::OBSTACLE },
timer{ new Timer{sec*2} }
{ timer->start(); }


Bomb::~Bomb()
{ delete timer; }


void Bomb::explode() {
	for (int i = location_->y - 1; i <= location_->y + 1; i++)
		for (int j = location_->x - 2; j <= location_->x + 2; j++) {
			Location* tmp = new Location{ location_->L, location_->r->y_cor, location_->r->x_cor, i, j };
			new Explosion{ tmp, this };
		}
	hp_ = 0;
}