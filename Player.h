/**
 * @file Player.h
 * @brief Declaration of the Player class and related functions/constants.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Card.h"


class Player {
public:
    /**
     * @brief Returns player's name.
     */
    virtual std::string const& get_name() const = 0;

    /**
     * @brief Returns player's hand.
     */
    virtual std::vector<Card> const& get_hand() const = 0;

    /**
     * @brief Adds Card to Player's hand.
     */
    virtual void add_card(Card const& c) = 0;

    /**
     * @brief Plays one Card from Player's hand according to their strategy. The card is removed from the player's hand.
     */
    virtual Card play_card() = 0;

    /**
     * @brief Virtual destructor for Player.
     */
    virtual ~Player() {}
};


/**
 * @brief Returns a pointer to a player with the given name and strategy.
 */
Player* Player_factory(std::string const& name, std::string const& strategy);

/**
 * @brief Prints player's name to output stream.
 */
std::ostream& operator<<(std::ostream& os, Player const& p);

#endif
