#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

int const PLAYER_COUNT = 4;


class Game {
public:
    Game(std::vector<Player*> const& players_in, bool shuffle_enabled_in)
        : players(players_in)
        , deck() {
        shuffle_enabled_in ? deck.shuffle() : deck.reset();
        deal(deck.size() / players.size());
        print_hands();
    }

    void deal(int cards_per_player = 5) {
        for (int i = 0; i < cards_per_player; ++i) {
            for (auto* player : players) {
                player->add_card(deck.deal_one());
            }
        }
    }

    void print_hands() const {
        for (auto* player : players) {
            cout << *player << endl;
        }
    }

    ~Game() {
        for (auto* player : players) {
            delete player;
        }
    }

private:
    std::vector<Player*> players;
    Deck deck;
};

int main(int argc, char* argv[]) {
    bool shuffle_enabled = true;

    vector<Player*> players;
    for (int i = 0; i < PLAYER_COUNT; i++) {
        Player* player = Player_factory("Player " + to_string(i + 1), "Computer");
        players.push_back(player);
    }

    for (int i = 0; i < argc; i++) cout << argv[i] << " ";
    cout << endl;

    Game game(players, shuffle_enabled);

    return 0;
}
