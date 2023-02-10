//
//  PrimaSchermata.hpp
//  ProgettoNcurses2
//
//  Created by Cono Cirone on 29/08/22.
//

#ifndef PRIMA_SCHERMATA_HPP
#define PRIMA_SCHERMATA_HPP
#include <curses.h>


enum class OPTION {
	GAME, COMMANDS, QUIT, NO_OPTION
};


class PrimaSchermata {
    WINDOW* win;
	void first_menu();
    void start();
    void disegna_titolo();
    void commands();
    void close_commands();

public:
    PrimaSchermata();

    OPTION seleziona();
    void command_menu();
};
#endif