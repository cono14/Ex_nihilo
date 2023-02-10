#include "Turret.hpp"
#include "Timer.hpp"

void Turret::update() {
    if (!shoot_) move(current_direction_);
    else attack(current_direction_);

    Enemy::update();
}


void Turret::move(DIRECTION d) {
    has_moved_ = true;
    if (d != DIRECTION::STILL) {
        if (move_timer->wait()) {
            shoot_ = true;

            switch (current_direction_) {
            case DIRECTION::UP:
                current_direction_ = DIRECTION::LEFT;
                shape_ = &turret_shape_left;
                break;
            case DIRECTION::DOWN:
                current_direction_ = DIRECTION::RIGHT;
                shape_ = &turret_shape_right;
                break;
            case DIRECTION::LEFT:
                current_direction_ = DIRECTION::DOWN;
                shape_ = &turret_shape_down;
                break;
            case DIRECTION::RIGHT:
                current_direction_ = DIRECTION::UP;
                shape_ = &turret_shape_up;
                break;
            default:
                break;
            }
        }
    }
}


void Turret::attack(DIRECTION d) {
   auto x = new Projectile{ projectile_, d, this, COLLISION::PROJECTILE };
   shoot_ = false;
}


Turret::Turret(Location* spawn, Player* ref, const Prj_Type* projectile)
: Enemy{ "Turret", turret_xp, &turret_shape_down, spawn, turret_hp, turret_wait, ref, turret_speed},
projectile_{projectile}, shoot_{false}
{ current_direction_ = DIRECTION::DOWN; }