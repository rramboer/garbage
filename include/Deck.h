/**
 * @file Deck.h
 * @brief Declaration of the Deck class and related functions/constants.
 */

#pragma once

#include <vector>

#include "Card.h"

class Deck {
public:
    /**
     * @brief Initializes the Deck to be in the following standard order:
     * The cards of the lowest suit arranged from lowest rank to highest rank, followed by the cards of the next lowest
     * suit in order from lowest to highest rank, and so on. If shuffling is enabled, the fresh deck is then shuffled,
     * and every subsequent reset()/redeal() reshuffles as well.
     * @param shuffle_enabled_in True to shuffle the deck now and whenever it is rebuilt.
     */
    explicit Deck(bool shuffle_enabled_in = false);

    /**
     * @brief Returns the next card in the deck and removes it from the deck. If the draw pile is empty, it is reset
     * from the discard pile first.
     * @return The next Card in the deck.
     * @throws std::runtime_error if no card is available in either pile. Callers must keep at least two cards
     * circulating outside players' hands (the CLI limits of 4 players and round 10 guarantee this).
     */
    Card deal_one();

    /**
     * @brief Resets the deck by moving all cards from the discard pile back into the draw pile, keeping the top
     * discard in place. The rebuilt draw pile is reshuffled if shuffling is enabled.
     */
    void reset();

    /**
     * @brief Resets the deck to a full, ordered deck (reshuffled if shuffling is enabled).
     */
    void redeal();

    /**
     * @brief Shuffles the draw pile using a Mersenne Twister PRNG seeded once from std::random_device.
     */
    void shuffle();

    /**
     * @brief Returns true if there are no more cards left in the draw pile.
     * @return True if draw pile is empty, false otherwise.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Returns true if the discard pile is empty.
     * @return True if discard pile is empty, false otherwise.
     */
    [[nodiscard]] bool discard_pile_empty() const noexcept;

    /**
     * @brief Returns the number of cards in the draw pile.
     * @return The number of cards in the draw pile.
     */
    [[nodiscard]] int size() const noexcept;

    /**
     * @brief Returns the top card in the discard pile without removing it.
     * @return The top Card in the discard pile.
     * @throws std::out_of_range if the discard pile is empty.
     */
    [[nodiscard]] Card const& peek_discard() const;

    /**
     * @brief Places a card into the discard pile.
     * @param card The Card to discard.
     */
    void discard(Card const& card);

    /**
     * @brief Takes the top card from the discard pile and returns it.
     * @return The top Card from the discard pile.
     * @throws std::out_of_range if the discard pile is empty.
     */
    Card take_discard();

private:
    /**
     * @brief Default number of Cards in the Deck.
     */
    static constexpr int DEFAULT_DECK_SIZE = NUM_SUITS * NUM_RANKS;

    /**
     * @brief True if the deck reshuffles whenever it is rebuilt.
     */
    bool shuffle_enabled = false;

    /**
     * @brief Cards in the Deck.
     */
    std::vector<Card> draw_pile;

    /**
     * @brief Cards in the discard pile.
     */
    std::vector<Card> discard_pile;
};
