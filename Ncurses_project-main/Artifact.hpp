#ifndef ARTIFACT_HPP
#define ARTIFACT_HPP
#include "Bomb.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
class Dynamic_Entity;
class Player;

/**
 *	Puntatore a funzione.
 */
typedef void (*skill) (Player*);

constexpr int NO_DURATION = 1;

/**
 *	Contenente le funzioni che rappresentano
 *	le abilita' conferite dagli artefatti.
 */
namespace Skills {
	/**
	 *	Esegui uno scatto nella direzione
	 *	di movimento.
	 */
	void dash(Player*);
	constexpr int dash_duration = NO_DURATION; 
	constexpr int dash_range = 6;
	constexpr int dash_recharge = 1 * sec;

	/**
	 *  Aggiungi uno stato di invincibilita' per 10 secondi.
	 */
	void armor(Player*);
	constexpr int armor_duration = 10 * sec;
	constexpr int armor_recharge = 25 * sec;

	/**
	 *	Scaglia una potente freccia (solo in orizzontale).
	 */
	void bow(Player*);
	constexpr int bow_duration = NO_DURATION;
	constexpr int bow_recharge = 2 * sec;
}


/**
 *	Struttura dati per la rappresentazione dei singoli artefatti,
 *	escludendo tutte le informazioni relative a posizione, etc...
 */
struct Artf_Type {
	const char* const name;
	const Shape* const shape;

	skill f;
	const int recharge_time, duration;

	const Prj_Type* const prj;

	// Variabili per il ripristino di risorse del giocatore.
	const int health, bombs;

	/**
	 *	Segnala se si tratta di un artefatto equipaggiabile o meno.
	 *	Gli artefatti non equipaggiabili non sostituiscono quello usato
	 *	al momento dal giocatore e si limitano a ripristinarne le risorse
	 *	(vita, bombe, etc...).
	 */ const bool equip_;

	/**
	 *	L'oggetto in input utilizza
	 *	l'abilita' dell'artefatto, se questa non
	 *	e' NULL.
	 */
	void use_skill(Player*) const;

	constexpr Artf_Type(const char* name, const Shape* s, skill skill, bool equip, const Prj_Type* p = nullptr,
	int recharge = 0, int duration = -1, int hp = 0, int bomb = 0)
	: shape{ s }, f{ skill }, prj{ p }, equip_{ equip }, health{ hp }, recharge_time{ recharge },
	duration{ duration }, bombs{ bomb }, name{ name }
	{}
};


/**
 *	Un artefatto e' un entita' che altera lo stato del giocatore.
 *
 *	Puo' fornire un'abilita' o alterare le statistiche dell'entita' che lo equipaggia.
 *	Puo' essere equipaggiato solo un artefatto alla volta.
 */
class Artifact : public Entity {
public:
	/**
	 *	Se l'artefatto non e' equipaggiato, aggiornalo
	 *	a schermo.
	 */
	void update() override;

	void handle_collision(COLLISION, int) override;

	Artifact(const Artf_Type* t, Location* l);

	const Artf_Type* const t_;
private:
	bool held_;
};


/* LISTA ARTEFATTI */
constexpr int NUM_ART = 9;

const Artf_Type heart
	{ "Heart", new Shape{new chtype[3] {'(', '+', ')'}, 3}, nullptr, false, nullptr, 0, -1, 10 };

const Artf_Type bomb
	{ "Bomb", &bomb_shape, nullptr, false, nullptr, 0, -1, 0, 1 };

const Artf_Type dash
	{ "Dash", new Shape{new chtype{'d'}, 1}, Skills::dash, true, nullptr, Skills::dash_recharge, Skills::dash_duration };

const Artf_Type armor
	{ "Armor", new Shape{ new chtype[3] {'{',':','}'}, 3}, Skills::armor, true, nullptr, Skills::armor_recharge, Skills::armor_duration };

const Artf_Type bow
	{ "Bow", new Shape{ new chtype{'D'}, 1}, Skills::bow, true, nullptr, Skills::bow_recharge, Skills::bow_duration };

const Artf_Type wave_prj
	{ "Wave", new Shape{new chtype[2]{'w','w'}, 2}, nullptr, true, wave };

const Artf_Type brst_prj
	{ "Burst", new Shape{ new chtype[3] {'<', '*', '>'}, 3}, nullptr, true, &burst};

const Artf_Type expl_prj
	{ "Explosive", new Shape{ new chtype{'0'}, 1}, nullptr, true, &explosive };

const Artf_Type boomerang_prj
	{ "Boomerang", new Shape{ new chtype{'q'}, 1}, nullptr, true, &boomerang };
#endif