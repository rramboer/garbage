/**
 * @file Game.h
 * @brief Declaration of the Game class.
 */

#pragma once

#include <memory>
#include <vector>

#include "Deck.h"
#include "Player.h"

/**
 * @brief Represents a game engine.
 *
 * The Game class manages the overall game flow, including player turns, dealing cards,
 * and handling the deck and discard pile. Constructing a Game only initializes state;
 * call run() to play a complete game.
 */
class Game {
public:
    /**
     * @brief Initializes the game with the given players. Each player is dealt according to their
     * current round once run() is called.
     * @param players_in The players participating in the game (ownership is transferred).
     * @param shuffle_enabled_in True to shuffle the deck at the start and whenever it is rebuilt.
     * @throws std::invalid_argument if players_in is empty.
     */
    Game(std::vector<std::unique_ptr<Player>> players_in, bool shuffle_enabled_in);

    /**
     * @brief Plays a complete game: deals, runs rounds until a player wins, and prints final scores.
     * @throws std::runtime_error if no player can make progress (stalemate safeguard).
     */
    void run();

private:
    void deal(std::vector<int> const& cards_per_player);
    void discard_first_card();
    std::vector<bool> take_turns();
    [[nodiscard]] bool game_over() const noexcept;
    bool play_round();
    void print_scores() const;
    [[nodiscard]] int total_cards_showing() const noexcept;

    /**
     * @brief Safety valve for take_turns(): if this many consecutive full passes produce no newly
     * face-up card for any player, the round is declared unwinnable and run() throws instead of
     * looping forever.
     */
    static constexpr int MAX_STALLED_PASSES = 1000;

    Deck deck;
    std::vector<std::unique_ptr<Player>> players;
};
