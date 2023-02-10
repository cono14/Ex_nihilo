#include <cstdlib>
#include <ctime>
#include "Enemy.hpp"
#include "Entity_List.hpp"


void Enemy::update() {
    if (!is_alive() && player!=nullptr)
        player->gain_xp(xp);
    Dynamic_Entity::update();
}


void Enemy::handle_collision(COLLISION t, int hit_key) {
	switch(t) {
	case COLLISION::PROJECTILE: {
		const auto prj = dynamic_cast<Projectile*>(location_->r->list->search(hit_key));
		if (prj != nullptr && prj->spawner_ == player)
			decrease_hp(prj->t->damage);
        knockback(1);
		break;
	}
    case COLLISION::PLAYER: {
        Dynamic_Entity::handle_collision(t, hit_key);
        knockback(3);

        break;
    }
	default:
		Dynamic_Entity::handle_collision(t, hit_key);
		break;
	}
}


DIRECTION Enemy::select_direction() {
    srand(time(0));
    int perc = (rand() % 100);
    if (perc >= wait) {
        int h_distance = abs(location_->x - player->get_location()->x);
        int v_distance = abs(location_->y - player->get_location()->y);

        if (h_distance > v_distance) {
            if (location_->x >= player->get_location()->x) return DIRECTION::LEFT;
            else return DIRECTION::RIGHT;
        }
        else if (h_distance < v_distance) {
            if (location_->y >= player->get_location()->y) return DIRECTION::UP;
            else return DIRECTION::DOWN;
        } else {
        	int tmp = rand() % 2;
            if (tmp == 0) {
                if (location_->x >= player->get_location()->x) return DIRECTION::LEFT;
                else return DIRECTION::RIGHT;
            }
            else {
                if (location_->y >= player->get_location()->y) return DIRECTION::UP;
                else return DIRECTION::DOWN;
            }
        }
    } return DIRECTION::STILL;
}


void Enemy::knockback(int range) {
    for (int i = 0; i < range; i++) { // Knockback
        *prev_loc_ = *location_;
        wipe_shape();
        switch (current_direction_) {
        case DIRECTION::UP:    location_->y++;  break;
        case DIRECTION::DOWN:  location_->y--;  break;
        case DIRECTION::LEFT:  location_->x++;  break;
        case DIRECTION::RIGHT: location_->x--;  break;
        } init_prev();
    }
}


Enemy::Enemy(const char* name, int xp, const Shape* s, Location* l, int hp, int wait, Player* ref, int speed)
: Dynamic_Entity{ s, l, COLLISION::ENEMY, hp, speed }, name{ name }, xp{ xp }
{
    this->wait = wait;
    player = ref;
}