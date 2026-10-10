/**
 * @file Card.h
 * @brief Declaration of the Card class and related functions/constants.
 */

#pragma once

#include <compare>
#include <cstdint>
#include <format>
#include <string>

class Card {
public:
    /**
     * @brief Strongly-typed card ranks. Ace = 1, King = 13.
     */
    enum class Rank : std::uint8_t { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

    /**
     * @brief Strongly-typed card suits. 0=Spades, 1=Hearts, 2=Clubs, 3=Diamonds
     */
    enum class Suit : std::uint8_t { SPADES = 0, HEARTS, CLUBS, DIAMONDS };

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
    [[nodiscard]] Rank get_rank() const noexcept;

    /**
     * @brief Gets the suit of the card.
     * @return The suit as enum Suit.
     */
    [[nodiscard]] Suit get_suit() const noexcept;

    /**
     * @brief Returns true if card is a face card (Jack, Queen, or King).
     * @return True if face card, false otherwise.
     */
    [[nodiscard]] bool is_face() const noexcept;

    /**
     * @brief Compares two cards by rank only; suit is deliberately ignored because it never
     * matters in Garbage (e.g. 5 of spades and 5 of hearts compare equal).
     */
    std::weak_ordering operator<=>(Card const& rhs) const noexcept { return rank <=> rhs.rank; }

    /**
     * @brief Returns true if both cards have the same rank; suit is ignored (see operator<=>).
     */
    bool operator==(Card const& rhs) const noexcept { return rank == rhs.rank; }

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
 * @brief Number of suits in a standard deck.
 */
inline constexpr int NUM_SUITS = 4;

/**
 * @brief Number of ranks in a standard deck.
 */
inline constexpr int NUM_RANKS = 13;

template <> struct std::formatter<Card> : std::formatter<std::string> {
    auto format(Card const& c, auto& ctx) const {
        std::string const s = Card::rank_to_string(c.get_rank()) + Card::suit_to_string(c.get_suit());
        return std::formatter<std::string>::format(s, ctx);
    }
};
