#include "Secret_Room.hpp"

Secret_Room::Secret_Room(Level* lvl, int x, int y)
: Room{lvl, x, y, 1}
{
	for (int i = 0; i < 30; i++)
        mvwaddstr(win, i, 0, mappa_secret[i]);
}
