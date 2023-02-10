#ifndef ROOM_HPP
#define ROOM_HPP
#include <curses.h>

class Entity;
class Entity_List;
class Level;
struct BP_Entity;

/*La classe Room è la classe alla base del gioco, in cui il Player si muove,
sconfigge nemici ed ottiene tesori.
Ogni istanza di Room viene generata da Level a seconda di una Blueprint,
da cui prende layout (blueprint.mappa) ed entità (blueprint->entities)*/

class Room {
public:

    /*Ciascuna stanza è inserita in una matrice di puntatori a Room nella classe
    Level, secondo le proprie coordinate    */
    Level* L;
    const int x_cor;
    const int y_cor;
    
    /*Ogni Room è dotata di un'id che può variare in base alle varie sottoclassi:
    3 per la stanza del boss, 2 per la stanza del tesoro, 1 per la stanza segreta, 
    0 per le stanze normali.
    Le porte tra stanza e stanza variano in base all'id, e richiedono condizioni 
    differenti per essere aperte    */
    const int id;

    /*Ogni Room è dotata di una Entity_List che contiene nemici e oggetti presenti
    in essa; quando sono assenti nemici, si aprono le porte verso le altre stanze, 
    se possibile*/
    Entity_List* const list;

    WINDOW* const win;

    Room(Level* lvl, int x, int y, int id = 0);

    ~Room();
    
    /*funzioni che disegnano le porte in una data stanza;
    Invocate da Level.close_all_doors()*/
    void mettiporta_up(int id);
    void mettiporta_down(int id);
    void mettiporta_sx(int id);
    void mettiporta_dx(int id);
    
    /*funzioni che gestiscono l'apertura delle porte in base agli id
    delle Room adiacenti (rispetto la matrice)*/
    void update();
    bool cleared();
    bool check_open_door(int id);
    void open_doors();

private:
    bool clear;

}; typedef Room* proom;
#endif