/**
 * @file Card.cpp
 * @brief Implementation of the Card class and related functions.
 */

#include "Card.h"

using namespace std;


constexpr char const* const Card::RANK_TWO;
constexpr char const* const Card::RANK_THREE;
constexpr char const* const Card::RANK_FOUR;
constexpr char const* const Card::RANK_FIVE;
constexpr char const* const Card::RANK_SIX;
constexpr char const* const Card::RANK_SEVEN;
constexpr char const* const Card::RANK_EIGHT;
constexpr char const* const Card::RANK_NINE;
constexpr char const* const Card::RANK_TEN;
constexpr char const* const Card::RANK_JACK;
constexpr char const* const Card::RANK_QUEEN;
constexpr char const* const Card::RANK_KING;
constexpr char const* const Card::RANK_ACE;

constexpr char const* const Card::SUIT_SPADES;
constexpr char const* const Card::SUIT_HEARTS;
constexpr char const* const Card::SUIT_CLUBS;
constexpr char const* const Card::SUIT_DIAMONDS;

Card::Card()
    : rank(RANK_TWO)
    , suit(SUIT_SPADES) {}

Card::Card(string const& rank_in, string const& suit_in)
    : rank(rank_in)
    , suit(suit_in) {}

string Card::get_rank() const {
    return rank;
}

string Card::get_suit() const {
    return suit;
}

bool Card::is_face() const {
    return (rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING || rank == RANK_ACE);
}

bool operator<(Card const& lhs, Card const& rhs) {
    int rankIndex_lhs = -1;
    int rankIndex_rhs = -1;
    for (int rankIndex = 0; rankIndex < NUM_RANKS; rankIndex++) {
        if (RANK_NAMES_BY_WEIGHT[rankIndex] == lhs.get_rank()) {
            rankIndex_lhs = rankIndex;
        }
        if (RANK_NAMES_BY_WEIGHT[rankIndex] == rhs.get_rank()) {
            rankIndex_rhs = rankIndex;
        }
    }

    if (rankIndex_lhs < rankIndex_rhs) {
        return true;
    } else if (rankIndex_lhs > rankIndex_rhs) {
        return false;
    }

    int suitIndex_lhs = -1;
    int suitIndex_rhs = -1;
    for (int suitIndex = 0; suitIndex < NUM_SUITS; suitIndex++) {
        if (SUIT_NAMES_BY_WEIGHT[suitIndex] == lhs.get_suit()) {
            suitIndex_lhs = suitIndex;
        }
        if (SUIT_NAMES_BY_WEIGHT[suitIndex] == rhs.get_suit()) {
            suitIndex_rhs = suitIndex;
        }
    }
    return (suitIndex_lhs < suitIndex_rhs);
}

bool operator>(Card const& lhs, Card const& rhs) {
    return ((lhs != rhs) && !(lhs < rhs));
}

bool operator==(Card const& lhs, Card const& rhs) {
    return (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit());
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
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}
