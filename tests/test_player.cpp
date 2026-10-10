/**
 * @file test_player.cpp
 * @brief Unit tests for the Player class and factory.
 */

#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <utility>
#include <vector>

#include "Card.h"
#include "Game.h"
#include "Player.h"

TEST_CASE("Player_factory creates a named computer player", "[player]") {
    auto player = Player_factory("Tester", 7);
    REQUIRE(player != nullptr);
    CHECK(player->get_name() == "Tester");
    CHECK(player->get_round() == 7);
    CHECK(player->get_hand().get_cards().empty());
}

TEST_CASE("register_win decrements the round and stops at zero", "[player]") {
    auto player = Player_factory("Tester", 1);
    player->register_win();
    CHECK(player->get_round() == 0);
    player->register_win();
    CHECK(player->get_round() == 0);
}

TEST_CASE("Cards added to a player go into their hand", "[player]") {
    auto player = Player_factory("Tester", 3);
    player->add_card(Card(Card::Rank::FIVE, Card::Suit::HEARTS));
    CHECK(player->get_hand().get_cards().size() == 1);

    player->reset_hand();
    CHECK(player->get_hand().get_cards().empty());
}

TEST_CASE("Constructing a Game has no side effects and rejects empty player lists", "[game]") {
    std::vector<std::unique_ptr<Player>> players;
    players.push_back(Player_factory("Player 1", 3));
    players.push_back(Player_factory("Player 2", 3));
    Game const game(std::move(players), true); // must not deal or print anything

    CHECK_THROWS_AS(Game({}, true), std::invalid_argument);
}
