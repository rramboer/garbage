
#include "Hand.h"

#include <algorithm>
#include <print>


Hand::Hand() noexcept = default;
Hand::~Hand() noexcept = default;

void Hand::add_card(Card const& card) noexcept {
    cards.push_back(card);
    showing.push_back(false);
}

void Hand::reset() noexcept {
    cards.clear();
    showing.clear();
}

void Hand::set_showing(size_t index, bool face_up) noexcept {
    if (index < showing.size()) {
        showing[index] = face_up;
    }
}

bool Hand::is_showing(size_t index) const noexcept {
    return index < showing.size() ? showing[index] : false;
}

bool Hand::is_completed() const noexcept {
    return std::ranges::all_of(showing.begin(), showing.end(), [](bool flag) { return flag; });
}

Card const& Hand::get_card(size_t index) const noexcept {
    return cards.at(index);
}

std::vector<Card> const& Hand::get_cards() const noexcept {
    return cards;
}

std::vector<bool> const& Hand::get_showing() const noexcept {
    return showing;
}

bool Hand::card_is_playable(Card const& card) const noexcept {
    short rank = static_cast<short>(card.get_rank());
    if (cards.empty() || rank > static_cast<short>(cards.size())) {
        return false;
    }
    return !showing[rank - 1];
}

Card Hand::play_card(Card const& card) noexcept {
    short idx = static_cast<short>(card.get_rank()) - 1;
    if (!card_is_playable(card)) {
        std::println("Card {} is not playable.", card);
        return card;
    }

    Card replaced = cards[idx];
    cards[idx] = card;
    bool was_showing = showing[idx];
    showing[idx] = true;

    std::println("Played card: {}, replaced card: {}", card, replaced);

    // Stop recursion if replaced card is already face up or not playable
    short replaced_idx = static_cast<short>(replaced.get_rank()) - 1;
    if (was_showing || replaced_idx < 0 || static_cast<size_t>(replaced_idx) >= showing.size()
        || !card_is_playable(replaced)) {
        return replaced;
    }
    return play_card(replaced);
}
