#ifndef BLUEPRINT_HPP
#define BLUEPRINT_HPP

constexpr int AMP_ROOM = 100;
constexpr int ALT_ROOM = 30;

/*La classe Blueprint nasce per la generazione manuale di stanze dotate di specifici layout
e nemici al loro interno, così da evitare situazioni di stallo (ad esempio, un nemico
che non può essere raggiunto dal player).

Ciascuna Blueprint è composta da una matrice di char per rappresentare il layout della stanza,
da un array di pseudo-nemici, da un intero per il numero di entità, e da un puntatore next
ad un'altra Blueprint.*/

/*La struttura BP_Entity è utilizzata per descrivere un'entità e le sue coordinate nella stanza.
Non è utilizzata la classe Entity per problemi di inclusione ricorsiva nei vari file.*/

struct BP_Entity {
	const char* name;
	int y, x, z;
	BP_Entity(const char* name, int y, int x, int z = 0) {
		this->name = name;
		this->y = y;
		this->x = x;

		this->z = z;
		/*la variabile z è necessaria per l'implementazione dei bottoni, in quanto unica classe Entity
		con variabili oltre alla Location. La BP_Entity successiva ad un bottone, nell'array, non
		rappresenta una entità ma determina le caratteristiche del bottone*/
	}
};


class Blueprint {
public:
	char mappa[ALT_ROOM][AMP_ROOM + 1];
	Blueprint* next;
	BP_Entity* entities;
	int e_size;

	Blueprint(const char a[][AMP_ROOM + 1], BP_Entity entities[], int e_size);

	/*crea una lista concatenata di blueprint, da cui verranno generati i livelli;
	la prima stanza sarà sempre la stessa, ma le seguenti saranno scelte avanzando
	casualmente nella lista*/
	Blueprint* create_map_list(Blueprint* const A[], int i);
	
}; typedef Blueprint* pblueprint;



static constexpr char printTEST[ALT_ROOM][AMP_ROOM + 1] = {
	 "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
	 "H                                                                                                  H",
	 "H                                                                                                  H",
	 "H                                                                                                  H",
	 "H                 #######                                                                          H",
	 "H             #############                                                                        H",
	 "H                ##############                                                                    H",
	 "H                #############                                                                     H",
	 "H               ############                                           |                           H",
	 "H                                                                      |                           H",
	 "H                                                                      |                           H",
	 "H                                                                                                  H",
	 "H                                                                                                  H",
	 "H                                                                      |                           H",
	 "H                                                                      |                           H",
	 "H                                                                      |                           H",
	 "H             ____________________                                                                 H",
	 "H            |                                                                                     H",
	 "H            |                                                                                     H",
	 "H            |                                                                                     H",
	 "H            |                                                                                     H",
	 "H            |                                                                                     H",
	 "H            |                                                                                     H",
	 "H                                                                 _____________                    H",
	 "H                                                                                                  H",
	 "H                                                                                                  H",
	 "H                                                                                                  H",
	 "H                                                                                                  H",
	 "H                                                                                                  H",
	 "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" };
static Blueprint* const bp_boss = new Blueprint(printTEST, 
new BP_Entity[1]{ 
	{"Boss", 15, 48}
}, 1);

/*static Blueprint* const bp_boss = new Blueprint(printTEST, 
new BP_Entity[1]{ 
	{"Dash",  10, 15},
	{"Armor", 10, 25},
	{"Bow",10, 35},
	{"Burst",10, 45},
	{"Wave",10, 65},
	{"Explosive",23, 30},
	{"Boomerang",23, 70},
}, 7);
*/

static constexpr char print1[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                  ############                    |",
	 "|                                                                  ############                    |",
	 "|                                                                  ############                    |",
	 "|                                                |                 ############                    |",
	 "|                                                |                 ############                    |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                        ------------------------|-------------------------                        |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_a = new Blueprint(print1, nullptr, 0);

static constexpr char print5[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                ############                      |",
	 "|                                                                ############                      |",
	 "|                                                                ############                      |",
	 "|                        #######                 |                                                 |",
	 "|                        #######                 |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                        ------------------------|-------------------------                        |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                   #######                       |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_f1 = new Blueprint(print5, new BP_Entity[1]{
	{"Bomb", 22, 30}
}, 1);
static Blueprint* const bp_f2 = new Blueprint(print5, new BP_Entity[1]{
	{"Big", 22, 30}
}, 1);

static constexpr char print3[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                        ------------------------|-------------------------                        |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                                                |                                                 |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                 #############                                                                    |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_c1 = new Blueprint(print3,
new BP_Entity[2]{
		{"Wasp",  10, 7 },
		{"Wasp",  25, 75},
	}, 2);
static Blueprint* const bp_c2 = new Blueprint(print3,
new BP_Entity[2]{
		{"Turret",  10, 27 },
		{"Turret",  25, 75},
	}, 2);

static constexpr char print14[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                       |                                                  |                       |",
	 "|                       |                                                  |                       |",
	 "|                       $                                                  $                       |",
	 "|                       $                                                  $                       |",
	 "|                       $                                                  $                       |",
	 "|                       |                                                  |                       |",
	 "|_______________________|                                                  |_______________________|", //1-24
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",	 
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|_______________________                                                    _______________________|",
	 "|                       |                                                  |                       |",
	 "|                       |                                                  |                       |",
	 "|                       $                                                  $                       |",
	 "|                       $                                                  $                       |",
	 "|                       $                                                  $                       |",
	 "|                       |                                                  |                       |", //98-23
	 "|                       |                                                  |                       |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };

	 static Blueprint* const bp_d1 = new Blueprint(print14,
	 new BP_Entity[9]{
		{"Button",16, 49, 3},
		{"Button_var", 3, 24, 1},
		
		{"Button",4, 12, 3},
		{"Button_var", 24, 75, 1},

		{"Button",25, 86, 3},
		{"Button_var", 24, 24, 1},

		{"Button",25, 12, 3},
		{"Button_var", 3, 75, 1},

		{"Bomb",4, 86 }
	 },9);

	 static Blueprint* const bp_d2 = new Blueprint(print14,
	 new BP_Entity[9]{
		{"Button",16, 49, 3},
		{"Button_var", 3, 24, 1},
		
		{"Button",4, 12, 3},
		{"Button_var", 24, 75, 1},

		{"Button", 25, 86, 3},
		{"Button_var", 24, 24, 1},

		{"Button",25, 12, 3},
		{"Button_var", 3, 75, 1},

		{"Wasp",4, 86 },
	 },9);

	 static Blueprint* const bp_d3 = new Blueprint(print14,
	 new BP_Entity[12]{
		{"Button",16, 49, 3},
		{"Button_var", 3, 24, 1},
		
		{"Button",4, 12, 3},
		{"Button_var", 24, 75, 1},

		{"Button", 25, 86, 3},
		{"Button_var", 24, 24, 1},

		{"Button",25, 12, 3},
		{"Button_var", 3, 75, 1},

		{"Turret",15, 48 },
		{"Nurse",4, 86 },
		{"Nurse",23, 86 },
		{"Nurse",13, 49 },

	 },12);

static constexpr char print4[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|       ----------------------                                 --------------------------          |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                     __________________                                           |",
	 "|                                    [                  ]                                          |",
	 "|                                    [                  ]                                          |",
	 "|                                    [                  ]                                          |",
	 "|                                    [                  ]                                          |",
	 "|                                    [                  ]                                          |",
	 "|                                    [____           ___]                                          |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|       ----------------------                                 --------------------------          |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",  
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_e1 = new Blueprint(print4, 
new BP_Entity[1]{
	{"Bomb", 17, 47}
}, 1);
static Blueprint* const bp_e2 = new Blueprint(print4, 
new BP_Entity[2]{
	{"Bomb", 16, 46},
	{"Big", 18, 46}
}, 2);

static constexpr char print8[ALT_ROOM][AMP_ROOM + 1] = {
	 "                          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                          ",
	 "                          |                                             |                          ",
	 "                          |                                             |                          ",
	 "                          |                                             |                          ",
	 "                          |                                             |                          ",
	 "                          |                      |                      |                          ",
	 "                          |                      |                      |                          ",
	 "                          |                      |                      |                          ",
	 "                          |                      |                      |                          ",
	 "                          |                      |                      |                          ",
	 " ^^^^^^^^^^^^^^^^^^^^^^^^^^                      |                      ^^^^^^^^^^^^^^^^^^^^^^^^^^^|",	
	 "|                                                |                                                 |",
	 "|                                           ############                                           |",
	 "|                                          #            #                                          |",
	 "|                                          #            #                                          |",
	 "|                                          #            #                                          |",
	 "|                                          #            #                                          |",
	 "|                                           ############                                           |",
	 "|                                                |                                                 |",
	 " ^^^^^^^^^^^^^^^^^^^^^^^^^^                      |                      ^^^^^^^^^^^^^^^^^^^^^^^^^^^ ",
	 "                          |                      |                      |                          ",
	 "                          |                      |                      |                          ",
	 "                          |                      |                      |                          ",
	 "                          |                      |                      |                          ",
	 "                          |                                             |                          ",
	 "                          |                                             |                          ",
	 "                          |                                             |                          ",
	 "                          |                                             |                          ",
	 "                          |                                             |                          ",
	 "                          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                          " };
static Blueprint* const bp_h1 = new Blueprint(print8, 
new BP_Entity[1]{
	{"Boomerang", 14, 49}
}, 1);
static Blueprint* const bp_h2 = new Blueprint(print8, 
new BP_Entity[1]{
	{"Armor", 14, 48}
}, 1);
static Blueprint* const bp_h3 = new Blueprint(print8, 
new BP_Entity[1]{
	{"Bow", 14, 49}
}, 1);


static constexpr char print7[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     $                             |",
	 "|                              |                                     $                             |",
	 "|                              |                                     $                             |",
	 "|                              |                                     $                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              $                                     |                             |",
	 "|                              $                                     |                             |",
	 "|                              $                                     |                             |",
	 "|                              $                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "|                              |                                     |                             |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_g1 = new Blueprint(print7,
	new BP_Entity[8]{
			{"Button",  10, 7,  4},
			{"Button_var", 17, 31, 1},

			{"Button",  21, 45, 4},
			{"Button_var", 17, 31, 1},

			{"Button",  20, 87, 4},
			{"Button_var", 7, 69, 1},

			{"Button",  6, 64, 4 },
			{"Button_var", 7, 69, 1},
	}, 8);


static constexpr char print2[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                          ##        ##                                            |",
	 "|                                         #   #    #   #                                           |",
	 "|                                        #      # #     #                                          |",
	 "|                                        #              #                                          |",
	 "|                                         #            #                                           |",
	 "|                                          #          #                                            |",
	 "|                                            #      #                                              |",
	 "|                                              #  #                                                |", 
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_b1 = new Blueprint(print2, 
new BP_Entity[4]{
	{"Heart",15, 48},
	{"Wasp", 25, 90},
	{"Big", 18, 15},
	{"Nurse", 10, 65},

}, 4);
static Blueprint* const bp_b2 = new Blueprint(print2, 
new BP_Entity[5]{
	{"Heart",15, 48},
	{"Turret", 21, 85},	
	{"Turret", 11, 85},
	{"Turret", 21, 12},
	{"Turret", 11, 12},

}, 5);

static constexpr char print9[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                       ####################################################                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       #                                                  #                       |",
	 "|                       ####################################################                       |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "|                                                                                                  |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_i1 = new Blueprint(print9, new BP_Entity[2]{
	{"Bomb", 18, 45},
	{"Heart", 12, 45}
}, 2);

static Blueprint* const bp_i2 = new Blueprint(print9, new BP_Entity[4]{
	{"Big", 18, 42},
	{"Wasp", 12, 47},
	{"Button",  4, 47,  10},
	{"Button_var", 22, 44, 0}
}, 4);
static Blueprint* const bp_i3 = new Blueprint(print9, new BP_Entity[3]{
	{"Bomb", 18, 45},
	{"Button",  4, 47,  10},
	{"Button_var", 22, 44, 0}
}, 3);
static Blueprint* const bp_i4 = new Blueprint(print9, new BP_Entity[4]{
	{"Bomb", 18, 45},
	{"Heart", 12, 45},
	{"Button",  4, 47,  10},
	{"Button_var", 22, 44, 0}
}, 4);
static Blueprint* const bp_i5 = new Blueprint(print9, new BP_Entity[2]{
	{"Turret", 5, 86},
	{"Turret", 25, 11}
}, 2);
static Blueprint* const bp_i6 = new Blueprint(print9, new BP_Entity[2]{
	{"Turret", 5, 11},
	{"Turret", 25, 86}
}, 2);
static Blueprint* const bp_k1 = new Blueprint(print9, 
new BP_Entity[9]{ 
	{"Wasp",  25, 75},
	{"Heart", 14, 49},
	{"Big",18, 18},
	{"Heart",18, 48},
	{"Turret",10, 35},
	{"Turret", 15, 65},
	{"Wasp",6, 80},
	{"Button",  4, 47,  10},
	{"Button_var", 22, 44, 0}
}, 9);

static constexpr char print10[ALT_ROOM][AMP_ROOM + 1] = {
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 $                                                                |",
	 "|                                 $                                                                |",
	 "|                                 $                                                                |",
	 "|                                 $                                                                |",	 
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |________________________________________________________________|",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 $                                                                |",
	 "|                                 $                                                                |",
	 "|                                 $                                                                |",
	 "|                                 $                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "|                                 |                                                                |",
	 "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" };
static Blueprint* const bp_j1 = new Blueprint(print10, new BP_Entity[10]{
	{"Button",  5, 20,  4},
	{"Button_var", 4, 34, 1},

	{"Button",  5, 80,  4},
	{"Button_var", 4, 34, 1},

	{"Button",  25, 80,  4},
	{"Button_var", 22, 34, 1},

	{"Button",  25, 20,  4},
	{"Button_var", 22, 34, 1},

	{"Big", 20, 65},
	{"Wasp", 14, 20}
}, 10);

static Blueprint* const bp_j2 = new Blueprint(print10, new BP_Entity[10]{
	{"Button",  5, 20,  4},
	{"Button_var", 4, 34, 1},

	{"Button",  5, 80,  4},
	{"Button_var", 4, 34, 1},

	{"Button",  25, 80,  4},
	{"Button_var", 22, 34, 1},

	{"Button",  25, 20,  4},
	{"Button_var", 22, 34, 1},

	{"Wasp", 20, 65},
	{"Heart", 14, 20}
}, 10);

constexpr int TOT_STANZE_BASE = 24;
//numero delle stanze regolari, da aggiornare man mano, MENO una stanza su cui chiamare create_map

static Blueprint* const blueprint_list[TOT_STANZE_BASE] = { bp_g1, bp_e1, bp_b2,   bp_i5, bp_i6, bp_j1, bp_j2, bp_c2,  bp_d2, bp_i2, bp_h1, bp_d1, bp_d3, bp_b1,bp_c1, bp_e2, bp_f1, bp_f2, bp_k1,  bp_h2, bp_h3, bp_i1, bp_i3, bp_i4 }; 
//la stanza iniziale è quella in indice [1]; in test1 sono presenti tutti gli artefatti


#endif