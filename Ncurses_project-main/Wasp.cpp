#include "Wasp.hpp"


void Wasp::update() {
	Enemy::update();
	move(select_direction());
}


Wasp::Wasp(Location* spawn, Player* ref)
: Enemy{ "Wasp", wasp_xp, &wasp_shape, spawn, wasp_hp, wasp_wait, ref, wasp_speed}
{}