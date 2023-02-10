#ifndef NURSE_HPP
#define NURSE_HPP
#include "Enemy.hpp"

static const Shape nurse_shape = { new chtype[2] {'a','a'}, 2}; // Caratteri temporanei
static constexpr int nurse_hp =    20;
static constexpr int nurse_wait =  50; 
static constexpr int nurse_speed = 1;
static constexpr int nurse_xp = 100;

class Nurse : public Enemy {
protected:
	DIRECTION select_direction() override;

	void get_heal(int heal_range);

	void attack(DIRECTION);

	const Prj_Type* projectile_;

public:
	Nurse(Location* spawn, Player* ref, const Prj_Type* prj);
};
#endif