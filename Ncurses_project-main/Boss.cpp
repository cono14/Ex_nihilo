#include "Boss.hpp"
#include "Timer.hpp"

void Boss::update() {
     srand(unsigned(time(0)));
    int xx = rand() % 3;
    if(xx==0){
        if(!shoot_) 
     move2(current_direction_);
    else attack(select_direction());}
    
    if(!shoot_) move(select_direction());
    
    
    Enemy::update();
}


void Boss::move2(DIRECTION d) {
    has_moved_ = true;
    if (d != DIRECTION::STILL) {
        if (move_timer->wait()) {
            shoot_ = true;

            switch (current_direction_) {
            case DIRECTION::UP:
                current_direction_ = DIRECTION::LEFT;
                shape_ = &boss_shape_left;
                break;
            case DIRECTION::DOWN:
                current_direction_ = DIRECTION::RIGHT;
                shape_ = &boss_shape_right;
                break;
            case DIRECTION::LEFT:
                current_direction_ = DIRECTION::DOWN;
                shape_ = &boss_shape_down;
                break;
            case DIRECTION::RIGHT:
                current_direction_ = DIRECTION::UP;
                shape_ = &boss_shape_up;
                break;
            default:
                break;
            }
        }
    }
};


void Boss::attack(DIRECTION d) {
    if (d != DIRECTION::STILL) {
   auto x = new Projectile{ projectile_, d, this, COLLISION::PROJECTILE };
   shoot_ = false;
}};


Boss::Boss(Location* spawn, Player* ref, const Prj_Type* projectile)
: Enemy{ "Boss", boss_xp, &boss_shape_down, spawn, boss_hp, boss_wait, ref, boss_speed},
projectile_{projectile}, shoot_{false}
{ current_direction_ = DIRECTION::DOWN; }