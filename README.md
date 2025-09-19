# Garbage (Card Game)

A modern, type-safe, and maintainable C++ card game engine. This project demonstrates best practices in C++, including strong typing, modern build automation, and clean code organization.

## Rules

Garbage (also known as Trash) is a simple card game for up to 4 players. The goal is to be the first player to fill all positions in your hand with cards in the correct order, reducing your hand size each round until you win.

### Setup

- Each player starts with a hand of 10 face-down cards (or fewer in later rounds).
- The remaining cards form a draw pile, and one card is placed face-up as the discard pile.

### Gameplay

1. On your turn, you draw either the top card from the draw pile or the discard pile.
2. If the card is an Ace through 10, you place it face-up in the corresponding position in your hand (Ace = position 1, 2 = position 2, ..., 10 = position 10). You then pick up the card that was previously in that position and repeat the process.
3. If you draw a Jack, Queen, or King, it is a "garbage" card and cannot be placed in your hand. Discard it to end your turn.
4. If you pick up a card that cannot be placed (because its position is already filled or it is a face card), discard it to end your turn.
5. Play passes to the next player.

### Winning a Round

- The first player to fill all positions in their hand with the correct cards wins the round.
- That player reduces their hand size by one for the next round (e.g., from 10 to 9 cards).
- The first player to complete a hand of just one card wins the game.

### Additional Notes

- Jacks, Queens, and Kings are always garbage and cannot be placed in your hand.
- If the draw pile runs out, reshuffle the discard pile to form a new draw pile.

This implementation automates the rules and manages the deck, hands, and turns for you.

## Features

- **Strongly-Typed Card System:**
  - Uses `enum class` for card ranks and suits for type safety.
  - Custom formatting for cards, hands, and players using C++23/26 `std::print` and `std::formatter`.
- **Game Engine:**
  - Flexible, extensible `Game` class for managing players, deck, and game flow.
  - `Player` abstraction with support for computer players and easy extension.
  - Robust gameplay logic with clear separation of concerns.
- **Modern Build System:**
  - Makefile supports automatic dependency tracking and out-of-source builds.
  - All build artifacts (`.o`, `.d`) are placed in a dedicated `build/` directory.
  - Source files in `src/`, headers in `include/`.

## Directory Structure

```
garbage/
├── include/         # Header files
├── src/             # Source files
├── build/           # Build artifacts (.o, .d files, created automatically)
├── Makefile         # Modern, robust build system
└── README.md        # Documentation
```

## Build Instructions

1. **Requirements:**

   - GCC 14+ or Clang with C++26 support
   - GNU Make

2. **Build the project:**

   ```sh
   make
   ```

   This will compile all sources and place build artifacts in the `build/` directory.

3. **Run the game:**

   ```sh
   ./main <num_players> <starting_round> <shuffle_enabled>
   # Example:
   ./main 2 10 true
   ```

   - `num_players`: Number of players (1-4)
   - `starting_round`: Starting round number (1-10)
   - `shuffle_enabled`: true/false/1/0/t/f (case-insensitive)

4. **Clean the build:**
   ```sh
   make clean
   ```

## Code Highlights

- **Modern Output:**
  - Uses `std::print` and custom formatters for clean, readable output.
- **Extensible Design:**
  - Add new player types or game rules by extending the `Player` or `Game` classes.
- **Automatic Dependency Tracking:**
  - Makefile generates and includes `.d` files for robust incremental builds.

## Contributing

Contributions are welcome! Please open issues or pull requests for improvements, bug fixes, or new features.
