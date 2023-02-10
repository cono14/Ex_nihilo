#include "Big.hpp"


void Big::update() {
	Enemy::update();
	move(select_direction());
}


Big::Big(Location* spawn, Player* ref)
: Enemy{ "Big", big_xp, &big_shape, spawn, big_hp, big_wait, ref, big_speed }
{}