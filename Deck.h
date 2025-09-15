/**
 * @file Deck.h
 * @brief Declaration of the Deck class and related functions/constants.
 */

#pragma once

#include <string>
#include <vector>

#include "Card.h"


class Deck {
public:
    /**
     * @brief Initializes the Deck to be in the following standard order:
     * The cards of the lowest suit arranged from lowest rank to highest rank, followed by the cards of the next lowest
     * suit in order from lowest to highest rank, and so on.
     */
    Deck();

    /**
     * @brief Returns the next card in the deck and removes it from the deck. If the deck is empty, it is reset first.
     * @return The next Card in the deck.
     */
    Card deal_one();

    /**
     * @brief Resets the deck by moving all cards from the discard pile back into the draw pile, and then discarding the
     * top card.
     */
    void reset();

    /**
     * @brief Resets the deck to a full, ordered deck.
     */
    void redeal();

    /**
     * @brief Shuffles the Deck using a cryptographically secure random number generator.
     */
    void shuffle();

    /**
     * @brief Returns true if there are no more cards left in the draw pile.
     * @return True if draw pile is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Returns true if the discard pile is empty.
     * @return True if discard pile is empty, false otherwise.
     */
    bool discard_pile_empty() const;

    /**
     * @brief Returns the number of cards in the Deck.
     * @return The number of cards in the Deck.
     */
    int size() const { return static_cast<int>(draw_pile.size()); }

    /**
     * @brief Returns the top card in the discard pile without removing it.
     * @return The top Card in the discard pile.
     */
    Card const& peek_discard() const;

    /**
     * @brief Places a card into the discard pile.
     * @param card The Card to discard.
     */
    void discard(Card const& card);

    /**
     * @brief Takes the top card from the discard pile and returns it.
     * @return The top Card from the discard pile.
     */
    Card const& take_discard();

private:
    /**
     * @brief Default number of Cards in the Deck.
     */
    inline static constexpr int DEFAULT_DECK_SIZE = NUM_SUITS * NUM_RANKS;

    // Use Card::Rank and Card::Suit for value arrays
    static constexpr Card::Suit SUIT_VALUES_BY_WEIGHT[4]
        = { Card::Suit::SPADES, Card::Suit::HEARTS, Card::Suit::CLUBS, Card::Suit::DIAMONDS };
    static constexpr Card::Rank RANK_VALUES_BY_WEIGHT[13]
        = { Card::Rank::ACE,  Card::Rank::TWO,   Card::Rank::THREE, Card::Rank::FOUR, Card::Rank::FIVE,
            Card::Rank::SIX,  Card::Rank::SEVEN, Card::Rank::EIGHT, Card::Rank::NINE, Card::Rank::TEN,
            Card::Rank::JACK, Card::Rank::QUEEN, Card::Rank::KING };

    /**
     * @brief Cards in the Deck.
     */
    std::vector<Card> draw_pile;

    /**
     * @brief Cards in the discard pile.
     */
    std::vector<Card> discard_pile;
};
