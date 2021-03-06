#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>

#include <fstream>
#include <sstream>
#include <string>

#include <thread>

#include "../include/model/entity.hpp"
#include "../include/model/player.hpp"
#include "../include/model/mapa.hpp"
#include "../include/view/view.hpp"
#include "../include/json.hpp"
#include "../include/controller/net.hpp"

using namespace std;

using nlohmann::json;

//controler
class update{
	public:
		//coord class with data and the size of time step
		void step(float T);
		update();
		~update();
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(update, Entities);
		int is_server();
	private:
		view Viewer;

		terrain Map;
		net udp;
		vector <entity> Entities;
		vector <Player> Players;

		std::thread t;
		int server=0;
		int client=0;

		int player_id=0;

		entity * spawns_entity(int type, int team, float x, float  y);
		void save();
		void load();
		void server_net();
		void client_net();

		void dig_grave(entity &player, float T, const Uint8 * plr_state);
		void move_player(entity &player, float T, const Uint8* player_state);
		void render_entity(entity &ent);

		const Uint8* state; // estado do teclado 
		int keyboard_vsize;
		//scans the enviroment for collisions in the proper direction
		float collision_up(entity &moved);
		float collision_down(entity &moved);
		float collision_left(entity &moved);
		float collision_right(entity &moved);

		float distance(entity &ent1,entity &ent2);
		void move_zombie(entity &zombie, float T);
		void attack_closest(entity &ent, float T);
		
};


