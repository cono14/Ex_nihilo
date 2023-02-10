#include "Button.hpp"
#include "Player.hpp"


void Button::update() {
	if (!pressed_) Entity::update();
}


void Button::handle_collision(COLLISION t, int) {
	if (t == COLLISION::PLAYER && !pressed_) {
		pressed_ = true;

		int xx = start_x, yy = start_y;
		for (int i = 0; i < len; i++)
			mvwaddch(location_->r->win, vertical ? yy++ : yy, vertical ? xx : xx++, ' ');
	}
}


Button::Button(Location* spawn, int l, bool vert, int y, int x)
	: Entity{ &button_shape, spawn, COLLISION::BUTTON }, len{ l }, vertical{ vert },
	start_x{ x }, start_y{ y }, pressed_{ false }
{};