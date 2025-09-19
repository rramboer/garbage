#include <algorithm>
#include <fstream>
#include <print>
#include <string>
#include <vector>

#include "Card.h"
#include "Deck.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"
#include "const.h"


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " num_players starting_round shuffle_enabled" << std::endl;
        exit(1);
    }

    int num_players = std::stoi(argv[1]);

    int starting_round = std::stoi(argv[2]);

    std::string shuffle_enabled_in(argv[3]);
    std::transform(shuffle_enabled_in.begin(), shuffle_enabled_in.end(), shuffle_enabled_in.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    bool shuffle_enabled = (shuffle_enabled_in == "true" || shuffle_enabled_in == "1" || shuffle_enabled_in == "t");

    if (num_players < 1 || num_players > Config::MAX_PLAYER_COUNT) {
        std::cerr << "num_players must be between 1 and " << Config::MAX_PLAYER_COUNT << std::endl;
        exit(1);
    }

    if (starting_round < 1 || starting_round > Config::MAX_STARTING_ROUND) {
        std::cerr << "starting_round must be between 1 and " << Config::MAX_STARTING_ROUND << std::endl;
        exit(1);
    }

    std::vector<Player*> players;

    for (short i = 0; i < num_players; i++) {
        Player* player = Player_factory("Player " + std::to_string(i + 1), starting_round);
        players.push_back(player);
    }

    Game game(players, starting_round, shuffle_enabled);

    return 0;
}
