//
//  GestioneSchermo.hpp
//  ProgettoNcurses2
//
//  Created by Cono Cirone on 29/08/22.
//

#ifndef GESTIONE_SCHERMO_HPP
#define GESTIONE_SCHERMO_HPP
#include <curses.h>
class Player;

class GestioneSchermo {
public:
    void update();

    GestioneSchermo(Player* pl);

    ~GestioneSchermo();

    void change_player(Player* pl) { ref = pl; }

private:
	WINDOW* dialogue;
	WINDOW* life;
    int start_x, start_y;
    int dialogue_size;
    int life_size;
    int x_finale_mezzocuore;
    int x_seconda_riga;
    int y_corrente;
    Player* ref;
    char* exp;
    char* bombs;

    void disegna_cuori();
    void disegna_cuori_aggiunti(bool t, int y, int x);
    void aggiungi_cuore();
    void partition();
    void punteggio();

	void gestisci_casi_particolari_prima_riga();
    void gestisci_casi_particolari_seconda_riga();
    void gestisci_indice_prima_riga();
    void gestisci_indice_seconda_riga();

    void gestisci_finestra_dialogo();
    void casi_margine(int x, int y);

    void gestisci_vita();

    void scegli_numero(char c);
    void clear_dialogue();
    bool can_add(int x);
    void add_prima_riga();
    void add_seconda_riga();
};
#endif