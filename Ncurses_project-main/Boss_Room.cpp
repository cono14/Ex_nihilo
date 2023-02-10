#include "Boss_Room.hpp"

/*
  Costruttore: 
   La stanza del boss viene inizializzata come sottoclasse di 'Room'. Il costruttore prende:
   - Livello corrente.
   - Coordinate x e y dove posizionare la stanza del boss nella matrice delle stanze.
*/

Boss_Room::Boss_Room(Level* lvl, int x, int y)
: Room{lvl, x, y, 3}
{
	box(win, 88, 88);
}
