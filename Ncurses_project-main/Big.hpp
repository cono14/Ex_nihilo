#ifndef BIGP_HPP
#define BIG_HPP
#include "Enemy.hpp"

static const Shape big_shape = { new chtype[3]{'+','T', '+'}, 3 };
static constexpr int big_hp = 120;
static constexpr int big_speed = 9;
static constexpr int big_wait = 20;
static constexpr int big_xp = 85;

class Big : public Enemy {
public:
	void update() override;

	Big(Location* spawn, Player* ref);
};
#endif