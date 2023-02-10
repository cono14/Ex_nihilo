#ifndef BOSS_ROOM_HPP
#define BOSS_ROOM_HPP
#include "Room.hpp"

class Boss_Room : public Room {
public:
	Boss_Room(Level* lvl, int x, int y);
}; typedef Boss_Room* p_boss_room;
#endif