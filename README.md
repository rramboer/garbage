# Garbage (Card Game)

[![CI](https://github.com/rramboer/garbage/actions/workflows/ci.yml/badge.svg)](https://github.com/rramboer/garbage/actions/workflows/ci.yml)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A modern, type-safe, and maintainable C++ card game engine. This project demonstrates best practices in C++, including strong typing, modern build automation, unit testing, and clean code organization.

All players are computer-controlled: the program simulates a complete game from start to finish and prints a turn-by-turn transcript. A human `Player` subclass is a natural extension point (see [Extending](#extending)).

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
- If the draw pile runs out, the discard pile (minus its top card) forms a new draw pile — reshuffled when shuffling is enabled.

This implementation automates the rules and manages the deck, hands, and turns for you.

## Features

- **Strongly-Typed Card System:**
  - Uses `enum class` for card ranks and suits for type safety.
  - Custom formatting for cards, hands, and players using C++23 `std::print` and `std::formatter`.
- **Game Engine:**
  - `Game` class managing players, deck, and game flow, with a side-effect-free constructor and an explicit `run()`.
  - `Player` abstraction with a computer player implementation; players are owned via `std::unique_ptr`.
  - Deck shuffling uses a Mersenne Twister PRNG seeded from `std::random_device`.
- **Modern Build System:**
  - CMake 3.28+ with presets (`debug`, `release`, `asan`), plus a thin Makefile wrapper for convenience.
  - All build artifacts are placed in a dedicated `build/` directory; `compile_commands.json` is exported for tooling.
- **Testing & CI:**
  - Catch2 v3 unit tests (pinned to an exact commit via FetchContent) and CLI smoke tests, wired into CTest.
  - GitHub Actions CI: GCC 14 + Clang 18 build matrix, ASan/UBSan run, clang-format, and clang-tidy.

## Directory Structure

```
garbage/
├── .github/workflows/   # CI pipeline
├── include/             # Header files
├── src/                 # Source files
├── tests/               # Catch2 unit tests
├── build/               # Build artifacts (created automatically, per preset)
├── CMakeLists.txt       # Build definition
├── CMakePresets.json    # debug / release / asan presets
├── Makefile             # Convenience wrapper around CMake
├── .clang-format        # Formatting rules (enforced in CI)
├── .clang-tidy          # Lint rules (enforced in CI)
├── .gitignore
├── CONTRIBUTING.md      # Build/test/format instructions for contributors
├── LICENSE              # MIT
└── README.md            # Documentation
```

## Build Instructions

1. **Requirements:**

   - GCC 14+ or Clang 18+ (with a C++23 standard library, e.g. libstdc++ 14)
   - CMake 3.28+ and GNU Make
   - Network access on first configure (to fetch Catch2 for the tests; pass `-DBUILD_TESTING=OFF` to skip)

2. **Build the project:**

   ```sh
   make            # equivalent to: cmake --preset release && cmake --build --preset release
   ```

   The binary is emitted at `build/release/garbage`. Use `make PRESET=debug` (or `asan`) for the other presets.

3. **Run the game:**

   ```sh
   ./build/release/garbage <num_players> <starting_round> <shuffle_enabled>
   # Example:
   ./build/release/garbage 2 10 true
   ```

   - `num_players`: Number of players (1-4)
   - `starting_round`: Starting round number (1-10)
   - `shuffle_enabled`: true/1/t enables shuffling (case-insensitive); any other value disables it

   Invalid arguments are rejected with a nonzero exit code: a wrong argument count or non-numeric values print a usage message, while out-of-range values print a specific range error. Note that full games print thousands of lines — consider piping the output to a file or `less`.

4. **Run the tests:**

   ```sh
   make test       # unit tests + CLI smoke tests via CTest
   make sanitize   # same suite under AddressSanitizer + UBSan
   ```

5. **Clean the build:**
   ```sh
   make clean
   ```

## Example Output

A trimmed excerpt from `./build/release/garbage 2 3 true` (a 2-player game starting at round 3):

```
Player 1's turn...
Player 1's turn. Current hand: XX XX XX
Top of discard pile: A♠
Player 1 takes from discard pile: A♠
Played card: A♠, replaced card: 9♠
Player 1 discards: 9♠
Player 2's turn...
Player 2's turn. Current hand: XX XX XX
Top of discard pile: 9♠
Player 2 draws from deck: 2♣
Played card: 2♣, replaced card: 5♣
Player 2 discards: 5♣
...
===========
Game over!
Final Scores:
Player 1: Round 2
Player 2 is the winner!
```

## Extending

New player types plug in with three steps:

1. Subclass `Player` (see `ComputerPlayer` in `include/Player.h`) and implement `take_turn`, `add_card`, `reset_hand`, and `register_win`.
2. Return your new type from `Player_factory` in `src/Player.cpp`.
3. Rebuild — `Game` drives any `Player` implementation through the same interface.

## Contributing

Contributions are welcome! Please open issues or pull requests for improvements, bug fixes, or new features. See [CONTRIBUTING.md](CONTRIBUTING.md) for build, test, and formatting instructions — CI gates on the build matrix, tests, sanitizers, clang-format, and clang-tidy.

## License

This project is licensed under the [MIT License](LICENSE).
