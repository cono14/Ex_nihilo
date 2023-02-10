#include "Dynamic_Entity.hpp"
#include "Entity_List.hpp"
#include "Timer.hpp"


void Dynamic_Entity::update() {
	move_timer->update();

	if (!is_alive()) {
		location_->r->list->remove(key);
		wipe_shape();
	} else {
		if (!has_moved_) {
			current_direction_ = DIRECTION::STILL;
			*prev_loc_ = *location_;
		} Entity::update();
	}
}


void Dynamic_Entity::handle_collision(COLLISION t, int k) {
	if (t!=COLLISION::OBSTACLE) { // Se è uno scontro con un'altra entità
		for (int x = location_->x; x < location_->x + shape_->length; x++)
			mvwaddch(location_->r->win, location_->y, x, ' ');

		Location* tmp = location_;
		location_ = prev_loc_;
		prev_loc_ = tmp;

		init_prev();
	} else {
		// Ripristina le serie di celle in cui e' avvenuta la collisione.
		mvwaddchnstr(location_->r->win, location_->y, location_->x, prev_shape_, shape_->length);

		// Scambia la posizione corrente con la precedente.
		Location* tmp = location_;
		location_ = prev_loc_;
		prev_loc_ = tmp;

		// Re-inizializza prev_shape_
		init_prev();
	}
}


void Dynamic_Entity::move(DIRECTION d) {
	if (d != DIRECTION::STILL) {
		if (speed_ == 0 || speed_ > 0 && move_timer->wait()) {
			*prev_loc_ = *location_;
			wipe_shape();

			switch (d) {
			case DIRECTION::UP:		location_->y--; break;
			case DIRECTION::DOWN:	location_->y++; break;
			case DIRECTION::RIGHT:	location_->x++; break;
			case DIRECTION::LEFT:	location_->x--; break;
			} init_prev();
		} has_moved_ = true;
		current_direction_ = d;

	} else has_moved_ = false;
}


bool Dynamic_Entity::is_alive() {
	return hp_ > 0;
}


void Dynamic_Entity::increase_hp(int hp) {
	hp_ += hp; heal_hp += hp;
	if (hp_ > max_hp_) hp_ = max_hp_;
	if (heal_hp > max_hp_) heal_hp = max_hp_;
}


void Dynamic_Entity::decrease_hp(int dmg) {
	hp_ -= dmg; lost_hp += dmg;
}


DIRECTION Dynamic_Entity::get_direction() const {
	return current_direction_;
}


Dynamic_Entity::Dynamic_Entity(const Shape* s, Location* spawn, COLLISION t, int hp, int speed)
: Entity{ s,spawn,t }, hp_ { hp }, max_hp_{ hp }, has_moved_{ false }, speed_{ speed },
current_direction_{ DIRECTION::STILL }, lost_hp{ 0 }, heal_hp{ 0 }, move_timer{ new Timer{speed} }
{ move_timer->start(); }


Dynamic_Entity::~Dynamic_Entity()
{ delete move_timer; }