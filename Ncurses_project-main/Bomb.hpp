#ifndef BOMB_HPP
#define BOMB_HPP
#include "Projectile.hpp"
#include "Explosion.hpp"
class Dynamic_Entity;
class Timer;

static const Shape bomb_shape{ new chtype{'Q'}, 1 };
static constexpr int bomb_dmg = 4; // Placeholder

// NOTA: il parametro 'dmg' e' a 0 poiche' la bomba in se' non danneggia,
// e' l'esplosione a farlo.
static constexpr Prj_Type bomb_type{ "Bomb", &bomb_shape, 0, 1, 0};

class Bomb : public Projectile {
public:
	void update() override;

	void handle_collision(COLLISION, int) override;

	Bomb(Dynamic_Entity* reference);

	~Bomb() override;

private:
	void explode();

	Timer* timer;
};
#endif