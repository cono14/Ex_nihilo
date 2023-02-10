#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Player.hpp"

class Enemy : public Dynamic_Entity {
protected:
	int wait;

	Player* player;

	void knockback(int range);

	virtual DIRECTION select_direction();

public:
	void update() override;

	void handle_collision(COLLISION, int) override;

	Enemy(const char* name, int xp, const Shape*, Location*, int hp, int wait, Player* ref, int speed=0);

	const char* const name;

	const int xp;
};
#endif