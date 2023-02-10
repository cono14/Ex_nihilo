#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <curses.h>
#include "Level.hpp"
#include <ostream>
class Room;


/**
 *	Corrisponde a un secondo di tempo (in funzione
 *	del numero di chiamate ad update in main).
 */
static constexpr int sec = 42; 


/**
 *	Struttura dati per la rappresentazione
 *	del corpo di un'entita'.
 */
struct Shape {
	const chtype* shape;
	const int length;

	Shape(chtype* s, int len)
		: shape{ s }, length{ len } {
	}
};


/**
 *	Struttura dati per la rappresentazione della posizione
 *	di una entita' in gioco.
 */
struct Location {
	Level* L;
	Room* r;
	int y, x;

	Location(Level* level, int room_y, int room_x, int y_coord, int x_coord)
	: L{ level }, y{ y_coord }, x{ x_coord }
	{
		if (level) r = level->matrice_stanze[room_x][room_y];
		else r = nullptr;
	}

	/**
	 *	Genera una posizione nella stanza corrente.
	 */
	Location(Level* level, int y_coord, int x_coord)
	: L{ level }, y{ y_coord }, x{ x_coord }
	{
		if (level) 
			r = level->matrice_stanze[level->cur_x][level->cur_y];
		else r = nullptr;
	}

	/**
	 *  Costruttore alternativo.
	 */
	Location(Level* level, Room* room, int y_coord, int x_coord)
	: L{ level }, r{ room }, y{ y_coord }, x{ x_coord }
	{}

	Location(const Location& l) = default;
};


/**
 *	Valori per classificare le tipologie di
 *	collisioni che avvengono in gioco.
 */
enum class COLLISION {
	PLAYER, ARTIFACT, ENEMY, PROJECTILE,
	OBSTACLE, EXPLOSION, BUTTON
};


/**
 *	Valori per il movimento in quattro direzioni,
 *	incluso il valore che rappresenta lo stato "fermo".
 */
enum class DIRECTION {
	UP, DOWN, LEFT, RIGHT,
	STILL
};

DIRECTION operator-(DIRECTION d);


/**
 *	Una entita' e' un oggetto in gioco con cui e' possibile interagire. Una entita' puo' essere fisicamente presente o meno,
 *	e passare da uno stato all'altro (ad es. artefatti).
 *
 *	La funzione principale di una entita' e' update(), che aggiorna correttamente lo stato dell'oggetto ad ogni loop
 *	di gioco. Se l'entita' e' fisicamente presente a schermo, essa e' in grado anche di gestire eventuali collisioni
 *	con altre entita' o ostacoli inanimati.
 *
 *	Le entita' sono oggetti astratti, pertanto non e' possibile inizializzarne direttamente una (si inizializzano
 *	le sottoclassi).
 */
class Entity {
public:

	/**
	 *	Aggiorna l'entita' a schermo, se fisicamente
	 *	presente in-game.
	 */
	virtual void update();

	/**
	 *	Gestisce le collisioni. Definita all'interno
	 *	delle sottoclassi.
	 */
	virtual void handle_collision(COLLISION, int) = 0;

	/**
	 *	Ritorna true se si e' verificata una collisione. Se non
	 *	si fornisce alcuna entit� in input, la funzione verifica
	 *	collisioni con oggetti inanimati.
	 */
	bool check_collisions(const Entity* e = nullptr) const;

	/**
	 *	Ritorna la locazione dell'entita'.
	 */
	Location* get_location() const;

	/**
	 *	Ritorna la forma dell'entit�.
	 */
	const Shape* get_shape() const;

	static bool is_empty(chtype* s, int len);

	Entity(const Shape*, Location*, COLLISION);

	virtual ~Entity();

	/**
	 * Ad ogni entita' nel gioco e' associato
	 * un valore chiave univoco.
	 */
	const int key;

	const COLLISION type;

protected:

	/**
	 *	"Ripulisci" le caselle occupate
	 *	dall'entita' cancellando i caratteri.
	 */
	void wipe_shape(bool restore=true);

	/**
	 *	Inizializza la variabile prev_shape_.
	 */
	void init_prev() const;

	const Shape* shape_;

	Location* location_;

	/* Gestione collisioni */
	Location* prev_loc_;
	chtype* prev_shape_;

	static int key_val;
};
#endif