
#include "Hand.h"

Hand::Hand() = default;
Hand::~Hand() = default;

void Hand::add_card(Card const& card) {
    cards.push_back(card);
    showing.push_back(false);
}

void Hand::reset() {
    cards.clear();
    showing.clear();
}

void Hand::set_showing(size_t index, bool face_up) {
    if (index < showing.size()) {
        showing[index] = face_up;
    }
}

bool Hand::is_showing(size_t index) const {
    return index < showing.size() ? showing[index] : false;
}

bool Hand::is_completed() const {
    return std::all_of(showing.begin(), showing.end(), [](bool flag) { return flag; });
}

Card const& Hand::get_card(size_t index) const {
    return cards.at(index);
}

std::vector<Card> const& Hand::get_cards() const {
    return cards;
}

std::vector<bool> const& Hand::get_showing() const {
    return showing;
}

bool Hand::card_is_playable(Card const& card) const {
    short rank = static_cast<short>(card.get_rank());
    if (cards.empty() || rank > static_cast<short>(cards.size())) {
        return false;
    }
    return !showing[rank - 1];
}

Card Hand::play_card(Card const& card) {
    short idx = static_cast<short>(card.get_rank()) - 1;
    if (!card_is_playable(card)) {
        std::cout << "Card " << card << " is not playable." << std::endl;
        return card;
    }

    Card replaced = cards[idx];
    cards[idx] = card;
    bool was_showing = showing[idx];
    showing[idx] = true;

    std::cout << "Played card: " << card << ", replaced card: " << replaced << std::endl;

    // Stop recursion if replaced card is already face up or not playable
    short replaced_idx = static_cast<short>(replaced.get_rank()) - 1;
    if (was_showing || replaced_idx < 0 || static_cast<size_t>(replaced_idx) >= showing.size()
        || !card_is_playable(replaced)) {
        return replaced;
    }
    return play_card(replaced);
}

std::ostream& operator<<(std::ostream& os, Hand const& hand) {
    for (size_t i = 0; i < hand.get_cards().size(); ++i) {
        if (hand.is_showing(i)) {
            os << hand.get_card(i) << " ";
        } else {
            os << "XX ";
        }
    }
    return os;
}