/**
 * @file Deck.cpp
 * @brief Implementation of the Deck class and related functions.
 */

#include "Deck.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <ranges>

using namespace std;

Deck::Deck()
    : next(0) {
    cards.reserve(DEFAULT_DECK_SIZE);
    for (int suit = 0; suit < NUM_SUITS; suit++) {
        for (int rank = 0; rank < NUM_RANKS; rank++) {
            cards.emplace_back(RANK_NAMES_BY_WEIGHT[rank], SUIT_NAMES_BY_WEIGHT[suit]);
        }
    }
}

Card Deck::deal_one() {
    if (empty()) {
        throw out_of_range("No more cards in the deck.");
    }
    return cards[next++];
}

void Deck::reset() {
    next = 0;
}

void Deck::shuffle() {
    static std::mt19937_64 rng(std::random_device {}());
    std::ranges::shuffle(cards, rng);
    reset();
}

bool Deck::empty() const {
    return (next == static_cast<int>(cards.size()));
}
