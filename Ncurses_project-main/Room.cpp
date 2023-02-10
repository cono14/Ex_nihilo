#include <cstring>
#include "Room.hpp"
#include "Entity_List.hpp"
#include "Level.hpp"


Room::Room(Level* lvl, int x, int y, int room_id)
: x_cor{ x }, y_cor{ y }, win{ newwin(30, 100, 0, 0) }, list{ new Entity_List{} }, id{ room_id },
L{ lvl }, clear{ false }
{};


Room::~Room() {
    delete list;
}


/*
   mettiporta_up(int id): 
    In base all'id della stanza che viene passato alla funzione sceglie il tipo di porta per creare il collegamento tra una stanza e un'altra.
    Svolgono la stessa funzione anche le altre 'mettiporta'.
*/
void Room::mettiporta_up(int id) {
    int x, y;
    getmaxyx(win, y, x);
    if (id == 0) {
        mvwaddstr(win, 0, x / 2 - 4, "xxxxxxxx");
    }
    else if (id == 1) {
        mvwaddstr(win, 0, x / 2 - 4, "########");
    }
    else if (id == 2) {
        mvwaddstr(win, 0, x / 2 - 4, "~~~~~~~~");
    }
    else if (id == 3) {
        mvwaddstr(win, 0, x / 2 - 4, "XXXXXXXX");
    }
}


void Room::mettiporta_down(int id) {
    int x, y;
    getmaxyx(win, y, x);
    if (id == 0) {
        mvwaddstr(win, y - 1, x / 2 - 4, "xxxxxxxx");
    }
    else if (id == 1) {
        mvwaddstr(win, y - 1, x / 2 - 4, "########");
    }
    else if (id == 2) {
        mvwaddstr(win, y - 1, x / 2 - 4, "~~~~~~~~");
    }
     else if (id == 3) {
        mvwaddstr(win, y - 1, x / 2 - 4, "XXXXXXXX");
    }
}


void Room::mettiporta_sx(int id) {
    int x, y;
    getmaxyx(win, y, x);
    if (id == 0) {
        mvwaddstr(win, y / 2 - 1, 0, "x");
        mvwaddstr(win, y / 2, 0, "x");
        mvwaddstr(win, y / 2 + 1, 0, "x");
    }
    else if (id == 1) {
        mvwaddstr(win, y / 2 - 1, 0, "#");
        mvwaddstr(win, y / 2, 0, "#");
        mvwaddstr(win, y / 2 + 1, 0, "#");
    }
    else if (id == 2) {
        mvwaddstr(win, y / 2 - 1, 0, "{");
        mvwaddstr(win, y / 2, 0, "{");
        mvwaddstr(win, y / 2 + 1, 0, "{");
    }
    else if (id == 3) {
        mvwaddstr(win, y / 2 - 1, 0, "X");
        mvwaddstr(win, y / 2, 0, "X");
        mvwaddstr(win, y / 2 + 1, 0, "X");
    }
}


void Room::mettiporta_dx(int id) {
    int x, y;
    getmaxyx(win, y, x);
    if (id == 0) {
        mvwaddstr(win, y / 2 - 1, x - 1, "x");
        mvwaddstr(win, y / 2, x - 1, "x");
        mvwaddstr(win, y / 2 + 1, x - 1, "x");
    }
    else if (id == 1) {
        mvwaddstr(win, y / 2 - 1, x - 1, "#");
        mvwaddstr(win, y / 2, x - 1, "#");
        mvwaddstr(win, y / 2 + 1, x - 1, "#");
    }
    else if (id == 2) {
        mvwaddstr(win, y / 2 - 1, x - 1, "}");
        mvwaddstr(win, y / 2, x - 1, "}");
        mvwaddstr(win, y / 2 + 1, x - 1, "}");
    }
     else if (id == 3) {
        mvwaddstr(win, y / 2 - 1, x - 1, "X");
        mvwaddstr(win, y / 2, x - 1, "X");
        mvwaddstr(win, y / 2 + 1, x - 1, "X");
    }
}


bool Room::check_open_door(int id){
    if(id==3) return (L->stanze_rimanenti==1);
    if(id==2) return (L->stanze_rimanenti <= L->tot_room / 2 + 1); //se si lascia il >= allora la stanza del tesoro viene sbloccata subito e quando si esplorano più stanze non ci si riuscirà più ad accedere.
    if(id==1) return 0;
    else return 1;
}


void Room::open_doors(){
    int y, x;
    getmaxyx(L->matrice_stanze[L->cur_x][L->cur_y]->win,y,x);
 
    if(L->matrice_stanze[L->cur_x][L->cur_y-1]!=NULL &&  check_open_door(L->matrice_stanze[L->cur_x][L->cur_y-1]->id)){
        mvwaddstr(win, 0, x/2-4, "        ");
    } if(L->matrice_stanze[L->cur_x][L->cur_y+1]!=NULL &&  check_open_door(L->matrice_stanze[L->cur_x][L->cur_y+1]->id)){
       mvwaddstr(win, y-1, x/2-4, "        ");
    } if(L->matrice_stanze[L->cur_x-1][L->cur_y]!=NULL &&  check_open_door(L->matrice_stanze[L->cur_x-1][L->cur_y]->id)){
        mvwaddstr(win, y/2-1, 0, " ");
        mvwaddstr(win, y/2, 0, " ");
        mvwaddstr(win, y/2+1, 0, " ");
    } if(L->matrice_stanze[L->cur_x+1][L->cur_y]!=NULL &&  check_open_door(L->matrice_stanze[L->cur_x+1][L->cur_y]->id)){
        mvwaddstr(win, y/2-1, x-1, " ");
        mvwaddstr(win, y/2, x-1, " ");
        mvwaddstr(win, y/2+1, x-1, " ");
    }
}

void Room::update() {
    list->update();
    if (list->enemies() == 0) {
        open_doors();
        L->diminuisci_stanze_rimanenti();
        clear = true;
    }
}


bool Room::cleared() {
    return clear;
}
