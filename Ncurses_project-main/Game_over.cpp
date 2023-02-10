#include "Game_over.hpp"
#include "string.h"

Game_over::Game_over(Player* player) {
    win = newwin(41, 151, 0, 0);
    this->player = player;
}

void Game_over::update() {
    clear();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    box(win, 81, 81);
    wbkgd(win, COLOR_PAIR(1));


    const char* art[] = {
      " _____                          ____                 ",
      "/ ____|                        / __ \\                ",
      "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __",
      "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|",
      "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   ",
      " \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   ",
    };

    int starty = 16;

    for (int i = 0; i < 6; i++) {
        int startx = 50;
        mvwprintw(win, starty + i, startx, "%s", art[i]);
    }
    mvwprintw(win, 24, 63, "Hai totatilizzato %d punti", player->expr_);
    mvwprintw(win, 28, 60, " > Premi E per tornare indietro < ");
   
    wrefresh(win);
}

void Game_over::go_back() {
    while (1) {
        int c = wgetch(win);
        if (c == 'e' || c == 'E') {
            break;
        }
    }
    clear();
}