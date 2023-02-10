#include <curses.h>
#include <clocale>
#include <chrono>
#include <thread>

#include "Artifact.hpp"
#include "GestioneSchermo.hpp"
#include "PrimaSchermata.hpp"
#include "Blueprint.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Game_over.hpp"

int main() {
	setlocale(LC_ALL, " ");
	initscr(); start_color();
	cbreak(); noecho(); curs_set(0);
	PrimaSchermata* menu = new PrimaSchermata{};

	/* game menu loop */
	while (true) {
		OPTION selected = menu->seleziona();

		if (selected == OPTION::GAME) {
			delete menu; clear(); refresh();

			Blueprint* map = bp_a->create_map_list(blueprint_list, TOT_STANZE_BASE);
			Level* lvl = new Level{ map };
			Player* player = lvl->generate();
			GestioneSchermo* screen = new GestioneSchermo{ player };
			Game_over* game_over = new Game_over{ player };

			/* game loop */
			while (player->gameState() != ENDED) {
				nodelay(player->get_location()->r->win, true);

				const chtype input = player->handle_input();
				if (lvl->cleared() && (input == 'n' || input == 'N')) {
					delete lvl;
					lvl = new Level{ map };
					Player* player_cpy = lvl->generate(player);
					player = player_cpy;
					screen->change_player(player);
				}

				player->get_location()->r->update(); screen->update();

				wrefresh(player->get_location()->r->win);
				std::this_thread::sleep_for(std::chrono::milliseconds(24));
				// Framerate: ~40 fps
			}

			game_over->update();
			game_over->go_back();

			/* end game code */
			menu = new PrimaSchermata{};
		}

		else if (selected == OPTION::COMMANDS)
			menu->command_menu();

		else if (selected == OPTION::QUIT)
			break;
	}

	endwin();
	return 0;
}