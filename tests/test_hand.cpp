/**
 * @file test_hand.cpp
 * @brief Unit tests for the Hand class.
 */

#include <catch2/catch_test_macros.hpp>

#include "Card.h"
#include "Hand.h"

namespace {

Card make(Card::Rank rank, Card::Suit suit = Card::Suit::SPADES) {
    return { rank, suit };
}

}

TEST_CASE("A new hand is empty and counts as completed", "[hand]") {
    Hand const hand;
    CHECK(hand.get_cards().empty());
    CHECK(hand.is_completed()); // vacuously true: no face-down cards remain
}

TEST_CASE("Cards are added face down", "[hand]") {
    Hand hand;
    hand.add_card(make(Card::Rank::FOUR));
    hand.add_card(make(Card::Rank::NINE));

    CHECK(hand.get_cards().size() == 2);
    CHECK_FALSE(hand.is_showing(0));
    CHECK_FALSE(hand.is_showing(1));
    CHECK_FALSE(hand.is_completed());
    CHECK(hand.is_showing(99) == false); // out-of-range indices are simply not showing
}

TEST_CASE("card_is_playable follows the rules of Garbage", "[hand]") {
    Hand hand;

    SECTION("nothing is playable in an empty hand") {
        CHECK_FALSE(hand.card_is_playable(make(Card::Rank::ACE)));
    }

    SECTION("rank must fit within the hand and position must be face down") {
        hand.add_card(make(Card::Rank::KING));
        hand.add_card(make(Card::Rank::KING));
        hand.add_card(make(Card::Rank::KING));

        CHECK(hand.card_is_playable(make(Card::Rank::ACE)));
        CHECK(hand.card_is_playable(make(Card::Rank::THREE)));
        CHECK_FALSE(hand.card_is_playable(make(Card::Rank::FOUR))); // beyond hand size
        CHECK_FALSE(hand.card_is_playable(make(Card::Rank::JACK)));
        CHECK_FALSE(hand.card_is_playable(make(Card::Rank::QUEEN)));
        CHECK_FALSE(hand.card_is_playable(make(Card::Rank::KING)));

        hand.play_card(make(Card::Rank::THREE, Card::Suit::HEARTS));
        CHECK_FALSE(hand.card_is_playable(make(Card::Rank::THREE))); // position already filled
    }
}

TEST_CASE("play_card places a card and returns the replaced card", "[hand]") {
    Hand hand;
    hand.add_card(make(Card::Rank::KING)); // position 1
    hand.add_card(make(Card::Rank::QUEEN)); // position 2
    hand.add_card(make(Card::Rank::JACK)); // position 3

    Card const replaced = hand.play_card(make(Card::Rank::TWO, Card::Suit::HEARTS));
    CHECK(replaced.get_rank() == Card::Rank::QUEEN);
    CHECK(hand.get_card(1).get_rank() == Card::Rank::TWO);
    CHECK(hand.is_showing(1));
    CHECK_FALSE(hand.is_showing(0));
    CHECK_FALSE(hand.is_completed());
}

TEST_CASE("play_card chains through replaced playable cards", "[hand]") {
    Hand hand;
    hand.add_card(make(Card::Rank::TWO, Card::Suit::HEARTS)); // position 1 hides a playable 2
    hand.add_card(make(Card::Rank::ACE, Card::Suit::CLUBS)); // position 2 hides a playable ace
    hand.add_card(make(Card::Rank::KING)); // position 3 hides garbage

    // Playing an ace flips position 1, whose 2 flips position 2, whose ace is now unplayable.
    Card const discarded = hand.play_card(make(Card::Rank::ACE, Card::Suit::DIAMONDS));
    CHECK(discarded.get_rank() == Card::Rank::ACE);
    CHECK(discarded.get_suit() == Card::Suit::CLUBS);
    CHECK(hand.is_showing(0));
    CHECK(hand.is_showing(1));
    CHECK_FALSE(hand.is_showing(2));

    // Completing the last position finishes the hand.
    Card const last = hand.play_card(make(Card::Rank::THREE, Card::Suit::SPADES));
    CHECK(last.get_rank() == Card::Rank::KING);
    CHECK(hand.is_completed());
}

TEST_CASE("play_card returns an unplayable card unchanged", "[hand]") {
    Hand hand;
    hand.add_card(make(Card::Rank::FIVE));

    Card const returned = hand.play_card(make(Card::Rank::JACK, Card::Suit::HEARTS));
    CHECK(returned.get_rank() == Card::Rank::JACK);
    CHECK(returned.get_suit() == Card::Suit::HEARTS);
    CHECK_FALSE(hand.is_showing(0));
}

TEST_CASE("reset clears all cards and showing flags", "[hand]") {
    Hand hand;
    hand.add_card(make(Card::Rank::ACE));
    hand.play_card(make(Card::Rank::ACE, Card::Suit::HEARTS));
    CHECK(hand.is_completed());

    hand.reset();
    CHECK(hand.get_cards().empty());
    CHECK(hand.get_showing().empty());
}
