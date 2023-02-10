#ifndef DYNAMIC_ENTITY_HPP
#define DYNAMIC_ENTITY_HPP
#include "Entity.hpp"
class Timer;

/**
 *	Una entita' dinamica e' una categoria di entita' in grado di muoversi
 *	tramite la funzione move().
 */
class Dynamic_Entity : public Entity {
public:

	/**
	 *	Se la vita e' scesa a 0 distruggi l'oggetto,
	 *  altrimenti aggiorna normalmente.
	 */
	void update() override;

	/**
	 *	Gestione generica di collisioni con
	 *	oggetti inanimati.
	 */
	void handle_collision(COLLISION, int) override;

	/**
	 *	Muovi l'entita' di una casella nella direzione specificata
	 *	alla velocita' in input.
	 *
	 *	Nota: speed = 0 indica la velocita' massima, e continua a
	 *	decrescere per speed = 1, 2, etc...
	 */
	virtual void move(DIRECTION);

	virtual bool is_alive();

	int get_hp() const { return hp_; }

	void increase_hp(int hp);

	void decrease_hp(int dmg);

	/**
	 *	Ritorna la direzione in cui l'entita' sta
	 *	procedendo al momento.
	 */
	DIRECTION get_direction() const;

	Dynamic_Entity(const Shape*, Location*, COLLISION, int hp, int speed=0);

	~Dynamic_Entity() override;
	
protected:

	/**
	 *	Funzione per la temporizzazione di azioni. Attende che il numero di chiamate ad update()
	 *	sia maggiore o uguale al parametro turns. Essendo il gioco programmato per aggiornarsi ogni 24ms,
	 *	è possibile calcolare l'effettivo tempo di attesa in millisecondi come 24 * turns.
	 
	bool wait_time(int turns);
	*/

	/**
	 *	Punti vita dell'entita'.
	 */
	int hp_, max_hp_;

	/**
	 *	True se l'entita' si e' mossa
	 *	nel turno di gioco corrente.
	 */
	bool has_moved_;

	int speed_;

	/**
	 *	Direzione in cui l'entita' sta
	 *	procedendo al momento.
	 */
	DIRECTION current_direction_;

	/* Variabili ausiliarie utilizzate nella gestione della barra della vita
	 * nell'HUD. */
	int lost_hp; int heal_hp;

	Timer* move_timer;
};
#endif