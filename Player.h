/**
 * @file Player.h
 * @brief Declaration of the Player class and related functions/constants.
 */

#pragma once

#include <format>
#include <optional>
#include <print>
#include <string>
#include <vector>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"

/**
 * @brief Represents a player in the game.
 */
class Player {
public:
    Player(std::string const name_in, short const round_in) noexcept
        : round(round_in)
        , name(name_in) {}

    /**
     * @brief Returns player's name.
     */
    virtual std::string const& get_name() const noexcept = 0;

    /**
     * @brief Returns player's current round.
     */
    virtual short const& get_round() const noexcept = 0;

    /**
     * @brief Adds Card to Player's hand.
     */
    virtual void add_card(Card const& c) noexcept = 0;

    /**
     * @brief Resets the player's hand.
     */
    virtual void reset_hand() noexcept = 0;

    /**
     * @brief Plays a turn according to their strategy. The card is removed from the player's hand
     * and discarded.
     * @param deck The deck from which to draw a card if needed.
     * @return true if the player completed their round in this turn. Otherwise false.
     */
    virtual bool take_turn(Deck& deck) noexcept = 0;

    /**
     * @brief Decreases the player's round by 1 upon winning a round.
     */
    virtual void register_win() noexcept = 0;

    /**
     * @brief Virtual destructor for Player.
     */
    virtual ~Player() noexcept {}

protected:
    short round;
    std::string name;
    Hand hand;
};


/**
 * @brief Returns a pointer to a player with the given name and round.
 */
Player* Player_factory(std::string const name, short const round);


/**
 * @brief A computer player implementation of the Player interface.
 */
class ComputerPlayer : public Player {
public:
    ComputerPlayer(std::string const& name_in, short round_in) noexcept
        : Player(name_in, round_in) {}

    std::string const& get_name() const noexcept override { return name; }

    short const& get_round() const noexcept override { return round; }

    void reset_hand() noexcept override { hand.reset(); }

    void add_card(Card const& c) noexcept override { hand.add_card(c); }

    void register_win() noexcept override {
        if (round > 0) [[likely]] {
            --round;
        }
    }

    bool take_turn(Deck& deck) noexcept override {
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

template <>
struct std::formatter<Player> : std::formatter<std::string> {
    auto format(Player const& p, auto& ctx) const noexcept {
        std::string s = p.get_name() + "\nRound: " + std::to_string(p.get_round()) + "\n";
        return std::formatter<std::string>::format(s, ctx);
    }
};