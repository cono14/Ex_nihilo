#ifndef SECRET_ROOM_HPP
#define SECRET_ROOM_HPP
#include "Room.hpp"


class Secret_Room : public Room {
public:
	Secret_Room(Level* lvl, int x, int y);
}; typedef Secret_Room* p_secret_room;

static constexpr char mappa_secret[30][101]={
	"                                 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                    ",	
	"                       % %% %%% %%                             % %%% % %                            ",
	"                    %% %                                                 %%% %%                     ",
	"                 %% %                                                           %%%                 ",
	"              %%%                                                                  %%               ",
	"           % %%                                                                       %%            ",
	"         %%                                                                             %%          ",
	"       %%%%                                                                               %%        ",
	"      %%                                                                                    %%      ",
	"    %%                                                                                       %%%    ",
	"  %%                                                                                           %%  ",
	" %%                                                                                              % ",
	"%%                                                                                                %",
	"%                                                                                                  %",//
	"%                                                                                                  %",//
	"%                                                                                                  %",//
	"%                                                                                                  %",
	"%%                                                                                                 %",
	" %%%                                                                                              % ",
	"  %%                                                                                            %%  ",
	"    %%                                                                                         %    ",
	"     %%                                                                                     % %     ",
	"       %%                                                                                  %        ",
	"         %%                                                                             %%          ",
	"           %%%                                                                       %%%            ",
	"               %%                                                                 %%                ",
	"                 %% %                                                          %%                   ",
	"                   % %                                                %% %%% %                      ",
	"                       %%%% %%% %%                            %%%% % %                              ",
	"                                  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                     ",	
};
#endif
