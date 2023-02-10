#ifndef BOSS_HPP
#define BOSS_HPP
#include "Enemy.hpp"
//sK@>
static const Shape boss_shape_up =	{ new chtype[3]{'<','A', '>'}, 3 };
static const Shape boss_shape_down =  { new chtype[3]{'<','V','>'}, 3 };
static const Shape boss_shape_left =  { new chtype[3]{'<','@', 'K'}, 3 };
static const Shape boss_shape_right = { new chtype[3]{'K','@', '>'}, 3 };
static constexpr int boss_hp = 250;
static constexpr int boss_wait = 30;
static constexpr int boss_speed = 9;
static constexpr int boss_xp = 500;

class Boss : public Enemy {
protected:
	void attack(DIRECTION);

	const Prj_Type* projectile_;

	bool shoot_;

public:
	void update() override;

	void move2(DIRECTION);

	Boss(Location* spawn, Player* ref, const Prj_Type* projectile);
};
#endif