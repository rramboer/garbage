/**
 * @file Deck.cpp
 * @brief Implementation of the Deck class and related functions.
 */

#include "Deck.h"

#include <algorithm>
#include <random>
#include <stdexcept>

#include "Card.h"

Deck::Deck(bool shuffle_enabled_in)
    : shuffle_enabled(shuffle_enabled_in) {
    draw_pile.reserve(DEFAULT_DECK_SIZE);
    for (int suit = 0; suit < NUM_SUITS; ++suit) {
        for (int rank = 1; rank <= NUM_RANKS; ++rank) {
            draw_pile.emplace_back(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
        }
    }
    if (shuffle_enabled) {
        shuffle();
    }
}

Card Deck::deal_one() {
    if (empty()) {
        reset();
    }
    if (empty()) {
        throw std::runtime_error("Deck::deal_one: no cards available in the draw or discard pile");
    }
    Card dealt_card = draw_pile.back();
    draw_pile.pop_back();
    return dealt_card;
}

void Deck::reset() {
    if (!discard_pile_empty()) {
        Card const top_discard = peek_discard();
        discard_pile.pop_back();
        draw_pile.insert(draw_pile.end(), discard_pile.begin(), discard_pile.end());
        discard_pile.clear();
        discard_pile.push_back(top_discard);
        if (shuffle_enabled) {
            shuffle();
        }
    }
}

void Deck::redeal() {
    *this = Deck { shuffle_enabled };
}

void Deck::shuffle() {
    static std::mt19937_64 rng(std::random_device {}());
    std::ranges::shuffle(draw_pile, rng);
}

bool Deck::empty() const noexcept {
    return draw_pile.empty();
}

int Deck::size() const noexcept {
    return static_cast<int>(draw_pile.size());
}

bool Deck::discard_pile_empty() const noexcept {
    return discard_pile.empty();
}

Card const& Deck::peek_discard() const {
    if (discard_pile_empty()) {
        throw std::out_of_range("Discard pile is empty");
    }
    return discard_pile.back();
}

void Deck::discard(Card const& card) {
    discard_pile.push_back(card);
}

Card Deck::take_discard() {
    if (discard_pile_empty()) {
        throw std::out_of_range("Discard pile is empty");
    }
    Card top_card = discard_pile.back();
    discard_pile.pop_back();
    return top_card;
}
