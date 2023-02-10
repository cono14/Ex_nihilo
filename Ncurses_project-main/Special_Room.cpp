#include "Special_Room.hpp"


Special_Room::Special_Room(Level* lvl, int x, int y)
: Room{lvl, x, y, 2 }
{
	box(win, 63, 63);
}