#include "GestioneSchermo.hpp"
#include <cstdlib>
#include "Artifact.hpp"
#include "Player.hpp"
#include "Timer.hpp"


GestioneSchermo::GestioneSchermo(Player* player)
{
	getmaxyx(stdscr, start_y, start_x);
	dialogue_size = 10;
	life_size = 50;
	dialogue = newwin(dialogue_size, 151, 31, 0);
	life = newwin(30, life_size, 0, 101);
	keypad(life, true);
	x_finale_mezzocuore = 43;
	x_seconda_riga = 43;
    y_corrente = 8;
    ref = player;
    exp = new char[10];
    bombs = new char[10];
    init_pair(2, COLOR_RED, COLOR_BLACK);
    disegna_cuori(); partition(); punteggio();
}


GestioneSchermo::~GestioneSchermo() {
    delete[] exp;
    delete[] bombs;
}

/*
  disegna_cuori(): 
   Funzione per mostare a schermo la vta del player. 
   E' presente un ciclo while che prende come indice la x in cui stampare i cuori, il ciclo termina una volta che sono stati stapati 5 cuori per riga.
   La y viene passata, invece, manualmente.
*/
   
void GestioneSchermo::disegna_cuori() {
    wattron(life, COLOR_PAIR(2));
    int i = 4;
    while (i < 45) {
        mvwprintw(life, 2, i,        "** **");
        mvwprintw(life, 3, i - 1,   "*  V  *");
        mvwprintw(life, 4, i,        "*   *");
        mvwprintw(life, 5, i + 2,      "*");

        mvwprintw(life, 7, i,        "** **");
        mvwprintw(life, 8, i - 1,   "*  V  *");
        mvwprintw(life, 9, i,        "*   *");
        mvwprintw(life, 10, i + 2,     "*");

        i += 9;
    } wattroff(life, COLOR_PAIR(2));
	wrefresh(life);
}

/* 
  partition(): 
    Divide lo schermo in 3 finestre:
     1)Finestra in cui si svolge la partita.
     2)Finestra in cui sono presenti: vita rimanente, punteggio e artefatto corrente.
     3)Finestra 'dialogo' in cui vengono mostrati vari messaggi in base a quello che sta succedendo nella partita.
*/

void GestioneSchermo::partition() {
	box(dialogue, 0, 0);
	box(life, 0, 0);
	refresh();
	wrefresh(life);
	wrefresh(dialogue);
}

/*
  gestisci_casi_particolari_prima_riga(): 
   Funzione implementata per visualizzare correttamente i cuori che vengono persi perdendo punti vita durante la partita. Senza questa funzione
   non si sarebbe riuscito a cancellare l'asterisco più a sinsitra di un cuore. Gestisce solo i casi particolari della prima riga di cuori.
*/
 

void GestioneSchermo::gestisci_casi_particolari_prima_riga() {
    int a[5] = { 3, 12, 21, 30, 39 };
    for (int i = 0; i < 5; i++) {
        if (x_finale_mezzocuore - 1 == a[i]) {
            mvwprintw(life, 3, x_finale_mezzocuore - 1, " ");
            wrefresh(life);
        }
    }
}

/*
  gestisci_casi_particolari_seconda_riga(): 
   Funzione parallela a gestisci_casi_particolari_prima_riga() solo che gestisce la seconda riga di cuori.
*/

void GestioneSchermo::gestisci_casi_particolari_seconda_riga() {
    int a[5] = { 3, 12, 21, 30, 39 };
    for (int i = 0; i < 5; i++) {
        if (x_seconda_riga - 1 == a[i]) {
            mvwprintw(life, 8, x_seconda_riga - 1, " ");
            wrefresh(life);
        }
    }
}

/*

  gestisci_indice_prima_riga(): 
   Funzione che permette di gestire correttamente la variabile 'x_finale_mezzocuore'. Una volta cancellato un cuore fa in modo che l'indice 
   vada sulla casella occupata dall'ultimo carattere del cuore precedente in modo da consentire un corretto funzionamento quando il player perderà un'altra 
   vita.
*/
void GestioneSchermo::gestisci_indice_prima_riga() {
    int b[4] = { 13, 22, 31, 40 };
    bool valore = false;
    for (int i = 0; i < 4; i++) {
        if (x_finale_mezzocuore == b[i]) {
            x_finale_mezzocuore -= 6;
            valore = true;
        }
    }
    if (valore == false) {
        x_finale_mezzocuore -= 3;
    }
}

/*
  gestisci_indice_seconda_riga(): 
   Funzione parallela a gestisci_indice_prima_riga() solo che viene implementata per gestire la seconda riga di cuori.
*/

void GestioneSchermo::gestisci_indice_seconda_riga() {
    int b[4] = { 13, 22, 31, 40 };
    bool valore = false;
    for (int i = 0; i < 4; i++) {
        if (x_seconda_riga == b[i]) {
            x_seconda_riga -= 6;
            valore = true;
        }
    }
    if (valore == false) {
        x_seconda_riga -= 3;
    }
}

/*

  gestisci_vita(): 
   Funzione per cancellare i cuori quando il player subisce danno. Inizia a cancellare dalla seconda riga di cuori, e, solo una volta dopo
   aver  tutti i cuori a disposizione su quella riga inizia a cancellare quelli sulla prima.
   
 */
void GestioneSchermo::gestisci_vita() {
    int j = 7;
    int i = 2;
    if (x_seconda_riga < 4) {
        while (i <= 5) {
            mvwprintw(life, i, x_finale_mezzocuore, "   ");
            gestisci_casi_particolari_prima_riga();
            i++;
        }
        gestisci_indice_prima_riga();
        y_corrente = 2;
    }
    else {
        while (j <= 10) {
            mvwprintw(life, j, x_seconda_riga, "   ");
            gestisci_casi_particolari_seconda_riga();
            j++;
        }
        gestisci_indice_seconda_riga();
        y_corrente = 7;
    }
    wrefresh(life);
}
/*
   scegli_numero(char c): 
    In base al danno subito dal player varia la quantità di cuori persi. In particolare il player può perdere:
    -Solo mezzo cuore.
    -Un cuore intero.
    -Un cuore e mezzo.
*/

void GestioneSchermo::scegli_numero(char c) {
    if (c == 'r') {
        gestisci_vita();
    } else if (c == 'w') {
        int i = 0;
        while (i < 2) {
            gestisci_vita();
            i++;
        }
    } else if (c == 'e') {
        int j = 0;
        while (j < 3) {
            gestisci_vita();
            j++;
        }
    } else if (c == 'f') {
        aggiungi_cuore();
    }
}


void GestioneSchermo::punteggio() {
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    wattron(life, COLOR_PAIR(1));
    mvwprintw(life, 13, 2, "POINTS:");
    mvwprintw(life, 15, 2, "BOMBS:");
    wattroff(life, COLOR_PAIR(1));

    sprintf(exp, "%d", ref->expr_); sprintf(bombs, "%d", ref->bombs);

    mvwprintw(life, 13, 10, exp);
    mvwprintw(life, 15, 9, bombs);
    if (ref->current_artifact_) {
        wattron(life, COLOR_PAIR(1));
        mvwprintw(life, 17, 2, "ARTIFACT:");
        wattroff(life, COLOR_PAIR(1));

        mvwprintw(life, 17, 12, "                  ");
        mvwprintw(life, 17, 12, ref->current_artifact_->name);
    }


    // Tempo di ricarica del proiettile
    mvwprintw(life, 22, 8, "Projectile: ");
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    wattron(life, COLOR_PAIR(3));
    if (ref->attack_timer->currentTime() >= ref->current_projectile_->time_delay)
		mvwprintw(life, 22, 20, "| | | | |");
    else if (ref->attack_timer->currentTime() >= static_cast<double>(ref->current_projectile_->time_delay)/5 * 4)
        mvwprintw(life, 22, 20, "| | | |  ");
    else if (ref->attack_timer->currentTime() >= static_cast<double>(ref->current_projectile_->time_delay)/5 * 3)
        mvwprintw(life, 22, 20, "| | |    ");
    else if (ref->attack_timer->currentTime() >= static_cast<double>(ref->current_projectile_->time_delay)/5 * 2)
        mvwprintw(life, 22, 20, "| |      ");
    else if (ref->attack_timer->currentTime() >= static_cast<double>(ref->current_projectile_->time_delay)/5)
        mvwprintw(life, 22, 20, "|        ");
    else
        mvwprintw(life, 22, 20, "         ");
    wattroff(life, COLOR_PAIR(3));


    // Ricarica delle abilita'
    /*
    if (ref->skill_recharge_timer) {
        mvwprintw(life, 24, 13, "Skill: ");
        if (!ref->skill_recharge_timer->hasStarted()) {
            init_pair(4, COLOR_GREEN, COLOR_BLACK);
            wattron(life, COLOR_PAIR(4));
        	mvwprintw(life, 24, 20, "R e a d y");
            wattroff(life, COLOR_PAIR(4));
        } else {
            init_pair(5, COLOR_RED, COLOR_BLACK);
            wattron(life, COLOR_PAIR(5));
            mvwprintw(life, 24, 20, "C h a r g i n g . . .");
            wattroff(life, COLOR_PAIR(5));
        }
    }
    */

    wrefresh(life);
}

/*
   gestisci_finestra_dialogo(): 
    In base a quello che sta succedendo nella partita mostra un determinato messagggio.
*/

void GestioneSchermo::gestisci_finestra_dialogo() {
    if (ref->gameState() == TERMINATING) {
        clear_dialogue();
        mvwprintw(dialogue, 1, 1, "Sei sicuro di voler abbandonare la partita?");
        mvwprintw(dialogue, 2, 1, " SI > Premi  'x' ");
        mvwprintw(dialogue, 3, 1, " NO > Continua a giocare ");
        wrefresh(dialogue);
    }
    else if (ref->get_location()->L->stanze_rimanenti == 0) {
        clear_dialogue();
        mvwprintw(dialogue, 1, 1, "Complimenti, puoi passare al livello successivo!");
        mvwprintw(dialogue, 2, 1, "Premi 'n' per iniziare un nuovo livello");
        wrefresh(dialogue);
    }
    else if (ref->get_location()->L->stanze_rimanenti == 1){
        if((ref->get_location()->L->cur_x == ref->get_location()->L->pbr_x) && (ref->get_location()->L->cur_y == ref->get_location()->L->pbr_y)){
            clear_dialogue();
            mvwprintw(dialogue, 1, 1, "Sconfiggi il boss!");
            wrefresh(dialogue);
        } else {
            clear_dialogue();
            mvwprintw(dialogue, 1, 1, "Coraggio! Resta solo il boss da affrontare!");
            wrefresh(dialogue);
        }
    }
    
    else if((ref->get_location()->L->cur_x == ref->get_location()->L->psr_x) && (ref->get_location()->L->cur_y == ref->get_location()->L->psr_y)){
        clear_dialogue();
        mvwprintw(dialogue, 1, 1, "Complimenti! Sei riuscito ad accedere alla stanza del tesoro, esplorala per guadagnare artefatti speciali!");
        wrefresh(dialogue);
    }
    else if(ref->get_location()->L-> cur_x == ref->get_location()->L->psecr_x && ref->get_location()->L-> cur_y == ref->get_location()->L->psecr_y){
         clear_dialogue();
         mvwprintw(dialogue, 1, 1, "WOW! Hai trovato una stanza segreta!");
         wrefresh(dialogue);
    } 
    else if(ref->get_location()->L->is_near_secr_room()){
        clear_dialogue();
        mvwprintw(dialogue, 1, 1, "C'è qualcosa di sospetto nelle vicinanze...");
        wrefresh(dialogue);
    }
    
    else clear_dialogue();
}

void GestioneSchermo::clear_dialogue(){
    mvwprintw(dialogue, 1, 1, "                                                                                                                 ");
    mvwprintw(dialogue, 2, 1, "                                                                                                                 ");
    mvwprintw(dialogue, 3, 1, "                                                                                                                 ");
    wrefresh(dialogue);
}

/*
  disegna_cuori_aggiunti(bool t, int y, int x):
   Il player potrebbe trovare un artefatto speciale che gli consente di ottenere un cuore aggiuntivo. Questa funzione 
   permette di vedere l'animazione su schermo. 
   In particolare gestisce due casi tramite un bool: 
   - Primo: Nel caso in cui il player abbia un numero di cuori non intero a disposizione allora disegna due metà
   -Secondo: Disegna un cuore intero.
*/

void GestioneSchermo::disegna_cuori_aggiunti(bool t, int y, int x) {
    wattron(life, COLOR_PAIR(2));
    if (t) {
        mvwprintw(life, y, x + 3,       "**");
        mvwprintw(life, y + 1, x + 3,   "  *");
        mvwprintw(life, y + 2, x + 4,   "*");
        x += 9;
        mvwprintw(life, y, x,            "** ");
        mvwprintw(life, y + 1, x - 1,  "*  V");
        mvwprintw(life, y + 2, x,       "*   ");
        mvwprintw(life, y + 3, x + 2,    "*");
    }  else {
        x += 9;
        mvwprintw(life, y, x - 3,      "** **");
        mvwprintw(life, y + 1, x - 4, "*  V  *");
        mvwprintw(life, y + 2, x - 3,  "*   *");
        mvwprintw(life, y + 3, x - 1,    "*");
    }
    wattroff(life, COLOR_PAIR(2));
}


void GestioneSchermo::casi_margine(int x, int y) {
    wattron(life, COLOR_PAIR(2));
    if (x == 40 && y == 2) {
        mvwprintw(life, y, x + 3, "**");
        mvwprintw(life, y + 1, x + 3, "  *");
        mvwprintw(life, y + 2, x + 4, "*");
        y = 7;
        x = 4;
        mvwprintw(life, y, x, "** ");
        mvwprintw(life, y + 1, x - 1, "*  V");
        mvwprintw(life, y + 2, x, "*   ");
        mvwprintw(life, y + 3, x + 2, "*");
        y_corrente = 7;
        x_finale_mezzocuore = 43;
        x_seconda_riga = 4;
    } else if (x == 40 && y == 7) {
        mvwprintw(life, y, x + 3, "**");
        mvwprintw(life, y + 1, x + 3, "  *");
        mvwprintw(life, y + 2, x + 4, "*");
        x_seconda_riga = 43;
    }
    wattroff(life, COLOR_PAIR(2));
}

bool GestioneSchermo::can_add(int x){
    if(x == 43){
        return false;
    } else {
        return true;
    }
}

/*
   aggiungi_cuore(): 
     Funzione per aggiungere un cuore quando si trova l'artefatto apposito. In particolare gestisce quattro casi:
      - I° Caso: Il player ha un numero di cuori intero. In questo caso aggiunge semplicemente un nuovo cuore a schermo.
      - II° Caso: Il player non ha un numero di cuori intero. In questo caso aggiunge prima la metà mancanta al cuore precedente e poi aggiunge un'altra metà.
      - III° Caso: Il cuore va aggiungto nella riga di cuori successiva.
      - IV° Caso: Va aggiunto metà cuore su una riga e metà sulla riga successiva.
*/

void GestioneSchermo::add_prima_riga(){
    int b[5] = { 4, 13, 22, 31, 40 };
    bool trovato = false;
    if(can_add(x_finale_mezzocuore)){
        for (int i = 0; i < 5; i++) {
            if (x_finale_mezzocuore == b[i]) {
                trovato = true;
            }
        }
      if(x_finale_mezzocuore == 40) {
            casi_margine(x_finale_mezzocuore, 2);
        } else {
            disegna_cuori_aggiunti(trovato, 2, x_finale_mezzocuore);
            x_finale_mezzocuore += 9;
        }
    } else {
        y_corrente = 7;
        x_seconda_riga = 7;
        wattron(life, COLOR_PAIR(2));
        mvwprintw(life, y_corrente, x_seconda_riga - 3,      "** **");
        mvwprintw(life, y_corrente + 1, x_seconda_riga - 4, "*  V  *");
        mvwprintw(life, y_corrente + 2, x_seconda_riga - 3 ,  "*   *");
        mvwprintw(life, y_corrente + 3, x_seconda_riga - 1,    "*");
        wattroff(life, COLOR_PAIR(2));
    }
}

void GestioneSchermo::add_seconda_riga(){
    int b[5] = { 4, 13, 22, 31, 40 };
    bool trovato = false;
    if(can_add(x_seconda_riga)){
        for (int i = 0; i < 5; i++) {
            if (x_seconda_riga == b[i]) {
                trovato = true;
            }
        }
        if (x_seconda_riga == 40) {
            casi_margine(x_seconda_riga, 7);
        } else {
            disegna_cuori_aggiunti(trovato, 7, x_seconda_riga);
            x_seconda_riga += 9;
        }
    }
}

void GestioneSchermo::aggiungi_cuore() {
    if (y_corrente == 7) {
        if(x_seconda_riga >= 4){
         add_seconda_riga();
        } else {
            add_prima_riga();
        }
    } else if (y_corrente == 2) {
        add_prima_riga();
        }
    }

    


void GestioneSchermo::update() {
    punteggio();

    /* Gestione cure */
    if (ref->heal_hp >= 10) {
        for (int i = ref->heal_hp; i >= 10; i -= 10) 
            scegli_numero('f');
        ref->heal_hp = 0;
    }

    /* Gestione danni */
    if (ref->lost_hp >= 15) {
        for (int i = ref->lost_hp; i >= 15; i -= 15) {
            scegli_numero('e');
            ref->lost_hp -= 15;
        }
    }

	if (ref->lost_hp >= 10) {
        for (int i = ref->lost_hp; i >= 10; i -= 10) {
            scegli_numero('w');
            ref->lost_hp -= 10;
        }

    }

	if (ref->lost_hp >= 5) {
        for (int i = ref->lost_hp; i >= 5; i -= 5) {
            scegli_numero('r');
            ref->lost_hp -= 5;
        }
	}

    gestisci_finestra_dialogo();
}

