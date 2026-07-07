/**
 * @file Player.h
 * @brief Declaration of the Player class and related functions/constants.
 */

#pragma once

#include <format>
#include <memory>
#include <print>
#include <string>
#include <utility>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"

/**
 * @brief Represents a player in the game.
 */
class Player {
public:
    Player(std::string name_in, int round_in) noexcept
        : round(round_in)
        , name(std::move(name_in)) {}

    Player(Player const&) = delete;
    Player& operator=(Player const&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;

    /**
     * @brief Returns player's name.
     */
    [[nodiscard]] std::string const& get_name() const noexcept { return name; }

    /**
     * @brief Returns player's current round.
     */
    [[nodiscard]] int get_round() const noexcept { return round; }

    /**
     * @brief Returns the player's hand.
     */
    [[nodiscard]] Hand const& get_hand() const noexcept { return hand; }

    /**
     * @brief Adds Card to Player's hand.
     */
    virtual void add_card(Card const& c) = 0;

    /**
     * @brief Resets the player's hand.
     */
    virtual void reset_hand() = 0;

    /**
     * @brief Plays a turn according to their strategy. The card is removed from the player's hand
     * and discarded.
     * @param deck The deck from which to draw a card if needed.
     * @return true if the player completed their round in this turn. Otherwise false.
     */
    virtual bool take_turn(Deck& deck) = 0;

    /**
     * @brief Decreases the player's round by 1 upon winning a round.
     */
    virtual void register_win() noexcept = 0;

    /**
     * @brief Virtual destructor for Player.
     */
    virtual ~Player() = default;

protected:
    int round;
    std::string name;
    Hand hand;
};

/**
 * @brief Returns an owning pointer to a player with the given name and round.
 */
std::unique_ptr<Player> Player_factory(std::string name, int round);

/**
 * @brief A computer player implementation of the Player interface.
 */
class ComputerPlayer : public Player {
public:
    ComputerPlayer(std::string name_in, int round_in) noexcept
        : Player(std::move(name_in), round_in) {}

    void reset_hand() override { hand.reset(); }

    void add_card(Card const& c) override { hand.add_card(c); }

    void register_win() noexcept override {
        if (round > 0) [[likely]] {
            --round;
        }
    }

    bool take_turn(Deck& deck) override {
        std::println("{}'s turn. Current hand: {}", name, hand);
        std::println("Top of discard pile: {}", deck.peek_discard());

        Card card_to_play;
        if (hand.card_is_playable(deck.peek_discard())) {
            card_to_play = deck.take_discard();
            std::println("{} takes from discard pile: {}", name, card_to_play);
        } else {
            card_to_play = deck.deal_one();
            std::println("{} draws from deck: {}", name, card_to_play);
        }
        Card flipped_card = hand.play_card(card_to_play);
        std::println("{} discards: {}", name, flipped_card);
        deck.discard(flipped_card);
        return hand.is_completed();
    }
};

template <> struct std::formatter<Player> : std::formatter<std::string> {
    auto format(Player const& p, auto& ctx) const {
        std::string const s = p.get_name() + "\nRound: " + std::to_string(p.get_round()) + "\n";
        return std::formatter<std::string>::format(s, ctx);
    }
};
