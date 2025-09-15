/**
 * @file Player.h
 * @brief Declaration of the Player class and related functions/constants.
 */

#pragma once

#include <optional>
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
    Player(std::string const& name_in, short const& round_in)
        : round(round_in)
        , name(name_in) {}

    /**
     * @brief Returns player's name.
     */
    virtual std::string const& get_name() const = 0;

    /**
     * @brief Returns player's current round.
     */
    virtual short const& get_round() const = 0;

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
    virtual void register_win() = 0;

    /**
     * @brief Virtual destructor for Player.
     */
    virtual ~Player() {}

protected:
    short round;
    std::string name;
    Hand hand;
};


/**
 * @brief Returns a pointer to a player with the given name and round.
 */
Player* Player_factory(std::string const& name, short const& round);

/**
 * @brief Prints player's name and current round to output stream.
 */
std::ostream& operator<<(std::ostream& os, Player const& p);


/**
 * @brief A computer player implementation of the Player interface.
 */
class ComputerPlayer : public Player {
public:
    ComputerPlayer(std::string const& name_in, short round_in)
        : Player(name_in, round_in) {}

    std::string const& get_name() const override { return name; }

    short const& get_round() const override { return round; }

    void reset_hand() override { hand.reset(); }

    void add_card(Card const& c) override { hand.add_card(c); }

    void register_win() override {
        if (round > 0) {
            --round;
        }
    }

    bool take_turn(Deck& deck) override {
        std::cout << name << "'s turn. Current hand: " << hand << std::endl;
        std::cout << "Top of discard pile: " << deck.peek_discard() << std::endl;

        Card card_to_play;
        if (hand.card_is_playable(deck.peek_discard())) {
            card_to_play = deck.take_discard();
            std::cout << name << " takes from discard pile: " << card_to_play << std::endl;
        } else {
            card_to_play = deck.deal_one();
            std::cout << name << " draws from deck: " << card_to_play << std::endl;
        }
        Card flipped_card = hand.play_card(card_to_play);
        std::cout << name << " discards: " << flipped_card << std::endl;
        deck.discard(flipped_card);
        return hand.is_completed();
    }
};
