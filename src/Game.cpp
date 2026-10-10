/**
 * @file Game.cpp
 * @brief Implementation of the Game class.
 */

#include "Game.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <print>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Card.h"
#include "Player.h"

Game::Game(std::vector<std::unique_ptr<Player>> players_in, bool shuffle_enabled_in)
    : deck(shuffle_enabled_in)
    , players(std::move(players_in)) {
    if (players.empty()) {
        throw std::invalid_argument("Game requires at least one player");
    }
}

void Game::run() {
    std::vector<int> rounds;
    rounds.reserve(players.size());
    for (auto const& player : players) {
        rounds.push_back(player->get_round());
    }
    deal(rounds);
    discard_first_card();
    std::println("Game start!\n");
    while (play_round()) {}
    print_scores();
}

void Game::deal(std::vector<int> const& cards_per_player) {
    for (size_t i = 0; i < players.size(); ++i) {
        int const num_cards = cards_per_player[i];
        for (int j = 0; j < num_cards; ++j) {
            Card const dealt_card = deck.deal_one();
            players[i]->add_card(dealt_card);
            std::println("\n{} was dealt: {}", players[i]->get_name(), dealt_card);
        }
        std::println("{} was dealt {} {}.\n", players[i]->get_name(), num_cards, num_cards == 1 ? "card" : "cards");
    }
}

void Game::discard_first_card() {
    Card const first_card = deck.deal_one();
    deck.discard(first_card);
}

std::vector<bool> Game::take_turns() {
    std::vector<bool> players_won(players.size(), false);
    int cards_showing = total_cards_showing();
    int stalled_passes = 0;
    while (!std::ranges::any_of(players_won, [](bool won) { return won; })) {
        for (size_t i = 0; i < players.size(); ++i) {
            std::println("{}'s turn...", players[i]->get_name());
            players_won[i] = players[i]->take_turn(deck);
        }
        int const now_showing = total_cards_showing();
        if (now_showing == cards_showing) {
            if (++stalled_passes >= MAX_STALLED_PASSES) {
                throw std::runtime_error("Stalemate detected: no player has made progress in "
                                         + std::to_string(MAX_STALLED_PASSES) + " passes");
            }
        } else {
            stalled_passes = 0;
            cards_showing = now_showing;
        }
    }
    return players_won;
}

bool Game::game_over() const noexcept {
    return std::ranges::any_of(players, [](auto const& player) { return player->get_round() == 0; });
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
        for (auto const& player : players) {
            std::print("{}", *player);
        }
        std::println("");
    } else {
        std::println("===========\nGame over!");
        return false;
    }

    deck.redeal();

    std::vector<int> rounds_remaining;
    rounds_remaining.reserve(players.size());
    for (auto const& player : players) {
        rounds_remaining.push_back(player->get_round());
        player->reset_hand();
    }
    deal(rounds_remaining);
    discard_first_card();

    return true;
}

void Game::print_scores() const {
    std::println("Final Scores:");
    for (auto const& player : players) {
        if (player->get_round() == 0) {
            std::println("{} is the winner!", player->get_name());
        } else {
            std::println("{}: Round {}", player->get_name(), player->get_round());
        }
    }
}

int Game::total_cards_showing() const noexcept {
    int total = 0;
    for (auto const& player : players) {
        total += static_cast<int>(std::ranges::count(player->get_hand().get_showing(), true));
    }
    return total;
}
