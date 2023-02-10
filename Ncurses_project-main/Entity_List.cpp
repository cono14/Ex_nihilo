#include "Entity_List.hpp"
#include "Entity.hpp"
#include <iostream>


void Entity_List::update() const {
	if (list_ != nullptr) {
		check_collisions();
		for (auto tmp = list_; tmp != nullptr; tmp = tmp->next)
			tmp->entity->update();
	}
}


Entity* Entity_List::search(int key) const {
	if (key==-1) return nullptr;
	for (auto tmp = list_; tmp != nullptr; tmp = tmp->next)
		if (tmp->entity->key == key)
			return tmp->entity;
	return nullptr;
}


void Entity_List::insert(Entity* e) {
	if (e) {
		if (list_ == nullptr) list_ = new Node{ e };
		else {
			list_->prev = new Node{ e, list_, nullptr };
			list_ = list_->prev;
		}

		if (e->type == COLLISION::ENEMY)
			enemy_count++;
		sz++;
	}
}


void Entity_List::remove(int key) {
	for (auto tmp = list_; tmp != nullptr; tmp = tmp->next)
		if (tmp->entity->key == key) {
			if (tmp->entity->type == COLLISION::ENEMY)
				enemy_count--;
			if (tmp->prev == nullptr) { // case head
				if (tmp->next == nullptr) { // case only element;
					list_ = nullptr;
				}
				else {
					list_ = list_->next;
					list_->prev = nullptr;
				}
			} else { // generic case
				tmp->prev->next = tmp->next;
				if (tmp->next) tmp->next->prev = tmp->prev;
			} sz--;
		} 
}


Entity_List::Entity_List()
: list_{ nullptr }, enemy_count{ 0 }, sz{ 0 }
{}


Entity_List::~Entity_List() {
	delete list_;
}


void Entity_List::check_collisions() const {
	auto collision_list = new Entity_List{};
	for (auto tmp = list_; tmp != nullptr; tmp = tmp->next)
		if (tmp->entity->get_shape() != nullptr)
			collision_list->insert(tmp->entity);

	for (auto p = collision_list->list_; p != nullptr; p = p->next) {
		for (auto s = p->next; s != nullptr; s = s->next)
			if (p->entity->check_collisions(s->entity)) {

				p->entity->handle_collision(s->entity->type, s->entity->key);
				s->entity->handle_collision(p->entity->type, p->entity->key);

				collision_list->remove(p->entity->key);
				collision_list->remove(s->entity->key);
			}
	}

	for (auto tmp = collision_list->list_; tmp != nullptr; tmp = tmp->next)
		if (tmp->entity->check_collisions())
			tmp->entity->handle_collision(COLLISION::OBSTACLE, -1);
}

int Entity_List::enemies() const {
	return enemy_count;
}

int Entity_List::size() const {
	return sz;
}