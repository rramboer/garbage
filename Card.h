/**
 * @file Card.h
 * @brief Declaration of the Card class and related functions/constants.
 */

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
public:
    static constexpr char const* const RANK_ACE = "Ace";
    static constexpr char const* const RANK_TWO = "Two";
    static constexpr char const* const RANK_THREE = "Three";
    static constexpr char const* const RANK_FOUR = "Four";
    static constexpr char const* const RANK_FIVE = "Five";
    static constexpr char const* const RANK_SIX = "Six";
    static constexpr char const* const RANK_SEVEN = "Seven";
    static constexpr char const* const RANK_EIGHT = "Eight";
    static constexpr char const* const RANK_NINE = "Nine";
    static constexpr char const* const RANK_TEN = "Ten";
    static constexpr char const* const RANK_JACK = "Jack";
    static constexpr char const* const RANK_QUEEN = "Queen";
    static constexpr char const* const RANK_KING = "King";

    static constexpr char const* const SUIT_SPADES = "Spades";
    static constexpr char const* const SUIT_HEARTS = "Hearts";
    static constexpr char const* const SUIT_CLUBS = "Clubs";
    static constexpr char const* const SUIT_DIAMONDS = "Diamonds";


    /**
     * @brief Default constructor for Card.
     */
    Card();

    /**
     * @brief Initializes Card to specified rank and suit.
     * @param rank_in The rank of the card. Must be one of "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
     * "Nine", "Ten", "Jack", "Queen", "King", "Ace".
     * @param suit_in The suit of the card. Must be one of "Spades", "Hearts", "Clubs", "Diamonds".
     */
    Card(std::string const& rank_in, std::string const& suit_in);

    /**
     * @brief Gets the rank of the card.
     * @return The rank as a string.
     */
    std::string get_rank() const;

    /**
     * @brief Gets the suit of the card.
     * @return The suit as a string.
     */
    std::string get_suit() const;

    /**
     * @brief Returns true if card is a face card (Jack, Queen, King or Ace).
     * @return True if face card, false otherwise.
     */
    bool is_face() const;

private:
    std::string rank;
    std::string suit;
};


/**
 * @brief Suits in order from lowest suit to highest suit.
 */
constexpr char const* const SUIT_NAMES_BY_WEIGHT[]
    = { Card::SUIT_SPADES, Card::SUIT_HEARTS, Card::SUIT_CLUBS, Card::SUIT_DIAMONDS };
int const NUM_SUITS = 4;

/**
 * @brief Ranks in order from lowest rank to highest rank.
 */
constexpr char const* const RANK_NAMES_BY_WEIGHT[]
    = { Card::RANK_TWO,   Card::RANK_THREE, Card::RANK_FOUR, Card::RANK_FIVE, Card::RANK_SIX,
        Card::RANK_SEVEN, Card::RANK_EIGHT, Card::RANK_NINE, Card::RANK_TEN,  Card::RANK_JACK,
        Card::RANK_QUEEN, Card::RANK_KING,  Card::RANK_ACE };
int const NUM_RANKS = 13;

/**
 * @brief Returns true if lhs is lower value than rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is lower value than rhs.
 */
bool operator<(Card const& lhs, Card const& rhs);

/**
 * @brief Returns true if lhs is lower value than rhs or the same card as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is lower or equal to rhs.
 */
bool operator<=(Card const& lhs, Card const& rhs);

/**
 * @brief Returns true if lhs is higher value than rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is higher value than rhs.
 */
bool operator>(Card const& lhs, Card const& rhs);

/**
 * @brief Returns true if lhs is higher value than rhs or the same card as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is higher or equal to rhs.
 */
bool operator>=(Card const& lhs, Card const& rhs);

/**
 * @brief Returns true if lhs is same card as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is same card as rhs.
 */
bool operator==(Card const& lhs, Card const& rhs);

/**
 * @brief Returns true if lhs is not the same card as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is not the same card as rhs.
 */
bool operator!=(Card const& lhs, Card const& rhs);

/**
 * @brief Prints Card to stream, for example "Two of Spades".
 * @param os Output stream.
 * @param card Card to print.
 * @return Reference to output stream.
 */
std::ostream& operator<<(std::ostream& os, Card const& card);

#endif
