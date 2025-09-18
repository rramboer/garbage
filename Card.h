/**
 * @file Card.h
 * @brief Declaration of the Card class and related functions/constants.
 */

#pragma once


#include <array>
#include <format>
#include <iostream>
#include <string>

class Card {
public:
    /**
     * @brief Strongly-typed card ranks. Ace = 1, King = 13.
     */
    enum class Rank : short { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

    /**
     * @brief Strongly-typed card suits. 0=Spades, 1=Hearts, 2=Clubs, 3=Diamonds
     */
    enum class Suit : short { SPADES = 0, HEARTS, CLUBS, DIAMONDS };

    /**
     * @brief Default constructor for Card (Ace of Spades).
     */

    Card() noexcept;

    /**
     * @brief Initializes Card to specified rank and suit.
     * @param rank_in The rank of the card (enum Rank).
     * @param suit_in The suit of the card (enum Suit).
     */
    Card(Rank rank_in, Suit suit_in) noexcept;

    /**
     * @brief Gets the rank of the card.
     * @return The rank as enum Rank.
     */
    Rank get_rank() const noexcept;

    /**
     * @brief Gets the suit of the card.
     * @return The suit as enum Suit.
     */
    Suit get_suit() const noexcept;

    /**
     * @brief Returns true if card is a face card (Jack, Queen, King or Ace).
     * @return True if face card, false otherwise.
     */
    bool is_face() const noexcept;

    /**
     * @brief Returns the rank as a string (for display).
     */

    static std::string rank_to_string(Rank rank);

    /**
     * @brief Returns the suit as a string (for display).
     */
    static std::string suit_to_string(Suit suit);

private:
    Rank rank;
    Suit suit;
};


/**
 * @brief Suits in order from lowest suit to highest suit.
 */
constexpr Card::Suit SUIT_VALUES_BY_WEIGHT[]
    = { Card::Suit::SPADES, Card::Suit::HEARTS, Card::Suit::CLUBS, Card::Suit::DIAMONDS };
constexpr short NUM_SUITS = 4;

/**
 * @brief Ranks in order from lowest rank to highest rank.
 */
constexpr Card::Rank RANK_VALUES_BY_WEIGHT[]
    = { Card::Rank::ACE,  Card::Rank::TWO,   Card::Rank::THREE, Card::Rank::FOUR, Card::Rank::FIVE,
        Card::Rank::SIX,  Card::Rank::SEVEN, Card::Rank::EIGHT, Card::Rank::NINE, Card::Rank::TEN,
        Card::Rank::JACK, Card::Rank::QUEEN, Card::Rank::KING };
constexpr short NUM_RANKS = 13;

/**
 * @brief Returns true if lhs is lower value than rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is lower value than rhs.
 */
bool operator<(Card const& lhs, Card const& rhs) noexcept;

/**
 * @brief Returns true if lhs is lower value than rhs or the same card as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is lower or equal to rhs.
 */
bool operator<=(Card const& lhs, Card const& rhs) noexcept;

/**
 * @brief Returns true if lhs is higher value than rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is higher value than rhs.
 */
bool operator>(Card const& lhs, Card const& rhs) noexcept;

/**
 * @brief Returns true if lhs is higher value than rhs or the same card as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is higher or equal to rhs.
 */
bool operator>=(Card const& lhs, Card const& rhs) noexcept;

/**
 * @brief Returns true if lhs is the same rank as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is the same rank as rhs.
 */
bool operator==(Card const& lhs, Card const& rhs) noexcept;

/**
 * @brief Returns true if lhs is not the same rank as rhs.
 * @param lhs Left-hand side card.
 * @param rhs Right-hand side card.
 * @return True if lhs is not the same rank as rhs.
 */
bool operator!=(Card const& lhs, Card const& rhs) noexcept;

template <>
struct std::formatter<Card> : std::formatter<std::string> {
    auto format(Card const& c, auto& ctx) const noexcept {
        std::string s = Card::rank_to_string(c.get_rank()) + Card::suit_to_string(c.get_suit());
        return std::formatter<std::string>::format(s, ctx);
    }
};