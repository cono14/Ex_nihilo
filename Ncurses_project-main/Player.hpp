#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Dynamic_Entity.hpp"
#include "Projectile.hpp"
struct Artf_Type;
class Bomb;

static const Shape player_shape_up = { new chtype[3]{'[','^',']'}, 3 };
static const Shape player_shape_down = { new chtype[3]{'[','v',']'}, 3 };
static const Shape player_shape_left = { new chtype[3]{'[','<',']'}, 3 };
static const Shape player_shape_right = { new chtype[3]{'[','>',']'}, 3 };
static const Shape def_shapes[4] = { player_shape_up, player_shape_down, player_shape_left, player_shape_right };

static const Shape armor_player_shape_up = { new chtype[3]{'{','^','}'}, 3 };
static const Shape armor_player_shape_down = { new chtype[3]{'{','v','}'}, 3 };
static const Shape armor_player_shape_left = { new chtype[3]{'{','<','}'}, 3 };
static const Shape armor_player_shape_right = { new chtype[3]{'{','>','}'}, 3 };
static const Shape armored_shapes[4] = { armor_player_shape_up, armor_player_shape_down, armor_player_shape_left, armor_player_shape_right };

static constexpr int player_hp = 100;
static constexpr int hit_dmg = 5; // Danno ricevuto per contatto fisico con un nemico (mezzo cuore)


enum GAME_STATUS {
	ONGOING, TERMINATING, ENDED
};


/**
 *	Il giocatore e' una entita' dinamica che puo' essere controllata tramite input da tastiera.
 */
class Player : public Dynamic_Entity {
public:
	chtype handle_input();

	void update() override;

	void move(DIRECTION) override;

	void handle_collision(COLLISION, int) override;

	void gain_xp(int);

	GAME_STATUS gameState() const;

	explicit Player(Location* spawn);

	Player(Level* lvl, Player &pl);

	~Player() override;

	// Funzioni legate alle abilita'
	void start_recharge_timer();
	void start_duration_timer();

	void set_armor();
	void remove_armor();

private:
	void attack(DIRECTION);

	void use_skill();

	void throw_bomb();

	bool check_door() const;

	bool is_alive() override;

	void quit();

	const Artf_Type* current_artifact_;

	const Prj_Type* current_projectile_;

	/**
	 *	Tipologia attuale della forma 
	 *	del giocatore.
	 */
	const Shape* shape_style;

	/**
	 *	Punti esperienza del giocatore.
	 */
	int expr_;

	int max_x, max_y;
	int bombs;
	bool armored;

	GAME_STATUS state_;

	Timer *attack_timer, *skill_recharge_timer, *skill_duration_timer, *quit_timer;

	friend class GestioneSchermo;
	friend class Game_over;
};
#endif
