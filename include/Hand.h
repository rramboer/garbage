/**
 * @file Hand.h
 * @brief Declaration of the Hand class and related functions/constants.
 */

#pragma once

#include <format>
#include <string>
#include <vector>

#include "Card.h"

class Hand {
public:
    /**
     * @brief Add a card to the hand (face down by default).
     * @param card The card to add.
     */
    void add_card(Card const& card);

    /**
     * @brief Remove all cards from the hand.
     */
    void reset() noexcept;

    /**
     * @brief Check if a card at the given index is face up.
     * @param index The index of the card.
     * @return True if the card is face up, false otherwise.
     */
    [[nodiscard]] bool is_showing(size_t index) const noexcept;

    /**
     * @brief Determine if the hand is completed.
     * @return True if the hand is completed, false otherwise.
     */
    [[nodiscard]] bool is_completed() const noexcept;

    /**
     * @brief Get the card at the given index.
     * @param index The index of the card.
     * @return The card at the index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    [[nodiscard]] Card const& get_card(size_t index) const;

    /**
     * @brief Get all cards in the hand.
     * @return const reference to the vector of cards.
     */
    [[nodiscard]] std::vector<Card> const& get_cards() const noexcept;

    /**
     * @brief Get all showing flags in the hand.
     * @return const reference to the vector of showing flags.
     */
    [[nodiscard]] std::vector<bool> const& get_showing() const noexcept;

    /**
     * @brief Tests if a card is playable.
     * @param card The card to test.
     * @return True if the card is playable, false otherwise.
     */
    [[nodiscard]] bool card_is_playable(Card const& card) const noexcept;

    /** @brief Executes a single play action with the given card.
     * @param card The card to play.
     * @return The card that was discarded after playing.
     */
    Card play_card(Card const& card);

private:
    std::vector<Card> cards;
    std::vector<bool> showing;
};

template <> struct std::formatter<Hand> : std::formatter<std::string> {
    auto format(Hand const& h, auto& ctx) const {
        std::string s;
        for (size_t i = 0; i < h.get_cards().size(); ++i) {
            if (h.is_showing(i)) {
                s += std::format("{} ", h.get_card(i));
            } else {
                s += "XX ";
            }
        }
        return std::formatter<std::string>::format(s, ctx);
    }
};
