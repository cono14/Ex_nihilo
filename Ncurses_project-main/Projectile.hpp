#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "Dynamic_Entity.hpp"

constexpr int NO_DELAY = 0;

/**
 *	Struttura dati per la rappresentazione delle
 *	tipologie di proiettili.
 */
struct Prj_Type {
	const Shape* shape;
	const int damage, range;
	const char* const name;

	/**
	 *	Tempo necessario per poter lanciare un altro
	 *	proiettile del medesimo tipo.
	 */
	const int time_delay;

	constexpr Prj_Type(const char* prj_name, const Shape* s, int dmg, int max_range, int delay)
	: shape { s }, damage{ dmg }, range{ max_range }, name{ prj_name }, time_delay{ delay }
	{}
};


/**
 *	Un proiettile e' un tipo di entita' lanciata da un'altra entita'.
 */
class Projectile : public Dynamic_Entity {
public:

	/**
	 *	Continua a far muovere il proiettile lungo la sua traiettoria.
	 */
	void update() override;

	/**
	 *	Se collide contro qualunque cosa, il proiettile viene distrutto.
	 */
	void handle_collision(COLLISION, int) override;

	Projectile(const Prj_Type*, DIRECTION, Entity* ref, COLLISION c_type = COLLISION::PROJECTILE, Location* loc=nullptr);

	/**
	 *	Riferimento all'entita' che lancia
	 *	il proiettile.
	 */
	Entity* const spawner_;

	const Prj_Type* t;

private:

	/**
	 *	Funzione ausiliaria per il costruttore.
	 */
	Location* init_location(DIRECTION, Entity*);

	/**
	 *	Numero di passi eseguiti al momento nel corso del movimento.
	 */
	int moves_;
};


/* TIPOLOGIE DI PROIETTILE */
static constexpr int def_prj_dmg = 10; static constexpr int def_prj_range = 15; static constexpr int def_prj_delay = sec/3;
static const Prj_Type def_prj{ "Default", new Shape{new chtype{'*'}, 1}, def_prj_dmg, def_prj_range, def_prj_delay };


static constexpr int wave_dmg = 15; static constexpr int wave_range = 10; static constexpr int wave_delay = sec/8;
static const Prj_Type wave_up{ "Wave", new Shape{new chtype{'^'}, 1}, wave_dmg, wave_range, wave_delay };
static const Prj_Type wave_down{ "Wave", new Shape{new chtype{'v'}, 1}, wave_dmg, wave_range, wave_delay };
static const Prj_Type wave_left{ "Wave", new Shape{new chtype{'<'}, 1}, wave_dmg, wave_range, wave_delay };
static const Prj_Type wave_right{ "Wave", new Shape{new chtype{'>'}, 1}, wave_dmg, wave_range, wave_delay };
static const Prj_Type wave[] = { wave_up,wave_down,wave_left,wave_right };


static constexpr int burst_dmg = 40; static constexpr int burst_range = 6; static constexpr int burst_delay = sec;
static const Prj_Type burst{ "Burst", new Shape{new chtype{'*'}, 1}, burst_dmg, burst_range, burst_delay };


static constexpr int bmrng_dmg = 20; static constexpr int bmrng_range = 20; static constexpr int bmrng_delay = sec/2;
static const Prj_Type boomerang{ "Boomerang", new Shape{ new chtype{'q'}, 1}, bmrng_dmg, bmrng_range, bmrng_delay };


static constexpr int explosive_dmg = 50; static constexpr int explosive_range = 10; static constexpr int explosive_delay = sec/2;
static const Prj_Type explosive{ "Explosive", new Shape{new chtype{'0'}, 1}, explosive_dmg, explosive_range, explosive_delay };


static constexpr int arrow_dmg = 100; static constexpr int arrow_range = 50; static constexpr int arrow_delay = NO_DELAY;
static const Prj_Type arrow_r{ "Arrow", new Shape{ new chtype[3]{'-', '-', '>'}, 3}, arrow_dmg, arrow_range, arrow_delay };
static const Prj_Type arrow_l{ "Arrow", new Shape{ new chtype[3]{'<', '-', '-'}, 3}, arrow_dmg, arrow_range, arrow_delay };
static const Prj_Type arrow[]={ arrow_l, arrow_r };
#endif