/**
 * @file Hand.cpp
 * @brief Implementation of the Hand class and related functions.
 */

#include "Hand.h"

#include <algorithm>
#include <cstddef>
#include <print>
#include <utility>
#include <vector>

#include "Card.h"

void Hand::add_card(Card const& card) {
    cards.push_back(card);
    showing.push_back(false);
}

void Hand::reset() noexcept {
    cards.clear();
    showing.clear();
}

bool Hand::is_showing(size_t index) const noexcept {
    return index < showing.size() ? showing[index] : false;
}

bool Hand::is_completed() const noexcept {
    return std::ranges::all_of(showing, [](bool flag) { return flag; });
}

Card const& Hand::get_card(size_t index) const {
    return cards.at(index);
}

std::vector<Card> const& Hand::get_cards() const noexcept {
    return cards;
}

std::vector<bool> const& Hand::get_showing() const noexcept {
    return showing;
}

bool Hand::card_is_playable(Card const& card) const noexcept {
    int const rank = static_cast<int>(card.get_rank());
    if (cards.empty() || card.is_face() || std::cmp_greater(rank, cards.size())) {
        return false;
    }
    return !showing[static_cast<size_t>(rank) - 1];
}

Card Hand::play_card(Card const& card) {
    if (!card_is_playable(card)) {
        std::println("Card {} is not playable.", card);
        return card;
    }

    Card current = card;
    while (true) {
        auto const idx = static_cast<size_t>(static_cast<int>(current.get_rank()) - 1);
        Card const replaced = cards[idx];
        cards[idx] = current;
        bool const was_showing = showing[idx];
        showing[idx] = true;

        std::println("Played card: {}, replaced card: {}", current, replaced);

        // Stop if the replaced card was already face up or cannot be placed anywhere.
        if (was_showing || !card_is_playable(replaced)) {
            return replaced;
        }
        current = replaced;
    }
}
