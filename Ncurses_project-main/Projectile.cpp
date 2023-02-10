#include <exception>
#include <iostream>
#include "Projectile.hpp"
#include "Explosion.hpp"


void Projectile::update() {
	switch (current_direction_) {
	case DIRECTION::UP:
	case DIRECTION::DOWN:
		if (strcmp(t->name, "Boomerang") == 0 && moves_ == t->range / 4 - 1)
			current_direction_ = -current_direction_;
		if (moves_ >= t->range / 2 - 1) hp_ = 0;
		break;
	case DIRECTION::LEFT:
	case DIRECTION::RIGHT:
		if (strcmp(t->name, "Boomerang") == 0 && moves_ == t->range/2 - 1)
			current_direction_ = -current_direction_;
		if (moves_ >= t->range) hp_ = 0;
		break;
	case DIRECTION::STILL:
		hp_ = 0;
		break;
	}

	if (is_alive()) {
		move(current_direction_);
		moves_++;
	} else if (!is_alive() && strcmp(t->name, "Explosive") == 0) {
		for (int i = location_->x - 1, j = location_->y - 1; i <= location_->x + 1 && j <= location_->y + 1; i++, j++)
			new Explosion{ new Location{location_->L, j, i}, this };
		for (int i = location_->x + 1, j = location_->y - 1; i >= location_->x - 1 && j <= location_->y + 1; i--, j++)
			new Explosion{ new Location{location_->L, j, i}, this };
	}

	Dynamic_Entity::update();
}


void Projectile::handle_collision(COLLISION type, int hit_key) {
	if (type != COLLISION::BUTTON) {
		Dynamic_Entity::handle_collision(type, hit_key);
		if (strcmp(t->name, "Boomerang") != 0)
			hp_ = 0;
		else if (type!=COLLISION::PLAYER) switch (current_direction_) {
		case DIRECTION::UP:	   location_->y -= 2;	break;
		case DIRECTION::DOWN:  location_->y += 2;	break;
		case DIRECTION::LEFT:  location_->x -= 2;	break;
		case DIRECTION::RIGHT: location_->x += 2;	break;
		case DIRECTION::STILL: break;
		} 
	}
}


Projectile::Projectile(const Prj_Type* type, DIRECTION d, Entity* ref, COLLISION c_type, Location* loc)
: Dynamic_Entity{ type->shape, loc==nullptr ? init_location(d,ref) : loc, c_type, 1 },
spawner_{ ref }, t{ type }, moves_{ 0 }
{ current_direction_ = d; }


Location* Projectile::init_location(DIRECTION d, Entity* e) {
	const Location* loc = e->get_location();
	const int len = e->get_shape()->length;

	try {
		switch (d) {
		case DIRECTION::UP:
			return new Location
			{ loc->L, loc->L->cur_y, loc->L->cur_x, loc->y - 1, loc->x + len / 2 };
		case DIRECTION::DOWN:
			return new Location
			{ loc->L, loc->L->cur_y, loc->L->cur_x, loc->y + 1, loc->x + len / 2 };
		case DIRECTION::LEFT:
			return new Location
			{ loc->L, loc->L->cur_y, loc->L->cur_x, loc->y, loc->x - 1 };
		case DIRECTION::RIGHT:
			return new Location
			{ loc->L, loc->L->cur_y, loc->L->cur_x, loc->y, loc->x + len };
		default:
			throw std::exception{};
		}
	} catch (std::exception& err) {
		std::cout << "Errore nella generazione del proiettile" << std::endl;
		return nullptr;
	}
}