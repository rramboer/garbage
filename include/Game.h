#pragma once

#include <vector>

#include "Deck.h"
#include "Player.h"

/**
 * @brief Represents a game engine.
 *
 * The Game class manages the overall game flow, including player turns, dealing cards,
 * and handling the deck and discard pile.
 */
class Game {
public:
    Game(std::vector<Player*> const& players_in, short starting_round_in, bool shuffle_enabled_in);
    void deal(std::vector<short> cards_per_player);
    void discard_first_card();
    std::vector<bool> take_turns();
    bool game_over() const noexcept;
    bool play_round();
    void print_scores() const;
    ~Game();

private:
    Deck deck;
    std::vector<Player*> players;
    short starting_round;
    bool shuffle_enabled;
};
