#ifndef TURRET_HPP
#define TURRET_HPP
#include "Enemy.hpp"

static const Shape turret_shape_up =	{ new chtype[3]{'}','^','{'}, 3 };
static const Shape turret_shape_down =  { new chtype[3]{'}','v','{'}, 3 };
static const Shape turret_shape_left =  { new chtype[3]{'}','<','{'}, 3 };
static const Shape turret_shape_right = { new chtype[3]{'}','>','{'}, 3 };
static constexpr int turret_hp = 30;
static constexpr int turret_wait = 100;
static constexpr int turret_speed = 10;
static constexpr int turret_xp = 75;

class Turret : public Enemy {
protected:
	void attack(DIRECTION);

	const Prj_Type* projectile_;

	bool shoot_;

public:
	void update() override;

	void move(DIRECTION) override;

	Turret(Location* spawn, Player* ref, const Prj_Type* projectile);
};
#endif