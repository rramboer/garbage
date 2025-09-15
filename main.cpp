#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"

using namespace std;

/* Configuration constants for the game. */
namespace Config {
short const MAX_PLAYER_COUNT = 4;
short const MAX_STARTING_ROUND = 10;
constexpr bool VERBOSE_GAMEPLAY = true;
}

/**
 * @brief Represents a game engine.
 *
 * The Game class manages the overall game flow, including player turns, dealing cards,
 * and handling the deck and discard pile.
 */
class Game {
public:
    Game(std::vector<Player*> const& players_in, short starting_round_in, bool shuffle_enabled_in, bool verbose_in)
        : players(players_in)
        , deck()
        , starting_round(starting_round_in)
        , shuffle_enabled(shuffle_enabled_in)
        , verbose(verbose_in) {
        if (shuffle_enabled) {
            deck.shuffle();
        }
        deal(std::vector<short>(players.size(), starting_round));
        discard_first_card();
        cout << "Game start!" << endl << endl;
        while (play_round());
        print_scores();
    }

    void deal(std::vector<short> cards_per_player) {
        for (size_t i = 0; i < players.size(); ++i) {
            short const num_cards = cards_per_player[i];
            for (short j = 0; j < num_cards; ++j) {
                Card const dealt_card = deck.deal_one();
                players[i]->add_card(dealt_card);
                if (verbose) {
                    cout << players[i]->get_name() << " was dealt: " << dealt_card << endl;
                }
            }
            if (verbose) {
                cout << players[i]->get_name() << " was dealt " << num_cards << " cards." << endl << endl;
            }
        }
    }

    void discard_first_card() {
        Card first_card = deck.deal_one();
        deck.discard(first_card);
        if (verbose) {
            cout << "First card discarded: " << first_card << endl;
        }
    }

    std::vector<bool> take_turns() {
        std::vector<bool> players_won(players.size(), false);
        while (!std::any_of(players_won.begin(), players_won.end(), [](bool b) { return b; })) {
            for (size_t i = 0; i < players.size(); ++i) {
                auto* player = players[i];
                if (deck.empty()) {
                    deck.reset();
                    if (shuffle_enabled) {
                        deck.shuffle();
                    }
                }
                cout << player->get_name() << "'s turn..." << endl;
                players_won[i] = player->take_turn(deck);
            }
        }
        return players_won;
    }

    bool game_over() const {
        return std::any_of(players.begin(), players.end(), [](auto* p) { return p->get_round() == 0; });
    }

    bool play_round() {
        auto players_won = take_turns();
        for (size_t i = 0; i < players.size(); ++i) {
            if (players_won[i]) {
                players[i]->register_win();
            }
        }

        bool const is_game_over = game_over();

        if (verbose && !is_game_over) {
            cout << "===========\nRound over. Current scores:" << endl;
            for (auto* player : players) {
                cout << *player;
            }
            cout << endl;
        } else if (verbose && is_game_over) {
            cout << "===========\nGame over!" << endl;
            return false;
        }

        // TODO: Handle re-dealing cards if not game over.
        deck.redeal();
        if (shuffle_enabled) {
            deck.shuffle();
        }

        std::vector<short> rounds_remaining;
        for (auto* player : players) {
            rounds_remaining.push_back(player->get_round());
            player->reset_hand();
        }
        deal(rounds_remaining);
        discard_first_card();

        return true;
    }

    void print_scores() const {
        cout << "Final Scores:" << endl;
        for (auto* player : players) {
            if (player->get_round() == 0) {
                cout << player->get_name() << " is the winner!" << endl;
            } else {
                cout << player->get_name() << ": Round " << player->get_round() << endl;
            }
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
    short starting_round;
    bool shuffle_enabled;
    bool verbose;
};


int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 5) {
        cerr << "Usage: " << argv[0] << " num_players starting_round shuffle_enabled (opt)verbose" << endl;
        exit(1);
    }

    int num_players = stoi(argv[1]);

    int starting_round = stoi(argv[2]);

    std::string shuffle_enabled_in = string(argv[3]);
    std::transform(shuffle_enabled_in.begin(), shuffle_enabled_in.end(), shuffle_enabled_in.begin(), ::tolower);
    bool shuffle_enabled = (shuffle_enabled_in == "true" || shuffle_enabled_in == "1" || shuffle_enabled_in == "t");

    bool verbose = Config::VERBOSE_GAMEPLAY;
    if (argc == 5) {
        std::string verbose_in = string(argv[4]);
        std::transform(verbose_in.begin(), verbose_in.end(), verbose_in.begin(), ::tolower);
        verbose = (verbose_in == "true" || verbose_in == "1" || verbose_in == "t");
    }

    if (num_players < 1 || num_players > Config::MAX_PLAYER_COUNT) {
        cerr << "num_players must be between 1 and " << Config::MAX_PLAYER_COUNT << endl;
        exit(1);
    }

    if (starting_round < 1 || starting_round > Config::MAX_STARTING_ROUND) {
        cerr << "starting_round must be between 1 and " << Config::MAX_STARTING_ROUND << endl;
        exit(1);
    }

    vector<Player*> players;

    for (short i = 0; i < num_players; i++) {
        Player* player = Player_factory("Player " + to_string(i + 1), starting_round);
        players.push_back(player);
    }

    Game game(players, starting_round, shuffle_enabled, verbose);

    return 0;
}
