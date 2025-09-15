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

Deck::Deck() {
    discard_pile.clear();
    draw_pile.reserve(DEFAULT_DECK_SIZE);
    for (short suit = 0; suit < NUM_SUITS; ++suit) {
        for (short i = 0; i < NUM_RANKS; ++i) {
            draw_pile.emplace_back(RANK_VALUES_BY_WEIGHT[i], static_cast<Card::Suit>(suit));
        }
    }
}

Card Deck::deal_one() {
    if (empty()) {
        reset();
    }
    Card dealt_card = draw_pile.back();
    draw_pile.pop_back();
    return dealt_card;
}

void Deck::reset() {
    if (!discard_pile_empty()) {
        Card top_discard = peek_discard();
        discard_pile.pop_back();
        draw_pile.insert(draw_pile.end(), discard_pile.begin(), discard_pile.end());
        discard_pile.clear();
        discard_pile.push_back(top_discard);
    }
}

void Deck::redeal() {
    discard_pile.clear();
    draw_pile.clear();
    draw_pile.reserve(DEFAULT_DECK_SIZE);
    for (short suit = 0; suit < NUM_SUITS; ++suit) {
        for (short i = 0; i < NUM_RANKS; ++i) {
            draw_pile.emplace_back(RANK_VALUES_BY_WEIGHT[i], static_cast<Card::Suit>(suit));
        }
    }
}

void Deck::shuffle() {
    static std::mt19937_64 rng(std::random_device {}());
    std::ranges::shuffle(draw_pile, rng);
}

bool Deck::empty() const {
    return draw_pile.empty();
}

bool Deck::discard_pile_empty() const {
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

Card const& Deck::take_discard() {
    if (discard_pile_empty()) {
        throw std::out_of_range("Discard pile is empty");
    }
    Card const& top_card = discard_pile.back();
    discard_pile.pop_back();
    return top_card;
}