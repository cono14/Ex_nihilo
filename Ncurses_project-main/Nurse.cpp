#include "Nurse.hpp"
#include <cmath>
#include <ctime>


DIRECTION Nurse::select_direction() {
    int h_distance = abs(location_->x - player->get_location()->x);
    int v_distance = abs(location_->y - player->get_location()->y);

    if (h_distance > v_distance) {
        if (location_->x >= player->get_location()->x) return DIRECTION::LEFT;
        else return DIRECTION::RIGHT;
    }
    else if (h_distance < v_distance) {
        if (location_->y >= player->get_location()->y) return DIRECTION::UP;
        else return DIRECTION::DOWN;
    }
    else {
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
}


void Nurse::attack(DIRECTION d) {

    int h_distance = abs(location_->x - player->get_location()->x);
    int v_distance = abs(location_->y - player->get_location()->y);

    srand(time(0));
    int perc = (rand() % 100) + 1;
    if (perc >= wait) {  //non attacca sempre

        switch (current_direction_) //attacca se il player si avvicina
        {
        case DIRECTION::LEFT:
        case DIRECTION::RIGHT:
            if (h_distance <= 9) new Projectile{ projectile_, d, this };
            break;
        case DIRECTION::DOWN:
        case DIRECTION::UP:
            if (v_distance <= 9) new Projectile{ projectile_, d, this };
            break;
        default:
            break;
        }
    }
}


Nurse::Nurse(Location* spawn, Player* ref, const Prj_Type* prj)
: Enemy{ "Nurse", nurse_xp ,&nurse_shape, spawn, nurse_hp, nurse_wait, ref}, projectile_{prj}
{}