#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP
#include <curses.h>
#include "Player.hpp"

class Game_over {
protected:
 Player* player;

public:
    WINDOW* win;
    void update();
    Game_over(Player* player);
    void go_back();
};

#endif