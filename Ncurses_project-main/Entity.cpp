#include "Entity.hpp"
#include "Entity_List.hpp"


void Entity::update() {
	if (location_ && shape_)
		mvwaddchnstr(location_->r->win, location_->y, location_->x, shape_->shape, shape_->length);
}


bool Entity::check_collisions(const Entity* e) const {
	bool collision_found = false;
	if (shape_ && location_) {
		if (e == nullptr) {
			for (int i = 0; i < shape_->length && !collision_found; i++)
				if (prev_shape_[i] != ' ')
					collision_found = true;
		}
		else if (e->shape_ && e->get_location() && location_->y == e->get_location()->y) {
			for (int x = location_->x; x < location_->x + shape_->length && !collision_found; x++)
				for (int e_x = e->get_location()->x; e_x < e->get_location()->x + e->get_shape()->length; e_x++)
					if (x == e_x)
						collision_found = true;
		}
	} return collision_found;
}


Location* Entity::get_location() const {
	return location_;
}


const Shape* Entity::get_shape() const {
	return shape_;
}


bool Entity::is_empty(chtype* s, int len) {
	for (int i = 0; i < len; i++)
		if (s[i] != ' ') return false;
	return true;
}


Entity::Entity(const Shape* s, Location* spawn, COLLISION t)
: key{ key_val++ }, type{ t }, shape_{ s }, location_{ spawn }
{
	if (spawn != nullptr) {
		prev_loc_ = new Location{ spawn->L, spawn->r->y_cor, spawn->r->x_cor, spawn->y, spawn->x };
		prev_shape_ = new chtype[shape_->length]; init_prev();
		location_->r->list->insert(this);
	} else {
		prev_loc_ = nullptr; prev_shape_ = nullptr;
	}
}


Entity::~Entity() {
	delete[] prev_shape_;
	delete prev_loc_;
}


void Entity::wipe_shape(bool restore) {
	if (shape_ && location_) {
		for (int x = location_->x, i = 0; x < location_->x + shape_->length; x++, i++)
			mvwaddch(location_->r->win, location_->y, x, restore ? prev_shape_[i] : ' ');
	}
}


void Entity::init_prev() const {
	if (prev_shape_ && location_)
		for (int i = 0, x = location_->x; i < shape_->length; i++, x++)
			prev_shape_[i] = mvwinch(location_->r->win, location_->y, x);
}


int Entity::key_val = 0;


DIRECTION operator-(DIRECTION d) {
	switch (d) {
	case DIRECTION::UP:
		return DIRECTION::DOWN;
	case DIRECTION::DOWN:
		return DIRECTION::UP;
	case DIRECTION::LEFT:
		return DIRECTION::RIGHT;
	case DIRECTION::RIGHT:
		return DIRECTION::LEFT;
	case DIRECTION::STILL:
		return DIRECTION::STILL;
	}
}