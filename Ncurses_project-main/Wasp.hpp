#ifndef WASP_HPP
#define WASP_HPP
#include "Enemy.hpp"

static const Shape wasp_shape = { new chtype[3]{'>','8','<'}, 3 };
static constexpr int wasp_hp = 20;
static constexpr int wasp_speed = 5;
static constexpr int wasp_wait = 10;
static constexpr int wasp_xp = 50;

class Wasp : public Enemy {
public:
	void update() override;

	Wasp(Location* spawn, Player* ref);
};
#endif