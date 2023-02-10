#ifndef SPECIAL_ROOM_HPP
#define SPECIAL_ROOM_HPP
#include "Room.hpp"

class Special_Room : public Room {
public:
	Special_Room(Level* lvl, int x, int y);
}; typedef Special_Room* p_special_room;
#endif