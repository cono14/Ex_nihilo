#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP
#include "Dynamic_Entity.hpp"

static const Shape explosion_shape{ new chtype[1]{'#'}, 1 };
static constexpr int explosion_dmg = 20;

class Explosion : public Dynamic_Entity {
public:
	void update() override;

	Explosion(Location* spawn, Entity* spawner);

	~Explosion() override;

	Entity* const ref;
private:
	void handle_collision(COLLISION, int) override;

	Timer* timer;
};
#endif