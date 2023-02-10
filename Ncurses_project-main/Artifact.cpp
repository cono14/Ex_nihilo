#include "Artifact.hpp"
#include "Entity_List.hpp"
#include "Player.hpp"


void Artf_Type::use_skill(Player* e) const {
	if (f != nullptr) {
		f(e);

		if (duration != NO_DURATION)
			e->start_duration_timer();
		else e->start_recharge_timer();
	}
}


void Artifact::update() {
	if (!held_) Entity::update();
	else {
		wipe_shape();
		location_->r->list->remove(key);
	}
}


void Artifact::handle_collision(COLLISION t, int k) {
	if (t == COLLISION::PLAYER) {
		held_ = true;
		wipe_shape(false);
	}
}


Artifact::Artifact(const Artf_Type* t, Location* l)
: Entity{ t->shape, l, COLLISION::ARTIFACT }, t_{ t }, held_{ false }
{}


void Skills::dash(Player* e) {
	const DIRECTION d = e->get_direction();
	const int range = d == DIRECTION::RIGHT || d == DIRECTION::LEFT ? dash_range : dash_range/2;
	for (int i = 0; i < range; i++)
		e->move(d);
}


void Skills::armor(Player* e) {
	e->set_armor();
}


void Skills::bow(Player* e) {
	if (e->get_shape()->shape[1] == '<') {
		Location* loc = e->get_location();
		new Projectile{ &arrow[0], DIRECTION::LEFT, e, COLLISION::PROJECTILE, new Location{ loc->L, loc->y, loc->x - 4 } };
	}

	if (e->get_shape()->shape[1] == '>')
		new Projectile{ &arrow[1], DIRECTION::RIGHT, e };
}