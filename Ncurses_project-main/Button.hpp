#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "Entity.hpp"

static const Shape button_shape{ new chtype{'@'}, 1 };

class Button : public Entity {
public:
	void update() override;

	Button(Location* spawn, int l, bool vert, int y, int x);

private:
	void handle_collision(COLLISION, int) override;
	
	const int start_x;

	const int start_y;

	const bool vertical;
	
	const int len;

	bool pressed_;
};
#endif