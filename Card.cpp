/**
 * @file Card.cpp
 * @brief Implementation of the Card class and related functions.
 */

#include "Card.h"

#include <utility>

using namespace std;


Card::Card()
    : rank(Rank::ACE)
    , suit(Suit::SPADES) {}

Card::Card(Rank rank_in, Suit suit_in)
    : rank(rank_in)
    , suit(suit_in) {}

Card::Rank Card::get_rank() const {
    return rank;
}

Card::Suit Card::get_suit() const {
    return suit;
}

bool Card::is_face() const {
    return (rank == Rank::JACK || rank == Rank::QUEEN || rank == Rank::KING);
}

std::string Card::rank_to_string(Rank rank) {
    switch (rank) {
    case Rank::ACE:
        return "A";
    case Rank::TWO:
        return "2";
    case Rank::THREE:
        return "3";
    case Rank::FOUR:
        return "4";
    case Rank::FIVE:
        return "5";
    case Rank::SIX:
        return "6";
    case Rank::SEVEN:
        return "7";
    case Rank::EIGHT:
        return "8";
    case Rank::NINE:
        return "9";
    case Rank::TEN:
        return "10";
    case Rank::JACK:
        return "J";
    case Rank::QUEEN:
        return "Q";
    case Rank::KING:
        return "K";
    default:
        std::unreachable();
    }
}

std::string Card::suit_to_string(Suit suit) {
    switch (suit) {
    case Suit::SPADES:
        return "♠";
    case Suit::HEARTS:
        return "♥";
    case Suit::CLUBS:
        return "♣";
    case Suit::DIAMONDS:
        return "♦";
    default:
        std::unreachable();
    }
}

bool operator<(Card const& lhs, Card const& rhs) {
    return (static_cast<short>(lhs.get_rank()) < static_cast<short>(rhs.get_rank()));
}


bool operator>(Card const& lhs, Card const& rhs) {
    return ((lhs != rhs) && !(lhs < rhs));
}

bool operator==(Card const& lhs, Card const& rhs) {
    return lhs.get_rank() == rhs.get_rank();
}

bool operator!=(Card const& lhs, Card const& rhs) {
    return !(lhs == rhs);
}

bool operator>=(Card const& lhs, Card const& rhs) {
    return ((lhs == rhs) || (lhs > rhs));
}

bool operator<=(Card const& lhs, Card const& rhs) {
    return ((lhs == rhs) || (lhs < rhs));
}


ostream& operator<<(ostream& os, Card const& card) {
    os << Card::rank_to_string(card.get_rank()) << Card::suit_to_string(card.get_suit());
    return os;
}
