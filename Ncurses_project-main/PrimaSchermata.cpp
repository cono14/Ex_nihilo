#include "PrimaSchermata.hpp"
#include "string.h"

PrimaSchermata::PrimaSchermata() {
    this->win = newwin(41, 151, 0, 0);
    box(win, 35, 35);
    keypad(win, true);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    wbkgd(win, COLOR_PAIR(2));
    nodelay(win, true);

    first_menu();
}

/*
  start():
   Vengono mostrate a schermo le varie opzioni tra cui scegliere quando si è nel menù iniziale.
*/

void PrimaSchermata::start() {
    wattron(win, A_STANDOUT);
    mvwprintw(win, 23, 53, " -> Premi 's' per iniziare una nuova partita <- ");
    mvwprintw(win, 25, 53, "     -> Premi 'c' per aprire i comandi <-       ");
    mvwprintw(win, 27, 53, "     -> Premi 'q' per uscire dal gioco <-       ");
    wrefresh(win);
    wattroff(win, A_STANDOUT);
}

/*
  command_menu(): 
   Utilizzata per la gestione della finestra dei comandi. 
   Per evitare collisioni su schermo viene cancellata la finestra del menù precdente e ne viene creata una nuova in cui vengono poi mostrati i comandi.
   Viene utilizzato un ciclo while per far in modo che, quando si è in questa finestra, basti premere il tasto 'esc' per tornare al menù principale.
   
*/

void PrimaSchermata::command_menu() {
    werase(win);
    box(win, 0, 0);
    commands();
    bool in_menu = true;
    wrefresh(win);

    while (in_menu) {
        if (wgetch(win) == 27) {
            close_commands();
            in_menu = false;
        }
    }
}

/* 
  close_commands(): 
   Aggiorna lo schermo mostrandoci nuovamente il menù principale.
  
 */

void PrimaSchermata::close_commands() {
    werase(win);
    first_menu();
    wrefresh(win);
}

/*
  first_menu(): 
   Mostra all'utente il menù principale.
*/

void PrimaSchermata::first_menu() {
    box(win, 35, 35);
    start();
    disegna_titolo();
    wrefresh(win);
}

/* 
 commands(): 
  Mostra all'utente i comandi.
*/

void PrimaSchermata::commands() {
    mvwprintw(win, 11, 55, "            MOVIMENTI:               ");
    mvwprintw(win, 12, 55, "-> w per spostarsi verso l'alto <- ");
    mvwprintw(win, 13, 55, " -> a per spostarsi a sinistra <- ");
    mvwprintw(win, 14, 55, "-> s per spostarsi verso il basso <-");
    mvwprintw(win, 15, 55, "  -> d per spostarsi a destra <- ");
    mvwprintw(win, 17, 55, "             ATTACCHI:               ");
    mvwprintw(win, 18, 55, "-> i per attaccare verso l'alto <-");
    mvwprintw(win, 19, 55, "-> k per attaccare verso il basso <-");
    mvwprintw(win, 20, 55, "  -> j per attaccare a sinistra <-");
    mvwprintw(win, 21, 55, "  -> l per attaccare a destra <-");
    mvwprintw(win, 23, 55, "             ARTEFATTI:          ");
    mvwprintw(win, 24, 55, "-> tab per usare l'artefatto corrente <-");
    mvwprintw(win, 25, 55, "      -> b per usare le bombe <-        ");
    mvwprintw(win, 27, 53, "-> x per abbandonare la partita corrente <-");
    wattron(win, A_STANDOUT);
    mvwprintw(win, 37, 53, "-> Premi esc per tornare al menu' principale <-");
    wrefresh(win);
    wattroff(win, A_STANDOUT);
}


/*
  seleziona(): 
   Funzione di tipo Option che prende l'input da tastiera e in base all'opzione scelta dell'utente esegue il comando.
   - S: inizia una nuova partita.
   - C: entra nel menù dei comandi.
   - Q: esce dal gioco.
*/

OPTION PrimaSchermata::seleziona() {
    chtype t = wgetch(win);
    if (t == 's' || t == 'S') return OPTION::GAME;
    if (t == 'c' || t == 'C') return OPTION::COMMANDS;
    if (t == 'q' || t == 'Q') return OPTION::QUIT;

	return OPTION::NO_OPTION;
}


void PrimaSchermata::disegna_titolo() {
    const char* art[] = {
    " ______     __  __        __   __     __     __  __     __     __         ______",
    "/\\  ___\\   /\\_\\_\\_\\      /\\ '-.\\ \\   /\\ \\   /\\ \\_\\ \\   /\\ \\   /\\ \\       /\\  __ \\ ",
    "\\ \\  __\\   \\/_/\\_\\/_     \\ \\ \\-.  \\  \\ \\ \\  \\ \\  __ \\  \\ \\ \\  \\ \\ \\____  \\ \\ \\/\\ \\ ",
    " \\ \\_____\\   /\\_\\/\\_\\     \\ \\_\\\' \\_\\  \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\  \\ \\_____\\  \\ \\_____\\",
    "  \\/_____/   \\/_/\\/_/      \\/_/ \\/_/   \\/_/   \\/_/\\/_/   \\/_/   \\/_____/   \\/_____/",
     
    };

    int starty = 12;

    for (int i = 0; i < 5; i++) {
        int startx = 35;
        mvwprintw(win, starty + i, startx, "%s", art[i]);
    }

    wrefresh(win);
}

