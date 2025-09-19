#include "Game.h"

#include <algorithm>
#include <print>
#include <string>
#include <vector>

Game::Game(std::vector<Player*> const& players_in, short starting_round_in, bool shuffle_enabled_in)
    : deck()
    , players(players_in)
    , starting_round(starting_round_in)
    , shuffle_enabled(shuffle_enabled_in) {
    if (shuffle_enabled) {
        deck.shuffle();
    }
    deal(std::vector<short>(players.size(), starting_round));
    discard_first_card();
    std::println("Game start!\n");
    while (play_round());
    print_scores();
}

void Game::deal(std::vector<short> cards_per_player) {
    for (size_t i = 0; i < players.size(); ++i) {
        short const num_cards = cards_per_player[i];
        for (short j = 0; j < num_cards; ++j) {
            Card const dealt_card = deck.deal_one();
            players[i]->add_card(dealt_card);
            std::println("\n{} was dealt: {}", players[i]->get_name(), dealt_card);
        }
        std::println("{} was dealt {} {}.\n", players[i]->get_name(), num_cards, num_cards == 1 ? "card" : "cards");
    }
}

void Game::discard_first_card() {
    Card first_card = deck.deal_one();
    deck.discard(first_card);
}

std::vector<bool> Game::take_turns() {
    std::vector<bool> players_won(players.size(), false);
    while (!std::ranges::any_of(players_won.begin(), players_won.end(), [](bool b) { return b; })) {
        for (size_t i = 0; i < players.size(); ++i) {
            auto* player = players[i];
            if (deck.empty()) {
                deck.reset();
                if (shuffle_enabled) {
                    deck.shuffle();
                }
            }
            std::println("{}'s turn...", player->get_name());
            players_won[i] = player->take_turn(deck);
        }
    }
    return players_won;
}

bool Game::game_over() const noexcept {
    return std::ranges::any_of(players.begin(), players.end(), [](auto* p) { return p->get_round() == 0; });
}

bool Game::play_round() {
    auto players_won = take_turns();
    for (size_t i = 0; i < players.size(); ++i) {
        if (players_won[i]) {
            players[i]->register_win();
        }
    }

    bool const is_game_over = game_over();

    if (!is_game_over) {
        std::println("===========\nRound over. Current scores:");
        for (auto* player : players) {
            std::print("{}", *player);
        }
        std::println("");
    } else {
        std::println("===========\nGame over!");
        return false;
    }

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

void Game::print_scores() const {
    std::println("Final Scores:");
    for (auto* player : players) {
        if (player->get_round() == 0) {
            println("{} is the winner!", player->get_name());
        } else {
            println("{}: Round {}", player->get_name(), player->get_round());
        }
    }
}

Game::~Game() {
    for (auto* player : players) {
        delete player;
    }
}