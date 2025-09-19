/**
 * @file Deck.cpp
 * @brief Implementation of the Deck class and related functions.
 */

#include "Deck.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <ranges>

Deck::Deck() noexcept {
    discard_pile.clear();
    draw_pile.clear();
    draw_pile.reserve(DEFAULT_DECK_SIZE);
    for (auto suit : std::views::iota(0, static_cast<int>(NUM_SUITS))) {
        for (auto rank : std::views::iota(0, static_cast<int>(NUM_RANKS))) {
            draw_pile.emplace_back(RANK_VALUES_BY_WEIGHT[rank], static_cast<Card::Suit>(suit));
        }
    }
}

Card Deck::deal_one() noexcept {
    if (empty()) {
        reset();
    }
    Card dealt_card = draw_pile.back();
    draw_pile.pop_back();
    return dealt_card;
}

void Deck::reset() noexcept {
    if (!discard_pile_empty()) {
        Card top_discard = peek_discard();
        discard_pile.pop_back();
        draw_pile.insert(draw_pile.end(), discard_pile.begin(), discard_pile.end());
        discard_pile.clear();
        discard_pile.push_back(top_discard);
    }
}

void Deck::redeal() noexcept {
    *this = Deck {};
}

void Deck::shuffle() noexcept {
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

void Deck::discard(Card const& card) noexcept {
    discard_pile.push_back(card);
}

Card const Deck::take_discard() {
    if (discard_pile_empty()) {
        throw std::out_of_range("Discard pile is empty");
    }
    Card const& top_card = discard_pile.back();
    discard_pile.pop_back();
    return top_card;
}