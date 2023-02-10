#include <cstring>
#include "Player.hpp"
#include "Level.hpp"
#include "Bomb.hpp"
#include "Artifact.hpp"
#include "Entity_List.hpp"
#include "Timer.hpp"


void Player::update() {
	attack_timer->update();
	if (quit_timer) {
		quit_timer->update();
		if (quit_timer->wait())
			state_ = ONGOING;
	}

	if (skill_duration_timer) {
		skill_duration_timer->update();
		if (skill_duration_timer->wait()) {
			const char* artf_name = current_artifact_->name;
			if (strcmp(artf_name, "Armor") == 0) remove_armor();

			start_recharge_timer();
		}
	}

	if (skill_recharge_timer) 
		skill_recharge_timer->update();

	Dynamic_Entity::update();
}


chtype Player::handle_input() {
	const chtype input = wgetch(location_->r->win);

	switch (input) {
	case 'W':
	case 'w': move(DIRECTION::UP);	break;
	case 'S':
	case 's': move(DIRECTION::DOWN);	break;
	case 'A':
	case 'a': move(DIRECTION::LEFT);	break;
	case 'D':
	case 'd': move(DIRECTION::RIGHT);	break;

	case 'I':
	case 'i': attack(DIRECTION::UP);		break;
	case 'K':
	case 'k': attack(DIRECTION::DOWN);	break;
	case 'J':
	case 'j': attack(DIRECTION::LEFT);	break;
	case 'L':
	case 'l': attack(DIRECTION::RIGHT);	break;

	case ' ': use_skill();				    break;

	case 'B':
	case 'b': if (bombs > 0) throw_bomb();	break;

	case 'X':
	case 'x': quit(); break;

	default: break;
	} return input;
}


void Player::quit() {
	if (state_ == ONGOING) {
		state_ = TERMINATING;
		quit_timer = new Timer{ sec*2, true };
	} else if (state_ == TERMINATING && !quit_timer->wait()) 
		state_ = ENDED;
}


void Player::use_skill() {
	if (current_artifact_ && current_artifact_->f && skill_recharge_timer->wait())
		current_artifact_->use_skill(this);
}


void Player::move(DIRECTION d) {
	Dynamic_Entity::move(d);

	switch (d) {
	case DIRECTION::UP:
		shape_ = &shape_style[0];	break;
	case DIRECTION::DOWN:
		shape_ = &shape_style[1];	break;
	case DIRECTION::LEFT:
		shape_ = &shape_style[2];	break;
	case DIRECTION::RIGHT:
		shape_ = &shape_style[3];	break;
	}

	// Codice per il cambio di stanza.
	if (check_door() && location_->r->cleared()) {
		const auto level = location_->L;
		location_->r->list->remove(key);
		switch (d) {
		case DIRECTION::UP:
			if (level->matrice_stanze[level->cur_x][level->cur_y - 1] != nullptr) {
				location_->r = level->matrice_stanze[level->cur_x][level->cur_y - 1];
				location_->y = max_y - 3;
				level->cur_y -= 1;
			} break;
		case DIRECTION::DOWN:
			if (level->matrice_stanze[level->cur_x][level->cur_y + 1] != nullptr) {
				location_->r = level->matrice_stanze[level->cur_x][level->cur_y + 1];
				location_->y = 2;
				level->cur_y += 1;
			} break;
		case DIRECTION::LEFT:
			if (level->matrice_stanze[level->cur_x - 1][level->cur_y] != nullptr) {
				location_->r = level->matrice_stanze[level->cur_x - 1][level->cur_y];
				location_->x = max_x - 5;
				level->cur_x -= 1;
			} break;
		case DIRECTION::RIGHT:
			if (level->matrice_stanze[level->cur_x + 1][level->cur_y] != nullptr) {
				location_->r = level->matrice_stanze[level->cur_x + 1][level->cur_y];
				location_->x = 2;
				level->cur_x += 1;
			} break;
		} getmaxyx(location_->r->win, max_y, max_x);
		//keypad(location_->r->win, true);
		touchwin(location_->r->win);
		location_->r->list->insert(this);
	}
}


bool Player::check_door() const {
	if (!check_collisions()) {
		switch (current_direction_) {
		case DIRECTION::UP:
			return location_->y <= 0 && location_->x >= max_x / 2 - 4 && location_->x <= max_x / 2 + 3;
		case DIRECTION::DOWN:
			return location_->y >= max_y - 1 && location_->x >= max_x / 2 - 4 && location_->x <= max_x / 2 + 3;
		case DIRECTION::LEFT:
			return location_->x <= 0 && location_->y >= max_y / 2 - 1 && location_->y <= max_y / 2 + 1;
		case DIRECTION::RIGHT:
			return location_->x + shape_->length >= max_x && location_->y >= max_y / 2 - 1 && location_->y <= max_y / 2 + 1;
		default: return false;
		}
	} return false;
}


bool Player::is_alive() {
	if (hp_ > 0) return true;
	else {
		state_ = ENDED;
		return false;
	}
}


void Player::handle_collision(COLLISION t, int hit_key) {
	switch (t) {

	case COLLISION::OBSTACLE: 
		Dynamic_Entity::handle_collision(COLLISION::OBSTACLE, -1);
		break;
	
	case COLLISION::ARTIFACT: {
		Dynamic_Entity::handle_collision(COLLISION::ARTIFACT, -1);
		const auto artf = dynamic_cast<Artifact*>(location_->r->list->search(hit_key));
		if (artf != nullptr) {
			if (artf->t_->equip_) {
				if (current_artifact_) // Abbandona il vecchio artefatto
					new Artifact{ current_artifact_, new Location{*artf->get_location()} };

				current_artifact_ = artf->t_;
				if (current_artifact_->f != nullptr) {
					// Aggiorna i timer dell'abilita'
					delete skill_duration_timer; delete skill_recharge_timer;

					skill_recharge_timer = new Timer{ current_artifact_->recharge_time };
					start_recharge_timer();

					if (current_artifact_->duration != NO_DURATION)
						skill_duration_timer = new Timer{ current_artifact_->duration };
					else skill_duration_timer = nullptr;
				}

				if (current_artifact_->prj != nullptr) {
					// Aggiorna i timer d'attacco
					current_projectile_ = current_artifact_->prj;
					delete attack_timer;
					attack_timer = new Timer{ current_projectile_->time_delay };
					attack_timer->start();
				}
			} 

			bombs += artf->t_->bombs;
			increase_hp(artf->t_->health);
		} 
	} break;
	
	case COLLISION::ENEMY: 
		Dynamic_Entity::handle_collision(COLLISION::ENEMY, hit_key);
		if (!armored)
			decrease_hp(hit_dmg);
		break;
	
	case COLLISION::PROJECTILE: {
		const auto prj = dynamic_cast<Projectile*>(location_->r->list->search(hit_key));
		if (prj != nullptr && prj->spawner_ != this && !armored)
			decrease_hp(prj->t->damage);
		break;
	}
	
	case COLLISION::EXPLOSION: {
		const auto expl = dynamic_cast<Explosion*>(location_->r->list->search(hit_key));
		if (expl) {
			const auto caster = dynamic_cast<Projectile*>(location_->r->list->search(expl->ref->key));
			if (caster != nullptr && caster->spawner_ != this)
				decrease_hp(explosion_dmg);
		} break;
	}

	default: break;
	}
}


Player::Player(Location* spawn)
: Dynamic_Entity{ &player_shape_up, spawn, COLLISION::PLAYER, player_hp },
current_artifact_{ nullptr }, current_projectile_{ &def_prj }, expr_{ 0 }, bombs{ 0 },
state_{ ONGOING }, armored{ false }, shape_style{ def_shapes }, attack_timer{ new Timer{current_projectile_->time_delay} },
skill_recharge_timer{ nullptr }, skill_duration_timer{ nullptr }, quit_timer{ nullptr }
{
	getmaxyx(location_->r->win, max_y, max_x);
	attack_timer->start();
}


Player::Player(Level* lvl, Player &pl)
:Dynamic_Entity{ pl.shape_, new Location{lvl, 13, 13, 25, 48 }, COLLISION::PLAYER, pl.hp_ },
current_artifact_{ pl.current_artifact_ }, current_projectile_{ pl.current_projectile_ }, shape_style{ pl.shape_style },
expr_{ pl.expr_ }, bombs{ pl.bombs }, armored{ pl.armored },  state_{ pl.state_ }, attack_timer{ pl.attack_timer },
skill_recharge_timer{ pl.skill_recharge_timer }, skill_duration_timer{ pl.skill_duration_timer }, quit_timer{ pl.quit_timer }
{
	getmaxyx(location_->r->win, max_y, max_x);
	attack_timer->start();
}


Player::~Player() {
	delete attack_timer;
}


void Player::attack(const DIRECTION d) {
	if (attack_timer->wait()) {
		if (strcmp(current_projectile_->name, "Burst") == 0) {
			for (const DIRECTION dir : { DIRECTION::UP, DIRECTION::DOWN, DIRECTION::LEFT, DIRECTION::RIGHT }) 
				new Projectile{ &burst, dir, this };
		} else {
			if (strcmp(current_projectile_->name, "Wave") == 0) {
				switch (d) {
				case DIRECTION::UP: new Projectile{ &wave_up, d, this }; break;
				case DIRECTION::DOWN:new Projectile{ &wave_down, d, this }; break;
				case DIRECTION::RIGHT:new Projectile{ &wave_right, d, this }; break;
				case DIRECTION::LEFT:new Projectile{ &wave_left, d, this }; break;
				}
			} else new Projectile{ current_projectile_, d, this };

			switch (d) {
			case DIRECTION::UP: shape_ = &shape_style[0]; break;
			case DIRECTION::DOWN: shape_ = &shape_style[1]; break;
			case DIRECTION::LEFT: shape_ = &shape_style[2]; break;
			case DIRECTION::RIGHT: shape_ = &shape_style[3]; break;
			default: break;
			}
		}
	}
}


void Player::throw_bomb() {
	new Bomb{ this };
	bombs--;
}


GAME_STATUS Player::gameState() const {
	return state_;
}


void Player::set_armor() {
	if (!armored) {
		armored = true;
		shape_style = armored_shapes;
	}
}


void Player::remove_armor() {
	if (armored) {
		armored = false;
		shape_style = def_shapes;
	}
}


void Player::gain_xp(int xp) {
	expr_ += xp;
}


void Player::start_recharge_timer() {
	if (skill_recharge_timer)
		skill_recharge_timer->start();

	if (skill_duration_timer)
		skill_duration_timer->stop();
}


void Player::start_duration_timer() {
	if (skill_duration_timer)
		skill_duration_timer->start();

	if (skill_recharge_timer)
		skill_recharge_timer->stop();
}