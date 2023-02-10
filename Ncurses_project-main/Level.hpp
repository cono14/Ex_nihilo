//
//  Level.hpp
//  ProgettoNcurses2
//
//  Created by Cono Cirone on 29/08/22.
//

#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <cstring>
#include "Room.hpp"
#include "Boss_Room.hpp"
#include "Blueprint.hpp"
class Player;

constexpr int max_stanze = 13;

class Level {
protected:
    int starting_x, starting_y;
    int dado;
    bool sx;
    bool up;
    Player* player;

    void convert(BP_Entity* e, Room* r, int i);

public:
    proom matrice_stanze[25][25];
    int tot_room;
    int cur_x;
    int cur_y;
    p_boss_room psr;
    int stanze_rimanenti;
    pblueprint print;
    int psr_x, psr_y;
    int pbr_x, pbr_y;
    int tiro_precedente;
    int psecr_x, psecr_y;
    Level(pblueprint blueprint);

    ~Level();

    void create_room(int x, int y);
    void spawn_item(proom r, int x, int y);
    int gestisci_sovrapposizione();
    void scelta(int dado, bool special = false);
    void diminuisci_stanze_rimanenti();
    void create_special_room(int x, int y);
    void create_boss_room(int x, int y);
    void position_special_room(int x, int y);
    void generate2(int x, int y);
    void ultima_posizione(int x, int y);
    void close_all_doors();
    void create_secret_room(int x, int y);
    void generate_secret_room(int x, int y);
    void chose_sx_or_dx();
    bool is_near_secr_room();
    bool cleared();

    Player* generate(Player* player = nullptr);
};
#endif