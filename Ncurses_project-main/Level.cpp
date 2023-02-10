#include "Level.hpp"
#include "Special_Room.hpp"
#include "Secret_Room.hpp"
#include "Boss_Room.hpp"
#include <random>

#include "Artifact.hpp"
#include "Nurse.hpp"
#include "Player.hpp"
#include "Turret.hpp"
#include "Wasp.hpp"
#include "Big.hpp"
#include "Boss.hpp"
#include "Button.hpp"

//funzione che converte una BP_Entity in una Entity vera e propria
void Level::convert(BP_Entity* e, Room* r, int i) {
    Location* loc = new Location{ this , r, e->y, e->x };

    /* Nemici */
    if (strcmp(e->name, "Wasp") == 0)
        new Wasp{ loc, player };
    if (strcmp(e->name, "Turret") == 0)
        new Turret{ loc, player, &def_prj };
    if (strcmp(e->name, "Big") == 0)
        new Big{ loc, player };
    if (strcmp(e->name, "Nurse") == 0)
        new Nurse{ loc, player, &def_prj };
    if (strcmp(e->name, "Boss") == 0)
        new Boss{ loc, player, &def_prj };
    //...

    if (strcmp(e->name, "Button") == 0) {
        BP_Entity* Button_var = &print->entities[i + 1];
        new Button{ loc, e->z, static_cast<bool>(Button_var->z), Button_var->y, Button_var->x };
    }

    /* Artefatti */
    if (strcmp(e->name, "Heart") == 0)
        new Artifact{ &heart, loc };
    if (strcmp(e->name, "Bomb") == 0)
        new Artifact{ &bomb, loc };
    if (strcmp(e->name, "Burst") == 0)
        new Artifact{ &brst_prj, loc };
    if (strcmp(e->name, "Dash") == 0)
        new Artifact{ &dash, loc };
    if (strcmp(e->name, "Armor") == 0)
        new Artifact{ &armor, loc };
    if (strcmp(e->name, "Wave") == 0)
        new Artifact{ &wave_prj, loc };
    if (strcmp(e->name, "Explosive") == 0)
        new Artifact{ &expl_prj, loc };
    if (strcmp(e->name, "Boomerang") == 0)
        new Artifact{ &boomerang_prj, loc };
    if (strcmp(e->name, "Bow") == 0)
        new Artifact{ &bow, loc };
    //...
}

//funzione che genera un artefatto casuale
void Level::spawn_item(proom r, int x, int y){
    srand(unsigned(time(0)));
    int xx = rand() % NUM_ART;
    
    Location* loc = new Location{ this , r, y, x };
    if (xx == 0) new Artifact{ &heart, loc };
    if (xx == 1) new Artifact{ &bomb, loc };
    if (xx == 2) new Artifact{ &dash, loc };
    if (xx == 3) new Artifact{ &wave_prj, loc };
    if (xx == 4) new Artifact{ &brst_prj, loc };
    if (xx == 5) new Artifact{ &armor, loc };
    if (xx == 6) new Artifact{ &expl_prj, loc };
    if (xx == 7) new Artifact{ &boomerang_prj, loc };
    if (xx == 8)  new Artifact{ &bow, loc };
}

/*
  Costruttore:
    Il livello viene generato come una matrice di stanze, tutte inizializzate a NULL.
    I parametri cur_x e cur_y indicano la posizione in cui si trova il player nella matrice delle stanze.
    Starting_x e Starting_y vengono usati per la generazione delle stanze del livello.
    Print è un puntatore a blueprint e serve per gestire l'aspetto della stanza.
   Tiro_precedente viene usato per gestire la posizione di generazione delle stanze nel livello.

 */

Level::Level(pblueprint blueprint) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            matrice_stanze[i][j] = nullptr;
        }
    }

    cur_x = 13; cur_y = 13;
    starting_x = 13; starting_y = 13;
    psr_x = 0; psr_y = 0;
    psecr_x = 0; psecr_y = 0;
    pbr_x = 0; pbr_y = 0;
    tot_room = 0;
    stanze_rimanenti = 0;
    print = blueprint;
    tiro_precedente = 0;
    sx = false;
    up = false;
}


Level::~Level() {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            delete matrice_stanze[i][j];
}


/*
  create_room(int x, int y):
     Crea un nuovo oggetto di tipo Room e lo posiziona nella matrice delle stanze. L'aspetto di tale stanza viene gestito
     mediante l'utilizzo di una lista. Ogni stanza avrà aspetto differente.

 */
void Level::create_room(int x, int y) {
    proom r = new Room(this, x, y);
    matrice_stanze[x][y] = r;
    
    srand(unsigned(time(0)));
    int random = rand() % 5;
    for (int i=0; i<random; i++) print=print->next;

    for (int i = 0; i < 30; i++)
        mvwaddstr(r->win, i, 0, print->mappa[i]);

    for (int i = 0; i < print->e_size; i++)
        convert(&print->entities[i], r, i);

    print = print->next;
}

/*
  create_boss_room(int x, int y):
     Crea un nuovo oggetto di tipo Boss_Room e lo posiziona nella matrice delle stanze.

 */
void Level::create_boss_room(int x, int y) {
    p_boss_room br = new Boss_Room(this, x, y);
    psr = br;
    matrice_stanze[x][y] = br;
    pbr_x = x;
    pbr_y = y;
    for (int i = 0; i < 30; i++)
        mvwaddstr(br->win, i, 0, bp_boss->mappa[i]);

    for (int i = 0; i < bp_boss->e_size; i++)
        convert(&bp_boss->entities[i], br, i);

}

/*
  create_special_room(int x, int y):
     Crea un nuovo oggetto di tipo Special_Room e lo posiziona nella matrice delle stanze.

 */

void Level::create_special_room(int x, int y) {
    p_special_room sr = new Special_Room(this, x, y);
    srand(unsigned(time(0)));
    int xx = rand() % NUM_ART;
    Location* loc = new Location{ this , sr, 14, 49 };

    if (xx == 0) new Artifact{ &heart, loc };
    if (xx == 1) new Artifact{ &bomb, loc };
    if (xx == 2) new Artifact{ &dash, loc };
    if (xx == 3) new Artifact{ &wave_prj, loc };
    if (xx == 4) new Artifact{ &brst_prj, loc };
    if (xx == 5) new Artifact{ &armor, loc };
    if (xx == 6) new Artifact{ &expl_prj, loc };
    if (xx == 7) new Artifact{ &boomerang_prj, loc };
    matrice_stanze[x][y] = sr;
    psr_x = x;
    psr_y = y;
}

/*
  create_secret_room(int x, int y):
     Crea un nuovo oggetto di tipo Secret_Room e lo posiziona nella matrice delle stanze.

*/

void Level::create_secret_room(int x, int y) {
    p_secret_room secr_r = new Secret_Room(this, x, y);
    matrice_stanze[x][y] = secr_r;
    psecr_x = x; psecr_y = y;
    srand(unsigned(time(0)));
    int random = rand() % 5;
    if(random>=3) spawn_item(secr_r, 67, 23);
    if(random % 2 ==0) {
        Location* loc1 = new Location{ this , secr_r, 10, 40 };
        new Wasp{ loc1, player };
    }
    if (random<3){
        Location* loc2 = new Location{ this , secr_r, 24, 42 };
        new Artifact{ &heart, loc2 };
    }
    if (random==0){
        Location* loc3 = new Location{ this , secr_r, 24, 42 };
        new Big{ loc3, player };
    }

}


/*
  gestisci_sovrapposizione():
    Funzione che ritorna un intero generato in maniera casuale.
*/
int Level::gestisci_sovrapposizione() {
    srand(unsigned(time(0)));
    int x = rand() % 4 + 1;
    return x;
}

/*
  close_all_doors():
   Fa un check su tutte le stanze presenti nella matrice delle stanze e, sceglie l'aspetto delle porte in base al tipo di stanza
   in modo da renderle riconoscibili al player, che saprà riconoscere quando si trova in corrispondenza di una stanza normale, del boss o speciale.

 */
void Level::close_all_doors() {
    for (int xx = 0; xx < 25; xx++) {
        for (int yy = 0; yy < 25; yy++) {
            proom r = matrice_stanze[xx][yy];
            if (r != NULL) {
                if (matrice_stanze[xx][yy - 1] != NULL) {
                    r->mettiporta_up(matrice_stanze[xx][yy - 1]->id);
                }if (matrice_stanze[xx][yy + 1] != NULL) {
                    r->mettiporta_down(matrice_stanze[xx][yy + 1]->id);
                }if (matrice_stanze[xx - 1][yy] != NULL) {
                    r->mettiporta_sx(matrice_stanze[xx - 1][yy]->id);
                }if (matrice_stanze[xx + 1][yy] != NULL) {
                    r->mettiporta_dx(matrice_stanze[xx + 1][yy]->id);
                }
            }
        }
    }
}

/*
   scelta(int dado, bool special):
     In base al numero random che è stato scelto nella funzione generate sceglie dove posizionare la nuova stanza servendosi delle variabili starting_x e starting_y.
     Se la posizione scelta è già occupata allora richiama la funzione  gestisci_sovrapposizione() per generare un nuovo numero, e, richiama ricorsivamente
         se stessa in modo da posizionare la nuova stanza solo quando si è sicuri di non creare collisioni nella matrice.
*/

void Level::scelta(int dado, bool special) {
    if (dado == 1) {
        starting_x += 1;
        tiro_precedente = 1;
    }
    else if (dado == 2) {
        starting_x -= 1;
        tiro_precedente = 2;
    }
    else if (dado == 3) {
        starting_y += 1;
        tiro_precedente = 3;
    }
    else if (dado == 4) {
        starting_y -= 1;
        tiro_precedente = 4;
    }
    if (matrice_stanze[starting_x][starting_y] != NULL) {
        dado = gestisci_sovrapposizione();
        scelta(dado);
    }
    if (special) {
        create_special_room(starting_x, starting_y);
    }
    else create_room(starting_x, starting_y);
}

/*
   generate():
     Si occupa delle generazione delle stanze all'interno del livello. Ogni livello ha una stanza centrale in posizione (13,13).
      Il resto delle stanze, invece, viene generato in posizione casuale. La generazione randomica avviene tramite l'utilizzo di un intero (dado)
      che ad ogni ripetizione del ciclo while assume un nuovo valore casuale e sceglie la nuova posizione in cui generare la stanza. Inoltre, si utilizza
      un bool special per gestire la generazione della stanza del tesoro.
      Questa funzione si serve dell'utilizzo di altre funzioni ausiliari quali:
       -generate2(intx, int y).
       -scelta(dado).
       -create_boss_room(int x, int y): genera la stanza del boss sempre alla fine del livello e nell'ultima posizione disponibile.
       -generate_secret_room(int x, int y): viene richiamata sulla posizione (13,13), e, da lì cerca autonomamente una posizione libera.

*/

Player* Level::generate(Player* pl) {
    // Creating starting room
    proom r = new Room(this, 13, 13);
    matrice_stanze[13][13] = r;

    if (pl) player = new Player{ this, *pl };
    else player = new Player{ new Location{this, 13, 13, 25, 48} };

    for (int i = 0; i < 30; i++)
        mvwaddstr(r->win, i, 0, print->mappa[i]);

    for (int i = 0; i < print->e_size; i++)
        convert(&print->entities[i], r, i);

    print = print->next;

    bool special = false;
    int dado = 0;
    while (tot_room < max_stanze) {
        dado = rand() % 4 + 1;
        if (tot_room > max_stanze / 2 - 2 && !special) {
            special = true;
            scelta(dado, true);
            tot_room += 1;
        }
        else {
            generate2(starting_x, starting_y);
            scelta(dado);
            tot_room += 1;
        }
    }

    create_boss_room(starting_x, starting_y);
    generate_secret_room(13, 13);
    close_all_doors();
    stanze_rimanenti = tot_room + 1;
    return this->player;
}


/*
   generate2(int x, int y):
      Viene richiamata in generate.
     Prende le coordinate x e y dell'ultima stanza generata, e, se quella stanza ha delle posizioni adiacenti libere nella matrice allora generate2
     genera nuove stanze in quelle posizioni. E' stata introdotta per continuare ad avere una generazione random del livello, ma, allo stesso tempo,
     essere sicuri di avere sempre più collegamenti tra stanze.
*/

void Level::generate2(int x, int y) {
    if (matrice_stanze[x + 1][y] == NULL) {
        create_room(x + 1, y);
        tot_room += 1;
    }
    if (matrice_stanze[x - 1][y] == NULL) {
        create_room(x - 1, y);
        tot_room += 1;
    }
    if (matrice_stanze[x][y + 1] == NULL) {
        create_room(x, y + 1);
        tot_room += 1;
    }
    if (matrice_stanze[x][y - 1] == NULL) {
        create_room(x, y - 1);
        tot_room += 1;
    }
    ultima_posizione(x, y);
}

/*
   chose_sx_or_dx():
     E' una funzione richiamata in generate_secret_room().
     In base ad un numero casuale sceglie in quale dei 4 estremi della mappa andare a posizionare la stanza segreta.
*/

void Level::chose_sx_or_dx() {
    srand(unsigned(time(0)));
    int dado = rand() % 3 + 1;
    if (dado == 1) {
        sx = true;
        up = true;
    }
    else if (dado == 2) {
        sx = false;
        up = true;
    }
    else if (dado == 3) {
        sx = true;
        up = false;   //non serve considerar eil quarto caso dato che up e sx sono già inizializzati a false
    }
}

/*
    generate_secrete_room(int x, int y):
             funzione ricorsiva per gestire la posizione della stanza segreta.
        La posizione in cui andare a generare la stanza segreta si basa sull'utilizzo di due bool: up e sx.
        Il loro valore viene scelto nella funzione chose_sx_or_dx(), e, in base a quello generate_secrete_room genera
        la stanza segreta in uno dei 4 angoli della mappa.
*/


void Level::generate_secret_room(int x, int y) {
    if (matrice_stanze[x][y] == NULL) {
        create_secret_room(x, y);
    }
    else {
        if (up == true) {
            y = y + 1;
        }
        else {
            y = y - 1;
        }  if (sx == true) {
            generate_secret_room(x - 1, y);
        }
        else {
            generate_secret_room(x + 1, y);
        }
    }
}

/*
   ultima_posizione(int x, int y):
     Serve per scegliere in maniera casuale la posizione da cui ricominciare a generare una singola stanza dopo aver eseguito generate2.
*/

void Level::ultima_posizione(int x, int y) {
    int choice = rand() % 4 + 1;
    int xx = x;
    int yy = y;
    if (choice == 1) {
        starting_x = x + 1;
        starting_y = y;
    }
    else if (choice == 2) {
        starting_x = x - 1;
        starting_y = y;
    }
    else if (choice == 3) {
        starting_x = x;
        starting_y = y + 1;
    }
    else if (choice == 4) {
        starting_x = x;
        starting_y = y - 1;
    }
    if (matrice_stanze[starting_x][starting_y] == NULL) {
        ultima_posizione(xx, yy);
    }
}

/*
    dimiuisci_stanze rimanenti():
        una volta completata una stanza non viene più contata nel conteggio delle stanze rimanenti.
        Arrivati a zero stanze rimanenti si può passare al livello successivo.
*/

void Level::diminuisci_stanze_rimanenti() {
    if (matrice_stanze[cur_x][cur_y]->cleared() == false) {
        stanze_rimanenti -= 1;
    }
}

/*
  is_near_secr_room():
    ritorna un booleano per sapere se ci si trova vicini o meno alla stanza del tesoro. Viene utilizzata
     nella funzione GestioneSchermo::gestisci_finestra_dialogo() per dare un indizio al giocatore.
*/

bool Level::is_near_secr_room() {
    if (cur_y == psecr_y || cur_x == psecr_x) {
        return true;
    }
    else {
        return false;
    }
}

bool Level::cleared() {
    return stanze_rimanenti == 0;
}