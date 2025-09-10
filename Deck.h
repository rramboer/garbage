/**
 * @file Deck.h
 * @brief Declaration of the Deck class and related functions/constants.
 */

#ifndef DECK_H
#define DECK_H


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
     * @brief Returns the next card in the deck and increments the next index.
     * @return The next Card in the deck.
     */
    Card deal_one();

    /**
     * @brief Resets next index to first card in the Deck.
     */
    void reset();

    /**
     * @brief Shuffles the Deck using a cryptographically secure random number generator.
     */
    void shuffle();

    /**
     * @brief Returns true if there are no more cards left in the deck.
     * @return True if deck is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Returns the number of cards in the Deck.
     * @return The number of cards in the Deck.
     */
    int size() const { return static_cast<int>(cards.size()); }

private:
    /**
     * @brief Default number of Cards in the Deck.
     */
    inline static constexpr int DEFAULT_DECK_SIZE = NUM_SUITS * NUM_RANKS;

    /**
     * @brief Cards in the Deck.
     */
    std::vector<Card> cards;

    /**
     * @brief Index of next card to be dealt.
     */
    int next;
};

#endif
