/**
 * @file test_card.cpp
 * @brief Unit tests for the Card class.
 */

#include <catch2/catch_test_macros.hpp>

#include <format>

#include "Card.h"

TEST_CASE("Default card is the Ace of Spades", "[card]") {
    Card const card;
    CHECK(card.get_rank() == Card::Rank::ACE);
    CHECK(card.get_suit() == Card::Suit::SPADES);
}

TEST_CASE("Card stores its rank and suit", "[card]") {
    Card const card(Card::Rank::QUEEN, Card::Suit::DIAMONDS);
    CHECK(card.get_rank() == Card::Rank::QUEEN);
    CHECK(card.get_suit() == Card::Suit::DIAMONDS);
}

TEST_CASE("Only Jack, Queen, and King are face cards", "[card]") {
    CHECK(Card(Card::Rank::JACK, Card::Suit::SPADES).is_face());
    CHECK(Card(Card::Rank::QUEEN, Card::Suit::SPADES).is_face());
    CHECK(Card(Card::Rank::KING, Card::Suit::SPADES).is_face());

    CHECK_FALSE(Card(Card::Rank::ACE, Card::Suit::SPADES).is_face());
    CHECK_FALSE(Card(Card::Rank::TWO, Card::Suit::SPADES).is_face());
    CHECK_FALSE(Card(Card::Rank::TEN, Card::Suit::SPADES).is_face());
}

TEST_CASE("Cards compare by rank and ignore suit", "[card]") {
    Card const five_of_spades(Card::Rank::FIVE, Card::Suit::SPADES);
    Card const five_of_hearts(Card::Rank::FIVE, Card::Suit::HEARTS);
    Card const nine_of_clubs(Card::Rank::NINE, Card::Suit::CLUBS);

    CHECK(five_of_spades == five_of_hearts);
    CHECK(five_of_spades != nine_of_clubs);
    CHECK(five_of_spades < nine_of_clubs);
    CHECK(five_of_spades <= five_of_hearts);
    CHECK(nine_of_clubs > five_of_hearts);
    CHECK(nine_of_clubs >= nine_of_clubs);
}

TEST_CASE("Cards format as rank followed by suit symbol", "[card]") {
    CHECK(std::format("{}", Card(Card::Rank::ACE, Card::Suit::SPADES)) == "A♠");
    CHECK(std::format("{}", Card(Card::Rank::TEN, Card::Suit::HEARTS)) == "10♥");
    CHECK(std::format("{}", Card(Card::Rank::KING, Card::Suit::DIAMONDS)) == "K♦");
    CHECK(std::format("{}", Card(Card::Rank::TWO, Card::Suit::CLUBS)) == "2♣");
}
