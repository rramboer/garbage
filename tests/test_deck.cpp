/**
 * @file test_deck.cpp
 * @brief Unit tests for the Deck class.
 */

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstddef>
#include <stdexcept>

#include "Card.h"
#include "Deck.h"

TEST_CASE("A fresh deck holds 52 cards and an empty discard pile", "[deck]") {
    Deck const deck;
    CHECK(deck.size() == NUM_SUITS * NUM_RANKS);
    CHECK_FALSE(deck.empty());
    CHECK(deck.discard_pile_empty());
}

TEST_CASE("An unshuffled deck deals from the top in standard order", "[deck]") {
    Deck deck;
    // The draw pile is built suit by suit (spades..diamonds), ace..king, and dealt from the back.
    Card const first = deck.deal_one();
    CHECK(first.get_rank() == Card::Rank::KING);
    CHECK(first.get_suit() == Card::Suit::DIAMONDS);
    CHECK(deck.size() == 51);

    Card const second = deck.deal_one();
    CHECK(second.get_rank() == Card::Rank::QUEEN);
    CHECK(second.get_suit() == Card::Suit::DIAMONDS);
}

TEST_CASE("A shuffled deck still contains four of each rank", "[deck]") {
    Deck deck(true);
    std::array<int, NUM_RANKS + 1> rank_counts {};
    for (int i = 0; i < NUM_SUITS * NUM_RANKS; ++i) {
        ++rank_counts.at(static_cast<size_t>(deck.deal_one().get_rank()));
    }
    CHECK(deck.empty());
    for (int rank = 1; rank <= NUM_RANKS; ++rank) {
        CHECK(rank_counts.at(static_cast<size_t>(rank)) == NUM_SUITS);
    }
}

TEST_CASE("Discarding and taking from the discard pile is LIFO", "[deck]") {
    Deck deck;
    Card const five(Card::Rank::FIVE, Card::Suit::HEARTS);
    Card const jack(Card::Rank::JACK, Card::Suit::CLUBS);

    deck.discard(five);
    deck.discard(jack);
    CHECK_FALSE(deck.discard_pile_empty());

    CHECK(deck.peek_discard().get_rank() == Card::Rank::JACK);
    CHECK(deck.peek_discard().get_rank() == Card::Rank::JACK); // peek does not remove

    Card const taken = deck.take_discard();
    CHECK(taken.get_rank() == Card::Rank::JACK);
    CHECK(taken.get_suit() == Card::Suit::CLUBS);
    CHECK(deck.peek_discard().get_rank() == Card::Rank::FIVE);
}

TEST_CASE("Peeking or taking from an empty discard pile throws", "[deck]") {
    Deck deck;
    CHECK_THROWS_AS(deck.peek_discard(), std::out_of_range);
    CHECK_THROWS_AS(deck.take_discard(), std::out_of_range);
}

TEST_CASE("Dealing from an empty draw pile rebuilds it from the discard pile", "[deck]") {
    Deck deck;
    while (!deck.empty()) {
        deck.deal_one();
    }

    deck.discard(Card(Card::Rank::TWO, Card::Suit::SPADES));
    deck.discard(Card(Card::Rank::SEVEN, Card::Suit::HEARTS));
    deck.discard(Card(Card::Rank::QUEEN, Card::Suit::CLUBS));

    // The top discard (Q♣) stays in place; the rest becomes the new draw pile.
    Card const dealt = deck.deal_one();
    CHECK(dealt.get_rank() == Card::Rank::SEVEN);
    CHECK(deck.size() == 1);
    CHECK(deck.peek_discard().get_rank() == Card::Rank::QUEEN);
}

TEST_CASE("Dealing with no cards available anywhere throws", "[deck]") {
    Deck deck;
    while (!deck.empty()) {
        deck.deal_one();
    }
    CHECK_THROWS_AS(deck.deal_one(), std::runtime_error);

    // A lone discard is kept as the discard pile top, so it cannot be drawn either.
    deck.discard(Card(Card::Rank::ACE, Card::Suit::SPADES));
    CHECK_THROWS_AS(deck.deal_one(), std::runtime_error);
}

TEST_CASE("redeal restores a full ordered deck", "[deck]") {
    Deck deck;
    deck.deal_one();
    deck.discard(Card(Card::Rank::THREE, Card::Suit::HEARTS));

    deck.redeal();
    CHECK(deck.size() == NUM_SUITS * NUM_RANKS);
    CHECK(deck.discard_pile_empty());
    CHECK(deck.deal_one().get_rank() == Card::Rank::KING);
}
