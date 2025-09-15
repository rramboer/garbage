/**
 * @file Hand.h
 * @brief Declaration of the Hand class and related functions/constants.
 */

#pragma once

#include <iostream>
#include <vector>

#include "Card.h"

class Hand {
public:
    /**
     * @brief Default constructor for Hand.
     */
    Hand();

    /**
     * @brief Virtual destructor for Hand.
     */
    virtual ~Hand();

    /**
     * @brief Add a card to the hand (face down by default).
     * @param card The card to add.
     */
    void add_card(Card const& card);

    /**
     * @brief Remove all cards from the hand.
     */
    void reset();

    /**
     * @brief Set a card at the given index to face up or down.
     * @param index The index of the card.
     * @param face_up True to set face up, false for face down.
     */
    void set_showing(size_t index, bool face_up);

    /**
     * @brief Check if a card at the given index is face up.
     * @param index The index of the card.
     * @return True if the card is face up, false otherwise.
     */
    bool is_showing(size_t index) const;

    /**
     * @brief Determine if the hand is completed.
     * @return True if the hand is completed, false otherwise.
     */
    bool is_completed() const;

    /**
     * @brief Get the card at the given index.
     * @param index The index of the card.
     * @return The card at the index.
     */
    Card const& get_card(size_t index) const;

    /**
     * @brief Get all cards in the hand.
     * @return const reference to the vector of cards.
     */
    std::vector<Card> const& get_cards() const;

    /**
     * @brief Get all showing flags in the hand.
     * @return const reference to the vector of showing flags.
     */
    std::vector<bool> const& get_showing() const;

    /**
     * @brief Tests if a card is playable.
     * @param card The card to test.
     * @return True if the card is playable, false otherwise.
     */
    bool card_is_playable(Card const& card) const;

    /** @brief Executes a single play action with the given card.
     * @param card The card to play.
     * @return The card that was discarded after playing.
     */
    Card play_card(Card const& card);

private:
    std::vector<Card> cards;
    std::vector<bool> showing;
};

std::ostream& operator<<(std::ostream& os, Hand const& hand);